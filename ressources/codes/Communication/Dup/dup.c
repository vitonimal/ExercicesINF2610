#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Descripteur de STDIN: %d\n", STDIN_FILENO);
    int newStdin = dup(STDIN_FILENO);
    printf("Copie du descripteur de STDIN (apres dup): %d\n", newStdin);
}