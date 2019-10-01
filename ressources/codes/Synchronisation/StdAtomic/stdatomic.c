// programme stdatomic.c
#include <stdatomic.h>
#include <pthread.h>
#include <stdio.h>
volatile atomic_long a;
volatile long b;
const int un=1, moinsun=-1;
void* inc_dec(void * x)
{
    int pas = *(int *)x;
    for(int i=0; i<100000; i++)
    {
        atomic_fetch_add(&a,pas);
        b=b+pas;
    }
    printf("Fin de inc_dec(%d), a =%ld, b=%ld\n", pas, a,b);
    pthread_exit(NULL);
}

int main( )
{
    atomic_init(&a,0);
    printf("ici main, a = %ld, %ld \n", a,b);
    pthread_t tid1, tid2;
    
    //creation de deux threads
    if ( pthread_create(&tid1, NULL, inc_dec, (void*)&un )!= 0)    return -1;
    //printf("ici main: creation du thread inc_dec(%d) avec succes\n",un);
    if ( pthread_create(&tid2, NULL, inc_dec, (void*)&moinsun) != 0)   return -1;
    // printf("ici main: creation du thread inc_dec(%d) avec succes\n",moinsun);
    
    // attendre la fin des deux threads
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    printf("ici main : fin des threads, a = %ld, b=%ld \n", a,b);
    return 0;
}

