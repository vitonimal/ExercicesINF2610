// threads3.c  
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
void afficher(int n, char lettre)
{	int i,j;
	for (j=1; j<n; j++) 
	{	for (i=1; i < 10000000; i++);
		printf("%c",lettre);
		fflush(stdout);
	}
}
void *thread(void *plettre)
{	char lettre = *(char *) plettre;
	afficher(100,lettre);
	printf("\n Fin du thread %c\n",lettre);
	fflush(stdout);
	pthread_exit(NULL);
}
int main()
{

	pthread_t thA, thB, thC;
	
	printf("Creation des threads A et B\n");
	pthread_create(&thA, NULL, thread, (void *)"A");	
	pthread_create(&thB, NULL, thread, (void*)"B");
        //attendre la fin des threads A et B
        printf("Le thread principal attend la fin des threads A et B\n");
	pthread_join(thA,NULL);
	pthread_join(thB,NULL);
	printf("\n Creation du thread C\n");
	pthread_create(&thC, NULL, thread, (void*)"C");
               printf("Le thread principal attend la fin du thread C\n");
        pthread_join(thC,NULL);
       	_exit(0);
}
