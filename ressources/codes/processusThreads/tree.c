// programme tree.c: appel système fork)
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main( ) {
    pid_t p;
    int i, n=5;
    for (i=1; i<n; i++) {
        p = fork();
        if (p > 0)
            break;
	sleep(1);
        printf(" Processus %d  de père %d. \n",  getpid(), getppid());
        //sleep(2);
    }
    //sleep(2);
    return 0;
}

