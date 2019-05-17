//   http://ilay.org/yann/articles/mem/mem0.html
// memoirevirtuelle.cpp
    #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
const int ci[4]={0,0,0,0};
int ig = 4, jg =5; /* Stocké dans le segment données initialisées */
int  sg; /* Stocké dans le segment bs */
int *psg;  /* Stocké dans le segment bs */
int main(int nargs, char **args) 
{
  int *psl;  /* dans la frame 1 de la pile */
  void *sbrk0 =(void *) sbrk(0); /*l'adresse de base avant le 1er malloc */
  if (!(psl = (int *) malloc(sizeof(int) * 16)))    /* allocation dynamique*/
	return 1;
  if (!(psg  = (int *) malloc(sizeof(int)*8))) 
			{ 	free(psl); 
				return 2;
			}
  // afficher les adresses 
  printf("adresse de ci = 0x%08x (zone programme, segment text)\n", &ci);
 printf("adresse de ig = 0x%08x (zone programme, segment data)\n", &ig);
  printf("adresse de jg = 0x%08x (zone programme, segment data)\n", &jg);
 printf("adresse de sg = 0x%08x (zone programme, segment bss)\n", &sg);
 printf("adresse de psg = 0x%08x (zone programme, segment bss)\n", &psg);
 printf("adresse de main = 0x%08x (zone programme, segment text)\n", main);
 printf("adresse de nargs  = 0x%08x (pile frame 1)\n", &nargs);
 printf("adresse de args  = 0x%08x (pile frame 1)\n", &args);
 printf("adresse de *args  = 0x%08x (pile frame 1)\n", args);
 printf("adresse de psc = 0x%08x (pile frame 1)\n", &psl);
 printf("sbrk(0) (heap) = 0x%08x (tas)\n", sbrk0);
 printf("psl = 0x%08x (tas)\n", psl);
 printf("psg = 0x%08x (tas)\n", psg);
 printf("sbrk(0) (heap) avant sbrk(100) = 0x%08x (tas)\n", sbrk(0));
 sbrk(100); sbrk0= sbrk(0);
 printf("sbrk(0) (heap) apres brk(100) = 0x%08x (tas)\n", sbrk0);
//  récupérer le contenu /proc/pid/maps du process (les sections courantes de l'espace virtuel du processus pid).

 char buf[128];
 printf("Affichage du fichier /proc/%d/maps\n",getpid());
 sprintf(buf,"/proc/%d/maps",getpid());
 int fd1 = open(buf,O_RDONLY);
 while (read(fd1,buf,128)>0) 
 write(1, buf,128);
 write(1, "\n",2);
 close(fd1);
 free(psg);
 free(psl);
 return 0;
}

