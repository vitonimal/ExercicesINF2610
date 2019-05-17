// vm.cpp
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
const int taille=4;
int sg = 0; /* variable globale initialisés */
int ig; /* variable globale non initialis�es */
int sum (int a, int b) 
{ 	int sf = a+b; // variable locale  
	return sf;
}
int main() 
{
  int il;  /* variable locale*/
  int pid=fork();
  if(pid) wait(NULL);
  ig=100;
  for(il=0; il<taille; il++) 
	  sg=sum(sum(il, ig),sg);
  printf(" sg = %d, pid= %d \n", sg,getpid()); 
  // afficher les adresses 
  printf("adresse de taille = 0x%08x, pid=%d\n", &taille, getpid());
 printf("adresse de main = 0x%08x, pid=%d \n", main, getpid());
  printf("adresse de sum = 0x%08x, pid=%d \n", sum, getpid());
 printf("adresse de printf = 0x%08x, pid=%d \n", printf, getpid());
 printf("adresse de getpid = 0x%08x, pid=%d \n", getpid, getpid());

//  récupérer le contendu fichier /proc/pid/maps du process (les sections courantes de son espace virtuel).
 char buf[128];
 printf("Affichage du fichier /proc/%d/maps\n",getpid());
 sprintf(buf,"/proc/%d/maps",getpid());
 int fd = open(buf,O_RDONLY);
 while (read(fd,buf,128)>0) 
 write(1, buf,128);
 write(1, "\n",2);
 close(fd);
 return 0;
}

