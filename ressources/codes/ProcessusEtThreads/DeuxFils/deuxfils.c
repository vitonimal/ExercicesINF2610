// programme deuxfils.c
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
void fils(int i);
int main() {
    int status;
    if (fork()==0) { // premier filss
            fils(1);
    } else if (fork()==0) { // second  fils
        fils(2);
    } else  {
    		if (wait(&status) > 0)
        	   printf("fin du fils%d\n", WEXITSTATUS(status));
    		if (wait(&status) > 0)
        	   printf("fin du fils%d\n", WEXITSTATUS(status));
	}
    return 0;
}
void fils(int i) {
    sleep(2);
    _exit(i);
}

