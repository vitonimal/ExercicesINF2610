#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5
#define G (i+1)%N
#define D i
#define libre 1
#define occupe 0

int fourchettes[N] = { libre, libre, libre, libre, libre };

sem_t mutex;

void* philosophe(void* arg) {
    int i = *(int*) arg;
    int tours = 2;
    while (tours) {
        sleep(1); // penser
        sem_wait(&mutex);
        if (fourchettes[G] == libre && fourchettes[D] == libre) {
            fourchettes[G] = occupe;
            fourchettes[D] = occupe;
            sem_post(&mutex);
            tours--;
            printf("le philosophe %d mange\n", i);
            sleep(1); // manger
            printf("le philosophe %d a fini de manger\n", i);
            sem_wait(&mutex);
            // liberer les fourchettes
            fourchettes[G] = libre;
            fourchettes[D] = libre;
            sem_post(&mutex);
        } else {
            sem_post(&mutex);
        }
    }
}

int  main() {
    int i, numPhilosophe[N] = {0, 1, 2, 3, 4};
    pthread_t tids[N];

    sem_init(&mutex, 0, 1);

    for (i = 0; i < N; ++i) {
        pthread_create(&tids[i], NULL, philosophe, &numPhilosophe[i]);
    }

    for (i = 0; i < N; i++) {
        pthread_join(tids[i], NULL);
    }

    printf("fin des threads\n");

    return 0;
}