#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// char *chaine1;
int main(int argc, const char *argv[], const char *envp[]) {
    
    int cpid = fork();
    int k;

    printf("Paramètres:\n");
    for (k = 0; k < argc; k++)
        printf("%d: %s\n", k, argv[k]);

    printf("---------------------------------------------------\n");
    printf("Variables d'environnement:\n");
    printf("---------------------------------------------------\n");
    for (k = 0; envp[k] != NULL; k++)
        printf("%d: %s\n", k, envp[k]);
    printf("---------------------------------------------------\n");

    char *newenviron[] = { "TOKEN_NOCHILD" };
    printf( "No_CHild=%s\n", getenv("TOKEN_NOCHILD")); 
    setenv("TOKEN_NOCHILD","TRUE",1);
    printf( "No_CHild=%s\n", getenv("TOKEN_NOCHILD"));
    printf("fork result = %d\n", cpid); 
    return 0;
}

