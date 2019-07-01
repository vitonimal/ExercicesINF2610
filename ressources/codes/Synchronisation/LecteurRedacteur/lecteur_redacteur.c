#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

sem_t mutex;
sem_t redact;
int db = 42;
int nbL = 0;

// BOUCLES INFNIES POUR OBSERVATION

void* lecteur(void* arg) {
    while (1) {
        sem_wait(&mutex);
        if (nbL == 0) {
            sem_wait(&redact); // il va y avoir un lecteur dans la bdd! Il faut decrementer le semaphore de redaction
        }
        nbL++;
        sem_post(&mutex);
        //lecture de la bdd
        sleep(1);
        printf("lecteur db=%d\n", db);

        // fin de l'access a la base
        sem_wait(&mutex);
        nbL--;
        if (nbL == 0) {
            sem_post(&redact); // il n'y a plus de lecteurs! les ecrivains peuvent y aller!
        }
        sem_post(&mutex);
    }
    return NULL;
}

void* redacteur(void* arg) {
    while (1) {
        sem_wait(&redact);
        // modifier les donnees de la bd bd
        db++;
        printf("redacteur bd=%d\n", db);
        sleep(1);
        sem_post(&redact);
    }
    return NULL;
}

int main() {
    const u_int8_t NUMBER_OF_THREADS = 5;
    pthread_t tids[5];

    sem_init(&mutex, 0, 1);
    sem_init(&redact, 0, 1);

    pthread_create(&tids[0], NULL, lecteur, NULL);
    pthread_create(&tids[1], NULL, lecteur, NULL);
    pthread_create(&tids[2], NULL, lecteur, NULL);
    pthread_create(&tids[3], NULL, redacteur, NULL);
    pthread_create(&tids[4], NULL, redacteur, NULL);

    for (int i = 0; i < NUMBER_OF_THREADS; ++i) {
        pthread_join(tids[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&redact);

    return 0;
}