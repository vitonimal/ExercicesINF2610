// programme threadsleepWakeup.c
#include <unistd.h> 
#include <pthread.h>
#include <stdio.h>
#include <signal.h>

int  glob=0;
pthread_spinlock_t lock;
pthread_t tid1, tid2;

void* inc_dec(void * x) {
        int i;
        int j;
        int pas = *(int *) x;
        sigset_t set;    
        sigemptyset(&set);
        for(i=0; i<100000; i++){
                while (pthread_spin_trylock(&lock)!=0) {
                        sigsuspend(&set); // attendre un signal
                }
                glob = glob + pas;
		for(j=0; j<50000; j++); // Simulation d'un traitement
		pthread_spin_unlock(&lock);
                if(pas==1) {
                        pthread_kill(tid2,SIGCONT); // WAKEUP thread 2
                }
                else {
                        pthread_kill(tid1,SIGCONT); // WAKEUP thread 1
                }
        } 
        printf("Fin inc_dec(%d), glob=%d\n", pas, glob);  // attention
        pthread_exit(NULL);
}
// programme threadsleepWakeup.c
int main( )
{
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

        pthread_join(tid1,NULL); 
	pthread_join(tid2,NULL);
        printf("ici main : fin des threads, glob = %d \n",glob);
        pthread_spin_destroy(&lock);
        return 0;
}

