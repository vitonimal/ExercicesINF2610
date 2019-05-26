#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
int f( int x)
     { if (x == 1) return 1; 
	else  return x * f(x - 1);
     } 
int main() {
	int a = 2; 
      printf("f(%d)=%d \n", a, f(a));
    //récupérer le contenu /proc/pid/maps du process les sections courantes de'espace virtuel du processus pid)).
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

