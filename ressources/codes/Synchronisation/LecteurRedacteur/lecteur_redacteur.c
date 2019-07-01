#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

sem_t mutex;
sem_t redact;
sem_t tour;
int db = 42;
int nbL = 0;

int getRandomTo(int limit) {
    return rand() % limit + 1;
}

// BOUCLES INFNIES POUR OBSERVATION

void* lecteur(void* arg) {
    while (1) {
        sem_wait(&tour);
        sem_wait(&mutex);
        if (nbL == 0) {
            sem_wait(&redact); // il va y avoir un lecteur dans la bdd! Il faut decrementer le semaphore de redaction
        }
        nbL++;
        sem_post(&mutex);
        sem_post(&tour);
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
        sleep(getRandomTo(3));
    }
    return NULL;
}

void* redacteur(void* arg) {
    while (1) {
        sem_wait(&tour);
        sem_wait(&redact);
        // modifier les donnees de la bd bd
        db++;
        printf("redacteur bd=%d\n", db);
        sleep(2);
        sem_post(&tour);
        sem_post(&redact);
        sleep(getRandomTo(5));
    }
    return NULL;
}

int main() {
    pthread_t tid1, tid2;

    sem_init(&mutex, 0, 1);
    sem_init(&redact, 0, 1);
    sem_init(&tour, 0, 1);

    pthread_create(&tid1, NULL, lecteur, NULL);
    pthread_create(&tid2, NULL, redacteur, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    sem_destroy(&mutex);
    sem_destroy(&redact);
    sem_destroy(&tour);

    return 0;
}