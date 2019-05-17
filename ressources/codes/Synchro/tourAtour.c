// programme tourAtour.c

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#define n  3

sem_t S[n] ; // initialisation dans la fonction main S[0]=1, S[i]=0 pour i>0
void *tourAtour(void *num) {
    int  i = *((int*) num), c=0;
    while(1) {
        sem_wait(&S[i]);
        printf("Cycle %d de %d\n", c++,i);
        sem_post(&S[(i+1)%n]);
    }
}

int main()
{ 
  pthread_t tid[n];
  int i, numthread[n];
  for(i=0; i<n; i++) 
	if(i==0)  sem_init(&S[i], 0, 1);
  	else sem_init(&S[i], 0, 0);
  for(i=0; i<n; i++)
  {	  numthread[i] = i;
	  pthread_create(&tid[i], NULL, tourAtour,&numthread[i]);
  }
  sleep(10); 
  for(i=0; i<n; i++) pthread_cancel(tid[i]);
  for(i=0; i<n; i++) pthread_join(tid[i],NULL);

return 0;
}

