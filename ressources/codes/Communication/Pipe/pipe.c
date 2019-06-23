#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../../../env_config/env_config.c"

int main(int argc, char* argv[]) {

    bootEnvVars(&argc, &argv);

    int fd[2];
    pid_t cpid;
    char buf;

    assert(argc == 2);

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);   
    }

    cpid = fork();

    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {
        // L'enfant est le lecteur
        close(fd[1]); // on ferme le descripteur non utilise
        while (read(fd[0], &buf, 1) > 0) { // tant que nous pouvons lire un caractere
            write(STDOUT_FILENO, &buf, 1); // nous l'affichons sur la sortie standard
        }
        write(STDOUT_FILENO, "\n", 1); // puis nous faisons un saut de ligne
        close(fd[0]); // on a termine la lecture
    }
    else {
        // Le parent ecrit le message passe en argument dans le tube
        close(fd[0]); // on ferme le descripteur non utilise
        write(fd[1], argv[1], strlen(argv[1])); // on ecrit le message dans le tube
        close(fd[1]); // on a termine l'ecriture
        wait(NULL); // On attend le fils
        exit(EXIT_SUCCESS);
    }

}