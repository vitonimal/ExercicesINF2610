#include <stdio.h>
#include <unistd.h>
int main ()
{ printf("main=%p, printf=%p,  sbrk=%p\n",main, printf, sbrk(0));
	return 0;
}
