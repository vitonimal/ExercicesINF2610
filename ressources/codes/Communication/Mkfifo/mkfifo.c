#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main () {
     mkfifo("monTube", 0660);
     if (!fork()) { // fils
        char m[50];
        int i;
        int fd = open("monTube", O_WRONLY);
        printf("Ici writer [%d]\n", getpid());
        // Ecriture dans le pipe
        for(i=0; i<4;i++) {
            sprintf(m, "mess%d de [%d]\n", i,getpid());
            write(fd, m, strlen(m) + 1); 
        }
        close(fd);
    }
    else { // parent
        char m;
        int fd = open("monTube", O_RDONLY);
        // lire du pipe 
        while (read(fd, &m, 1) > 0) {
            write(1,&m,1);
        }
       close(fd);
       wait(NULL);
    }
    exit(0);
}