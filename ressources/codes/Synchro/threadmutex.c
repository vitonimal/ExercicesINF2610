// programme threadmutex.c
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

int  glob=0;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
void* inc_dec(void * x)
{
        int i, j, pas = *(int *) x;
        for(i=0; i<100000; i++)
        {       pthread_mutex_lock(&mutex);
                glob = glob + pas ;
                for(j=0; j<50000; j++);
                pthread_mutex_unlock(&mutex);
        }
        printf("Fin de inc_dec(%d), glob =%d\n", pas, glob);
        pthread_exit(NULL);
}
// programme threadmutex.c
int main( )
{
        int th1=1, th2=-1;
        printf("ici main, glob = %d\n", glob);
        pthread_t tid1, tid2;

        //creation de deux threads
        if ( pthread_create(&tid1, NULL, inc_dec, (void*) &th1 )!= 0)    return -1;
        printf("ici main: creation du thread inc_dec(%d) avec succes\n", th1);
        if ( pthread_create(&tid2, NULL, inc_dec, (void*) &th2) != 0)   return -1;
        printf("ici main: creation du thread inc_dec(%d) avec succes\n", th2);

        // attendre la fin des deux threads
        pthread_join(tid1,NULL);
        pthread_join(tid2,NULL);
        printf("ici main : fin des threads, glob = %d \n",glob);
        pthread_mutex_destroy(&mutex);
        return 0;
}

