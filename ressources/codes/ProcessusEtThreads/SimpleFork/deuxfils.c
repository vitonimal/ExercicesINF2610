// programme deuxfils.c
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
void fils(int i);
int main() {
    if (fork()==0) { // premier filss
            fils(1);
    } else if (fork()==0) { // second  fils
        fils(2);
    } else  {
    		if (wait(NULL) > 0)
        	   printf("fin du fils\n");
    		if (wait(NULL) > 0)
        	   printf("fin du fils\n");
	}
    return 0;
}
void fils(int i) {
    sleep(2);
    _exit(i);
}

