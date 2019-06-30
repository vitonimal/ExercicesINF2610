#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 6
#define BUFF_SIZE 3

typedef struct args {
    sem_t libre;
    sem_t occupe;
} args_t;

void* prod(void* arg);
void* cons(void* arg);

static int buf[BUFF_SIZE];

int main () {

    pthread_t producteur, consommateur;
    args_t args;

    sem_init(&args.libre, 0, BUFF_SIZE);
    sem_init(&args.occupe, 0, 0);

    pthread_create(&producteur, NULL, prod, &args);
    pthread_create(&consommateur, NULL, cons, &args);

    pthread_join(producteur, NULL);
    pthread_join(consommateur, NULL);

    printf("FIN \n");

    return EXIT_SUCCESS;
}

void* prod(void* arg) {
    int ip = 0;
    int nbProd = 0;
    int objAInserer = 1001;

    args_t* args = (args_t*) arg;
    
    while (nbProd < MAX) {
        sem_wait(&args->libre);
        buf[ip] = objAInserer;
        sem_post(&args->occupe);
        objAInserer++;
        nbProd++;
        ip = (ip + 1) % BUFF_SIZE;
    }

    return NULL;
}

void* cons(void* arg) {
    int ic = 0;
    int nbCons = 0;
    int objRecupere;

    args_t* args = (args_t*) arg;
    
    while (nbCons < MAX) {
        sem_wait(&args->occupe);
        objRecupere = buf[ic];
        sem_post(&args->libre);
        nbCons++;
        ic = (ic + 1) % BUFF_SIZE;
    }

    return NULL;
}