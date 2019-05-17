// vm.cpp
    #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
const int ci[4]={0,0,0,0};
int ig = 4, jg =5; /* Stocké dans le segment données initialisées */
int  sg; /* Stocké dans le segment bs */
int sum (int a, int b) { int sf = a+b;  printf("adresse de sf = 0x%08x (zone pile, frame appel a sum)\n", &sf); return sf;}
int main(int nargs, char **args) 
{
  int il, jl=10;  /* dans la frame 1 de la pile */
  for(il=0; il<jl; il++) sg=sum(il, jl);
  // afficher les adresses 
  printf("adresse de ci = 0x%08x (zone programme, segment text)\n", &ci);
 printf("adresse de ig = 0x%08x (zone programme, segment data)\n", &ig);
  printf("adresse de jg = 0x%08x (zone programme, segment data)\n", &jg);
 printf("adresse de sg = 0x%08x (zone programme, segment bss)\n", &sg);
 printf("adresse de main = 0x%08x (zone programme, segment text)\n", main);
 printf("adresse de nargs  = 0x%08x (pile frame 1)\n", &nargs);
 printf("adresse de args  = 0x%08x (pile frame 1)\n", &args);
 printf("adresse de *args  = 0x%08x (pile frame 1)\n", args);
//  récupérer le contenu /proc/pid/maps du process (les sections courantes de l'espace virtuel du processus pid).
 char buf[128];
 printf("Affichage du fichier /proc/%d/maps\n",getpid());
 sprintf(buf,"/proc/%d/maps",getpid());
 int fd1 = open(buf,O_RDONLY);
 while (read(fd1,buf,128)>0) 
 write(1, buf,128);
 write(1, "\n",2);
 close(fd1);
 return 0;
}

