#include <semaphore.h>  // pour les sémaphores
#include <pthread.h> // pour pthread_create et pthread_join
#include <stdio.h>  // pour printf
#include <fcntl.h>
#define val 1
sem_t*  mutex;  // sémaphore
long long var_glob=0;
void* increment( void *);
void* decrement( void *);
int main ( )
{       pthread_t threadA, threadB;
        int i=1;
        if((mutex = sem_open("/mutex", O_CREAT, 0644, 1)) == SEM_FAILED )
        perror("error in opening sem");
       else {
        // sem_init(&mutex, 0, val);              // initialiser mutex
        printf("ici main : var_glob = %lld, mutex=%d, i=%d\n", var_glob, sem_getvalue(mutex,&i),i);
        pthread_create(&threadA, NULL, increment,NULL); // création d'un thread pour increment
        printf("ici main creation d un thread\n");
	pthread_create(&threadB,NULL,decrement,NULL); // création d'un thread pour decrement
        pthread_join(threadA,NULL); // attendre la fin des threads
          pthread_join(threadB,NULL);
       sem_close(mutex);
      printf("ici main, fin threads : var_glob =%lld \n",var_glob);
     }
      return 0;
}
void* decrement(void *)
{       // attendre l'autorisation d'accès
        long long i; int j; printf("ici decrement %d\n", sem_getvalue(mutex,&j));
        sem_wait(mutex);  
         for(i=0;i<100;i++) var_glob= var_glob - 1 ;
        printf("ici sc de decrement : var_glob = %lld, mutex=%d\n", var_glob,sem_getvalue(mutex,&j));
        sem_post(mutex);
        return (NULL);
}
void* increment (void *)
{       long long i; int j;
        sem_wait(mutex);
         for(i=0;i<100;i++)  var_glob=var_glob + 1;
        printf("ici sc de increment : var_glob = %lld, mutex=%d\n", var_glob,sem_getvalue(mutex,&j));
        sem_post(mutex);
        return (NULL);
}


