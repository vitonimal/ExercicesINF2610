#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigintHandler(int signum) {
    printf("Eh bien! Vous avez appuye sur CTRL+C!\n");
}

int main () {

    struct sigaction* newConfig = calloc(1, sizeof(struct sigaction));
    struct sigaction* oldConfig = calloc(1, sizeof(struct sigaction));

    newConfig->sa_sigaction = &sigintHandler;

    sigaction(SIGINT, newConfig, oldConfig);

    printf("Gestionnaire change! Essayez CTRL+C\n");

    pause();

    return 0;

}