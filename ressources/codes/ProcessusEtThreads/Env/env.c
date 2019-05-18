#include <stdio.h>
#include <stdlib.h>
int main(int argc, const char *argv[], const char *envp[]) {
	int k;
	printf("Affichage des paramèes effectifs :\n");
	for (k=0; k<argc; k++) 
		 printf("%d: %s\n", k, argv[k]); 
	printf("Affichage des variables d'environnement:\n");
	for (k=0; envp[k]!=NULL; k++)  
		printf("%d: %s\n", k, envp[k]);
	return 0;
}

