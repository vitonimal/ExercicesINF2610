#include<unistd.h>
#include <stdlib.h>
#include<stdio.h>
const int s=100;
void affiche_adr (void* x, int psize)
{   long adx = (long)x ;
    long offset = adx % psize ;
    long nump = adx / psize;
    long adp = adx - offset;
   printf("x=%p, adx=0x%lx, nump= %ld, offset =%ld, adp=0x%lx\n", x, adx, nump, offset, adp);
    printf(" siseof int = %ld, size of long = %ld \n", sizeof(int), sizeof(long));
}

int main()
{  int a[s];
   int *p= &a[0], *q=&a[s-1];
   affiche_adr(a, 4096);
   long offset1 = (long)p % 4096;
   long np1 = (long)p / 4096;
    long offset2 = (long)q % 4096;
   long np2 = (long)q / 4096;

  printf("np1= %ld, offset1 =%ld, \n, np2=%ld, offset2=%ld, (long) p - offset1 =%ld \n, (long) q - offset2 =%ld, np1 *4096=%ld , np2 *4096=%ld \n",
          np1, offset1, np2, offset2, (long)p-offset1, (long)q-offset2, np1*4096, np2*4096);
  printf(" (long) p - offset1 =0%lX \n, (long) q - offset2 =0%lX \n", (long) p - offset1, (long) q - offset2);

   exit(0);
}

