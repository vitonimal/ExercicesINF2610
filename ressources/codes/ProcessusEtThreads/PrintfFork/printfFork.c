#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {

    printf("bonjour je suis le processus principal de pid %d", getpid());

    int cpid = fork();

    if (!cpid) {
        printf("Ici le fils!\n");
        exit(0);
    }

    printf("Fin du programme\n");

    return 0;

}
