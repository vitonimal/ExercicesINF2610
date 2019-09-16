#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
static volatile unsigned long long counter = 0;
#define MAX 1000000000

void* count(void *arg) {
    volatile unsigned long long*receivedValue = (unsigned long long*) arg;
    volatile unsigned long long i;
    for (i = 0; i < MAX; i++) {
        *receivedValue += 1;
    }
    pthread_exit(NULL);
}

int main( ) {
    pthread_t t1, t2;
    
    
    pthread_create(&t1,NULL,count, (void*)&counter);
    pthread_create(&t2,NULL,count, (void*)&counter);
    
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    
    printf("pid= %d counter=%llu\n", getpid(), counter);
    
    return 0;
}