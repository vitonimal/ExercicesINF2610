#include<stdio.h>
int f( int x)
     { if (x == 1) return 1; 
	else  return x * f(x - 1);
     } 
int main(int argc, char*argv[]) {
	int a = 3; 

      printf(" %d %d\n", f(a), sizeof(int));
     return 0;
}

