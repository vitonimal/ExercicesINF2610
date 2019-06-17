#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {

    printf("message0\n");
    if (fork()) {
        printf("message1\n");
        if (fork()) {
            printf("message2\n");    
        }
        else {
            exit(0);
        }
    }
    else {
        printf("message3\n");
    }
    return 0;
}
