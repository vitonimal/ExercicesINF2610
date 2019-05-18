#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
void action (int signum) { printf( "signal %d recu \n", signum); }
void * fonction (void * x) 
{ signal(SIGINT, action);
  printf("ici thread %lu, je vais me mettre en pause \n", pthread_self()); pause(); 
  printf("ici thread %lu, je vais terminer \n", pthread_self());
  pthread_exit(0);}
int main()
{  int pid;
   pthread_t tid;
   pthread_create (&tid, NULL, fonction, NULL);
   pid = fork();
   if( pid==0)
   {  printf( "ici processus fils %d, le thread de mon pere est %lu\n", getpid(), tid);
	sleep(1); printf(" ici fils, envoie du signal SIGCONT au thread de mon pere %d\n",
	pthread_kill(tid,SIGCONT)); sleep(1);
	pthread_kill(tid,SIGINT);  sleep(1); 
	printf("ici fils envoie de SIGINT au pere %d\n", kill(getppid(),SIGINT));
	printf("ici fils envoie de SIGKILL au pere %d\n", kill(getppid(),SIGKILL));

	printf( "ici fils va terminer %s\n", strerror(errno) ); 
   }
   else { pthread_join(tid, NULL); printf("ici pere fin du thread detectee \n"); wait(NULL); }
 return 0;
}

