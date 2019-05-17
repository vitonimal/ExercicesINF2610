#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/user.h>
#include <unistd.h>
//#include <linux/malloc.h>
int main() {
int*v=(int*)valloc(10);
printf(" v= %p , *v=%d\n", v,*v);

  printf("PIPE_BUF=%d, PAGE_SIZE=%d, FOPEN_MAX=%d\n",PIPE_BUF,PAGE_SIZE,FOPEN_MAX); //I have to include some header file to make this constant available... But which one?
  return 0;
}

