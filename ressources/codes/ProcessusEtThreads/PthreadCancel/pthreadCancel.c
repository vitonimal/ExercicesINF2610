// pthreadCancel.c Annulation d'un thread
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

// pour les variantes 1,2 et 3
void mfree (void *arg)  {
    printf("free\n"); free(arg);
}
//

void* mthread(void*taille);

int main() {
    pthread_t th;
    int* pstatus;
    if(pthread_create(&th,NULL,mthread,(void*)5))   return 1;
    // pour les variantes 1,2 et 3
    usleep(200000);  // usleep(280000); 
    pthread_cancel(th);
    //
    pthread_join(th, (void**) &pstatus);
    if(pstatus == PTHREAD_CANCELED) { 
        printf("\n Terminaison forcÃ©e\n");
    }
    else if(pstatus== NULL) {
        printf("Terminaison normale avec NULL\n");
    }
    else {
        printf("Terminaison normale avec %p.\n", pstatus);
        for(int i=0; i<5;i++)
        { 
            printf("tab[%d]=%d ", i, pstatus[i]);
        }
        printf("\n");
        free(pstatus);
    }
    return 0;
}


void *mthread(void *taille)
{    
    setvbuf(stdout, (char *) NULL, _IONBF, 0);
    int*tab = (int*) malloc ( (long)taille*sizeof(int));
    if (tab!=NULL)
    {   // pour les variantes 2 et 3
        pthread_cleanup_push(mfree, (void*) tab);
        //
        for (long i=0; i<(long)taille; i++) {
            tab[i]=i;
            printf("%ld sur %ld ",i,(long)taille-1);
            usleep(50000); // pour ralentir le traitement, attendre 5ms
        }
        printf("fin \n");
        // pour la variante 3
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
        //
        // pour les variantes 2 et 3
        pthread_cleanup_pop(0);
        // pour la variante 3
        sleep(5);
    }
    pthread_exit ((void*) tab);
}



