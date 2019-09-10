#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    mkfifo("tubeA", 0660);
    mkfifo("tubeB", 0660);
    if (fork() == 0) {
        // fils
        int f1 = open("tubeA", O_WRONLY);
        int f2 = open("tubeB", O_RDONLY);
        close(f1);
        close(f2);
        exit(0);
    }
    int f1 = open("tubeB", O_WRONLY);
    int f2 = open("tubeA", O_RDONLY);
    close(f1);
    close(f2);
    wait(NULL);
    return 0;
}