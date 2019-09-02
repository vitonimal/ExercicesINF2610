// programme forkExecve.c
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> // pour exit
int main( ) {
    
    if (fork()==0) { // fils
	   //  printf("Le premier fils de pid=%d va se transformer \n",getpid());
             char* args[]={"fils", NULL};
	     char* env[]={"PWD=../",NULL};
	     execve("./fils",args,env);
	     printf("echec de execvpe \n");
	     exit(1);
       } // p�re
    int pid, status; 
    pid=wait(&status);
    printf("fin du fils %d axec %d\n", pid, WEXITSTATUS(status));
    return 0;
}


