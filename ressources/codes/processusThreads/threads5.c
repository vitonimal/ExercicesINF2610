// threads5.c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
static unsigned long long a = 0;
#define MAX 1000000000
void *count(void *arg) ;
int main( ) {
        int p, i;
        for (i = 0; i < 2; i++) {
        if ((p = fork()) < 0) return 1;
        if (p == 0) {   count(&a);
           printf("child %d a=%llu\n", getpid(), a);
           return 0;
         }
        }
        for (i = 0; i < 2; i++) { wait(NULL);}
        printf("parent %d a=%llu \n", getpid(), a);
        return 0;
}
void *count(void *arg) {
  volatile unsigned long long*var = (unsigned long long*) arg;
  volatile unsigned long long i;
  for (i = 0; i < MAX; i++) 
	*var = *var + 1;
  return NULL;
}

