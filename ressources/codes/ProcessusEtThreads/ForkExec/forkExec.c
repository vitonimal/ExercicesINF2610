// programme forkExec.c
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> // pour exit
int main( ) {
    int status;
    if (fork()==0) { // premier fils
	    printf("Le premier fils de pid=%d va se transformer \n",getpid());
            execl("/bin/ls","ls", "-l",NULL);
	    printf("echec de execl de ls ./\n");
	    exit(1);
    } else if (fork()==0) { // second  fils
	       printf("Le second fils de pid=%d va se transformer \n",getpid());
            char* params[]={"ls", "-a", NULL};
			execv("/bin/ls",params);
			printf("echec de execv de ls -a/\n");
				exit(1);
			} else  {
			if ((status=wait(NULL)) > 0)
				printf("fin du fils de pid=%d\n", status);
			if ((status=wait(NULL))>0)
				printf("fin du fils de pid=%d\n", status);
	}
    return 0;
}


