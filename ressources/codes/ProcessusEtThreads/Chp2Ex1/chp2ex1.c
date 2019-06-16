#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    int i;
    int n = 2;
    pid_t fils_pid;

    for (i = 0; i < n; ++i) {
        fils_pid = fork();
        if (fils_pid > 0) {
            wait(NULL);
            break;
        }
    }
    printf("Processus %d de pere %d\n", getpid(), getppid());
    return 0;
}
