#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main () {

    const char* PIPE_NAME = "monTube";

    // Creation du tube
    mkfifo(PIPE_NAME, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

    const pid_t cpid = fork();

    if (!cpid) { // fils
        int fd;
        char message[50];
        pid_t mainPID = getpid();

        sprintf(message, "bonjour du writer [%d]", mainPID);

        // Ouverture du pipe en mode ecriture et creation si !existe
        fd = open("monTube", O_WRONLY);
        printf("Ici writer [%d]\n", mainPID);

        if (fd == -1) {
            printf("Tube non disponible\n");
            exit(1);
        }

        // Ecriture d'un message dans le pipe
        write(fd, message, strlen(message) + 1); // +1 pour le retour a la ligne
        printf("message ecrit\n");
        close(fd);
        exit(0);
    }
    else { // parent
        
        int fd;
        int readStatus;
        char message[100];

        // ouverture du pipe en mode lecture
        fd = open("monTube", O_RDONLY);
        printf("Ici reader [%d] : attente de l ecriture\n", getpid());

        if (fd == -1) {
            printf("Tube non disponible\n");
            return 1;
        }

        wait(NULL);
        printf("Ici reader [%d] : attente terminee\n", getpid());

        while (read(fd, message, 50) > 0) {
            printf("Message lu: %s\n", message);
            close(fd);
        }

        exit(0);

    }

    wait(NULL);

    return 0;

}