// programme threads1pinlock.c; partage de variables
#include <unistd.h> //pour sleep
#include <pthread.h>
#include <stdio.h>

int  glob=0;
pthread_spinlock_t lock;
void* inc_dec(void * x)
{   
	int i, j, pas = *(int *) x;
	for(i=0; i<100000; i++)
	{	pthread_spin_lock(&lock);
		glob = glob + pas ;
		for(j=0; j<50000; j++); // attente active dans la section critique
		pthread_spin_unlock(&lock);
		// for(j=0; j<50000; j++); // attente active en dehors de la section critique
	}
        printf("ici inc_dec(%d), glob = %d, thread_id = %lu, pid=%d\n", pas, glob, pthread_self(), getpid());
        pthread_exit(NULL);
}

int main( )
{   	
	pthread_t tid1, tid2;
  	int th1=1, th2=-1;
	
	printf("ici main, glob = %d\n", glob);
	
	pthread_spin_init(&lock,PTHREAD_PROCESS_PRIVATE);
    
	//creation de deux threads
	if ( pthread_create(&tid1, NULL, inc_dec, (void*) &th1 )!= 0)
		return -1;
	printf("ici main: creation du thread inc_dec(%d) avec succes\n",  th1);
	if ( pthread_create(&tid2, NULL, inc_dec, (void*) &th2) != 0)
		return -1;
	printf("ici main: creation du thread inc_dec(%d) avec succes\n", th2);
    
	pthread_join(tid1,NULL); // attendre la fin du thread tid1
    pthread_join(tid2,NULL);
    
	printf("ici main : fin des threads, glob = %d \n",glob);
	
	pthread_spin_destroy(&lock);
    
	return 0;
}

