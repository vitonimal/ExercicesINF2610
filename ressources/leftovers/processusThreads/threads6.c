//threads6.c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h>
static unsigned long long a = 0;
#define MAX 1000000000
void *count(void *arg) ;

int main( ) {
        pthread_t t1, t2;
        pthread_create(&t1, NULL, count, &a);
        pthread_create(&t2, NULL, count, &a); 
	pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        printf("pid=%d, tid=%d,  a=%llu\n", getpid(), syscall(SYS_gettid), a);
        return 0;
}

void *count(void *arg) {
  volatile unsigned long long*var = (unsigned long long*) arg;
  volatile unsigned long long i;
  for (i = 0; i < MAX; i++)
	*var = *var + 1;
   printf("pid = %d, tid=%d, a=%llu\n", getpid(), syscall(SYS_gettid),a);
  return NULL;
}

