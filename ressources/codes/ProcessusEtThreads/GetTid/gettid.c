// threads4.c : threads POSIX = threads noyau sous Linux 
#include <unistd.h> //pour sleep
#include <stdio.h>  // pour printf
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>

void* thread1(void * nused)
{        printf("ici thread1 %ld du processus %d\n", syscall(SYS_gettid), getpid());
        pthread_exit(NULL);
}

void* thread2(void * nused)
{       printf("ici thread2 %ld du processus %d\n",syscall(SYS_gettid), getpid());
        pthread_exit(NULL);
}
// threads7.c : threads POSIX = threads noyau sous Linux 
int main( )
{        pthread_t tid1, tid2;
         // creation de deux threads
        if ( pthread_create(&tid1, NULL, thread1, NULL) != 0)    return -1;
        if ( pthread_create(&tid2, NULL, thread2, NULL) != 0)   return -1;
        // attente de la fin des threads
        pthread_join(tid1,NULL);
        pthread_join(tid2,NULL);
        printf("ici thread principal %ld du processus %d \n",syscall(SYS_gettid), getpid());
        return 0;
}

