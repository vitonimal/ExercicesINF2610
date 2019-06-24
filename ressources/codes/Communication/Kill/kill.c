#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void handler(int signum) {
    printf("Ici le handler!\n");
}

int main() {

    pid_t cpid = fork();

    if (!cpid) {
        // fils
        
        // On assigne au signal SIGUSR1 le gestionnaire handler
        signal(SIGUSR1, handler);

        // On attend le signal SIGUSR1
        pause();

        exit(EXIT_SUCCESS);

    }

    // Pere

    // On attend quelques secondes
    sleep(5);

    // On envoie le signal SIGUSR1 au fils
    kill(cpid, SIGUSR1);

    // On attend la fin du fils
    wait(NULL);

    exit(EXIT_SUCCESS);
}