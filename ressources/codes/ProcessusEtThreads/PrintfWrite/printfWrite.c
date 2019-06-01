#include <unistd.h>             /* pour write */
#include <stdio.h>              /* pour printf */
int main( ) {
   printf(" ici 1er printf ");
   write(1," ici 1er write ",16);
   printf(" ici 2eme printf ");
   write(1," ici 2eme write \n", 17);
   fflush(stdout);
  // fork(); 
   //printf("11111111111111111111111111111111111111111111111111111111111111111");  printf("222222222222222222222222222222222222222222222222222"); 
   //write(1, " ici 3eme write \n",18); printf("\n");
   return 0;
}  
