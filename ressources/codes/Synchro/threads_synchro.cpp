// programme threads.c
#include <unistd.h> //pour sleep
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
int glob=0;
sem_t mutex;
void* decrement(void * x)
{ 	int r;
	// sem_wait(&mutex);
	r = glob;
	for(int j=0; j<10000; j++)
	{ r=r-1;} 
	glob = r ;
	printf("ici decrement[%u], glob = %d\n", pthread_self(),glob);
	// sem_post(&mutex);
	pthread_exit(NULL);
 }

void* increment (void * x)
{
	int r;
	// sem_wait(&mutex);
	r = glob;
	for(int j=0; j<10000; j++)
	{ r=r+1;}
	glob = r;
	printf("ici increment[%u], glob = %d\n", pthread_self(), glob);
	//sem_post(&mutex);
	pthread_exit(NULL);
}

int main( )
{	pthread_t tid1, tid2;
	sem_init(&mutex, 0, 1);
	printf("stdout = %d, %u, %u \n", stdout, STDOUT_FILENO, STDIN_FILENO);	
	printf("ici main[%d], glob = %d\n", getpid(),glob);
	//creation d'un thread pour increment
	if ( pthread_create(&tid1, NULL, increment, NULL) != 0)    return -1;
//	printf("ici main: creation du thread[%u] avec succes\n",tid1);
	// creation d'un thread pour decrement
	if ( pthread_create(&tid2, NULL, decrement, NULL) != 0)   return -1;
	 printf("ici main: creation du thread[%u] avec succes\n",tid1);
	printf("ici main: creation du thread [%u] avec succes\n",tid2);
	pthread_join(tid1,NULL); // attendre la fin dun thread
	pthread_join(tid2,NULL);
	printf("ici main : fin des threads, glob = %d \n",glob);
	return 0;								}
