// threads2.c Annulation d'un thread
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void mfclose (void *arg)  {
  printf("fclose\n"); fclose((FILE *)arg);
}

void munlink(void * arg)  {
  printf("unlink\n"); unlink((char*)arg);
}

void* mthread(void*inutilise);

int main() {
  pthread_t th;
  char* pstatus;
  if(pthread_create(&th,NULL,mthread,NULL) ){
    perror("Erreur dans la création du thread");
    return 1;
  }
  sleep(2);
  // pthread_cancel(th); // pour forcer la terminaison du thread
  pthread_join(th, (void**) &pstatus); // attendre la fin du thread
  if(pstatus == PTHREAD_CANCELED) {
    printf("Terminaison forcee du thread \n");
  }
  else if(pstatus== NULL) {
    printf("Terminaison normale du thread avec NULL\n");
  }
  else {
    printf("Terminaison normale du thread avec %s.\n", pstatus);
  }
  return 0;
}

void *mthread(void *inutilise)
{
  FILE* fichier; int i;
  setvbuf(stdout, (char *) NULL, _IONBF, 0);
  if ((fichier = fopen("sortie.txt","w")) == NULL)
    perror("Erreur dans l'ouverture du fichier");
  else {  // pour une terminaison propre
    pthread_cleanup_push(munlink, (void *) "sortie.txt");
    pthread_cleanup_push(mfclose, (void *) fichier);

    for (i=0; i<50; i++) {
      fprintf(fichier,"%d",i);
      fprintf(stdout,"%d sur 50 ",i);
      usleep(50000);
    }
    
    fprintf(stdout,"fin\n");
    pthread_cleanup_pop(1); // exécute fclose
    pthread_cleanup_pop(1); // exécute unlink
  }

  return (void*) "success";
}


