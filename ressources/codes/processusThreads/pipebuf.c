#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int main() {
  int fd[2];
  struct stat stat;
  pipe(fd);
   if ( fstat (fd[0],&stat) == -1) {
   perror ("fstat"); exit (1);
 }
   if (S_ISFIFO (stat.st_mode)) {
   printf ("il s'agit d'un tube \n");
   printf ("num. inode %d \n", (int)stat.st_ino);
   printf ("nbr. de liens %d \n", (int)stat.st_nlink);
   printf ("Taille : %d \n", (int) stat.st_size);
}

  printf("PIPE_BUF=%d\n",PIPE_BUF); //I have to include some header file to make this constant available... But which one?

 int  attributs= fcntl(fd[1], F_GETFL);
  attributs|=O_NONBLOCK;
  fcntl (fd[1],F_SETFL,attributs);
  char c='1'; int cp=0;
  while(write(fd[1], &c,1)>0) cp++;
  printf(" cp=%d\n",cp);
  printf(" page_size=%d \n", getpagesize()); 
  return 0;
}


