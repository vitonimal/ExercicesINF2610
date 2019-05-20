   #include <unistd.h>
   #include <stdlib.h>
    #include <stdio.h>
    #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
    int fonction() { int i=0; i=i+1; return i;}
    int main(int nargs, char **args) {
   void* brk0 = (void*) sbrk(0);
 // afficher les adresses

      printf("adresse de main   = 0x%08x (zone programme, segment text)\n", main);

      printf("adresse de nargs  = 0x%08x (pile frame 1)\n", &nargs);

      printf("adresse de args   = 0x%08x (pile frame 1)\n", &args);

      printf("sbrk(0) (heap)    = 0x%08x (tas)\n", brk0);
      printf("fonction = 0x%08x\n", &fonction); 
 //  récupérer le contenu /proc/pid/maps du processus
        char buf[128];
        printf("Affichage du fichier /proc/%d/maps\n",getpid());
        sprintf(buf,"/proc/%d/maps",getpid());
        int fd1 = open(buf,O_RDONLY);
        while (read(fd1,buf,128)>0) write(1, buf,128);
        write(1, "\n",2);
        close(fd1);
        return 0;
    }

