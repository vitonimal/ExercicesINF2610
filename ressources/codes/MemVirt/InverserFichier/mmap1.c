 #include <fcntl.h>
 #include <stdio.h>
 #include <stdlib.h> 
 #include <unistd.h>
 #include <sys/stat.h>
 #include <sys/mman.h>

 int main(int argc, char *argv[]) {
 char   *projection;
 int    fichier;
 struct stat etat_fichier;
 long   taille_fichier;
 int    i;
 char   tmp;

 if(argc != 2) {
     printf("Syntaxe: %s fichier_a_inverser\n",argv[0]);
     exit(1);
 }
 printf("argv[1]=%s \n", argv[1]);
 fichier = open(argv[1],O_RDWR);
 if(fichier==-1) exit(1); 
 stat(argv[1], &etat_fichier);

 taille_fichier = etat_fichier.st_size;
 projection = (char *) mmap(NULL, taille_fichier,
                            PROT_READ | PROT_WRITE,
                            MAP_SHARED, fichier, 0);
 if(projection == (char *) MAP_FAILED) {
      perror("mmap");
      exit(0);
    }
 close(fichier);

 for(i=0; i<taille_fichier/2; i++) {
    tmp = projection[i];
    projection[i] = projection[taille_fichier - i -1];
    projection[taille_fichier - i -1] = tmp;
 }
 munmap((void *) projection, taille_fichier);
 printf("fin\n");
 return 0;
}

