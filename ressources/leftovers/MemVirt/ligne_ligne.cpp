#include <stdio.h>
#include <stdlib.h>
int main()
{  char A[512][4096];
   int i,j;
   for(i=0; i<512; i++)
     for(j=0; j<4096; j++)
                A[i][j] = 'A';
   return 0;
}
