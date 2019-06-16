#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* action() {
    printf("Ici un thread!");
    fflush(stdout);
    return NULL;
}

int main () {

    pthread_t tid;
    pthread_create(&tid, NULL, action, NULL);
    pthread_join(tid, NULL);
    return 0;

}