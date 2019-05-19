#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#define N 3
#define M 2

/*0*/
sem_t S[N][M]; // utiliser pour bloquer/debloquer un joueur
sem_t Att ;  // utiliser pour attendre que les joueurs en cours terminent 

int Joueurs [M*N];  
void* ThreadJoueur (void* num) 
{    	
int i= *((int*) num);
	int E = i / M;   	// l'équipe du joueur
	int J = i %  M;   // joueur J de l'équipe E
       printf("VALEUR num= %d, E= %d, J=%d \n", i, E, J);
	int j=0;
	while (j<2) 
	{   /*1*/ sem_wait(&S[E][J]);    
		printf( "le thread %d de l'equipe %d joue \n",J, E) ; 

		/*2*/   sem_post(&Att);
          j++;
	}
}

int main()
{ 
	int i;
	
	/* 3*/ 
	int j, equipeCourante=0;
	for(i=0; i<N; i++)
		for(j=0; j<M; j++)
		if(i==0)	sem_init(&S[i][j], 0,1);
		else 		sem_init(&S[i][j],0,0);  
	sem_init(&Att,0,0);

	
	pthread_t th[M*N] ;
	for(i=0; i<M*N; i++)    
	{	Joueurs[i] = i;
		pthread_create(&th[i], NULL, ThreadJoueur, (void*) &Joueurs[i]);
	}
	i=0;
	while (i<6)
	{
	/* 4*/
		for(j=0; j<M; j++) sem_wait(&Att);  
	// attendre que les M joueurs en cours finissent de jouer
	 equipeCourante = (equipeCourante+1) % N;
	   		for(j=0; j<M; j++) sem_post(&S[equipeCourante][j]);  
	
	i++;
	}
}

