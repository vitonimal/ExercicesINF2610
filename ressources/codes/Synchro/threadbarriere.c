// programme barriere.c

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#define n  3

pthread_barrier_t barrier1, barrier2;
void *tourAtour(void *num) {
    int  i = *((int*) num), c=0;
    while(c<10) {
       if(i==n-1)  pthread_barrier_wait(&barrier1);
        printf("Cycle %d de %d\n", c++,i);
        if(i<n-1) pthread_barrier_wait(&barrier1);
	pthread_barrier_wait(&barrier2);
    }
}

int main()
{ 
  pthread_t tid[n];
  int i, numthread[n];
  pthread_barrier_init(&barrier1,NULL,n);
  pthread_barrier_init(&barrier2, NULL,n);
  for(i=0; i<n; i++)
  {	  numthread[i] = i;
	  pthread_create(&tid[i], NULL, tourAtour,&numthread[i]);
  }

  for(i=0; i<n; i++) pthread_join(tid[i],NULL);
  pthread_barrier_destroy(&barrier1);
  pthread_barrier_destroy(&barrier2);

return 0;
}

