#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    printf("message0");
    fflush(stdout);
    if (fork()) {
        printf("message1");
        fflush(stdout);
        if (fork()) {
            printf("message2");    
            fflush(stdout);        
        }
        else {
            exit(0);
        }
    }
    else {
        printf("message3");
        fflush(stdout);
    }
    return 0;
}
