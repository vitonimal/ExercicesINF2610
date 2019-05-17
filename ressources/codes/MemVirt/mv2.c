#include<stdio.h>
#include<stdlib.h>
#include <unistd.h> 
int main() {
	printf(" sbrk(0)= %p \n",sbrk(0));
        char *p1=malloc(1024);
        printf(" p1=malloc(1024) =%p, p1+1024=%p, sbbrk(0)=%p \n",p1,p1+1024, sbrk(0));
	char *p2=malloc(2048);
	printf(" p2=malloc(2048) =%p, p2+2048=%p,sbrk(0)=%p \n", p2, p2+2048,sbrk(0));
        char *p3=malloc(3072);
	printf(" p3=malloc(3072) =%p, p3+3072=%p, sbrk(0)=%p  \n", p3, p3+3072, sbrk(0));
        free(p2);
        printf(" free(p2), sbrk(0)=%p \n",sbrk(0));
        p2=malloc(512);
	printf(" p2=malloc(512) =%p, p2+512=%p, sbrk(0)=%p  \n", p2, p2+512, sbrk(0));
	char *p4=malloc(256);
	printf(" p4=malloc(256) =%p, p4+256=%p, sbrk(0)=%p  \n", p4, p4+256, sbrk(0));
        char* p5=malloc(3072);
        printf(" p5=malloc(3072) =%p, p5+3072=%p, sbrk(0)=%p  \n", p5, p5+3072, sbrk(0));
	free(p4);
	printf(" free(p4), sbrk(0)=%p  \n", sbrk(0));
	p4=malloc(31*4096);
        printf(" p4=malloc(31*4096) =%p, p4+31*4096=%p, sbrk(0)=%p  \n", p4, p4+31*4096, sbrk(0));
	char* p6=malloc(512);
       printf(" p6=malloc(512) =%p, p6+512=%p, sbrk(0)=%p  \n", p6, p6+512, sbrk(0));
     return 0;
}

