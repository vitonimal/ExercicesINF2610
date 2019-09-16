#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <sys/syscall.h>

void sigIntHandler (int signum) {
    printf( "signal %d recu  par %ld \n", signum, syscall(SYS_gettid));
 //    pthread_exit((void*)-1);
}

void * action (void * unused) {
 // signal(SIGINT, sigIntHandler); 
  printf("Thread %ld se met en pause \n", syscall(SYS_gettid));
  pause(); 
  printf("Thread %ld se termine \n", syscall(SYS_gettid));
  pthread_exit(NULL);
}

int main(){
    void *pstatus;
    pthread_t tid;
    pthread_create (&tid, NULL, action, NULL);
    // sleep(1);
    printf("Thread %ld envoie SIGINT (%d) au thread  \n", syscall(SYS_gettid), SIGINT);
    pthread_kill(tid, SIGINT);
    printf("Thread %ld attend la fin du thread \n",  syscall(SYS_gettid) );
    pthread_join(tid,&pstatus);
    if (pstatus==NULL || pstatus!=PTHREAD_CANCELED)
    {
      printf(" Fin normale du thread crÃ©Ã© \n");
    }
    else {
      printf(" Fin forcee du thread crÃ©Ã© \n");
    }
    return 0;
}
