//   http://ilay.org/yann/articles/mem/mem0.html
// memoirevirtuelle.cpp

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
static int i_stat = 4; /* Stocké dans le segment données initialisées */
int  i_glob;  /* Stocké dans le segment bs� */
int *pi_pg;  /* Stocké dans le segment bs� */
int main(int nargs, char **args) 
{   	int *pi_loc;  /* dans la frame 1 de la pile */
	void *sbrk0 =(void *) sbrk(0);  /* l'adresse de base avant le 1er malloc */
	if (!(pi_loc = (int *) malloc(sizeof(int) * 16)))    /* allocation dynamique */
				return 1;
	if (!(pi_pg  = (int *) malloc(sizeof(int) *8))) 
			{ 	free(pi_loc); 
				return 2;
			}
	 // afficher les adresses 

	 printf("adresse de i_stat = 0x%08x (zone programme, segment data)\n", &i_stat);

	printf("adresse de i_glob = 0x%08x (zone programme, segment bss)\n", &i_glob);

	printf("adresse de pi_pg� = 0x%08x (zone programme, segment bss)\n", &pi_pg);

	printf("adresse de main = 0x%08x (zone programme, segment text)\n", main);

	printf("adresse de nargs  = 0x%08x (pile frame 1)\n", &nargs);

	printf("adresse de args = 0x%08x (pile frame 1)\n", &args);

	printf("adresse de pi_loc = 0x%08x (pile frame 1)\n", &pi_loc);

	printf("sbrk(0) (heap) = 0x%08x (tas)\n", sbrk0);

	printf("pi_loc = 0x%08x (tas)\n", pi_loc);

	printf("pi_p  = 0x%08x (tas)\n", pi_pg);

//récupérer le contenu /proc/pid/maps du processus  (les sections courantes de l’espace virtuel du processus pid).

    	char buf[128];
	printf("Affichage du fichier /proc/%d/maps\n",getpid());
	sprintf(buf,"/proc/%d/maps",getpid());
	int fd1 = open(buf,O_RDONLY);
	while (read(fd1,buf,128)>0) 
        	write(1, buf,128);
	write(1, "\n",2);
	close(fd1);
	free(pi_pg);
	free(pi_loc);
	return 0;
	}
