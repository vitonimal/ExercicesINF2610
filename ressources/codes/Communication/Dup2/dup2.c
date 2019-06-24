#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    printf("On rend STDERR synonyme de STDIN en faisant dup2(STDIN_FILENO, STDERR_FILENO)\n");
    dup2(STDIN_FILENO, STDERR_FILENO);
    printf("On peut maintenant acceder a STDIN avec le descripteur 2 (qui appartenait initialement a STDERR)\n");
    printf("Ecrivez un message dans STDIN a partir du descripteur synonyme puis l'afficher sur STDOUT a partir du decripteur original\n");
    printf("Cela va nous permettre de verifier que le synonyme fonctionne bien\n");

    printf("Le programme attend que vous ecriviez un message dans le synonyme de stdin\n");
    char buffMessageLu[100];
    read(STDERR_FILENO, &buffMessageLu, 100 );

    printf("ICI STDOUT\n");
    printf(buffMessageLu);
}