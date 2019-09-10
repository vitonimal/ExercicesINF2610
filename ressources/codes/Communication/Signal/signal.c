#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sigintHandler(int num) {
    printf("signal SIGINT reçu par %d\n",getpid());
}
int main() {
    printf("assigner un gestionnaire personnalise a SIGINT\n");
    signal(SIGINT, sigintHandler);
    printf("c’est fait!\n");
    printf("appuyez sur CTRL+C!\n");
    pause();
    return 0;
}
