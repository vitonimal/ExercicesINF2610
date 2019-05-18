// programme test de execvp : texecvp.c
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
int main (int argc , char * argv[]) {
    if (fork() == 0) { // il s'agit du fils
        // exécute un autre programme
        execvp(argv[1], &argv[1]) ;
        fprintf(stderr, "invalide %s\n ",  argv[1]);
        _exit(1);
    }  
    int status;
   if(wait(&status) > 0)
        printf("fin du fils avec %d\n", WEXITSTATUS(status));
    return 0;
}

