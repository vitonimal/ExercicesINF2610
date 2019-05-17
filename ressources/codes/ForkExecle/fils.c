// programme fils.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> // pour exit
int main(int argc, char* argv[], char*env[]) {
    
      printf("ici fils, argc = %d \n", argc);
      int i;
      for(i=0; i<argc;i++)
	     printf("ici fils argv[%d]=%s \n", i, argv[i]);
      for(i=0;env[i]!=NULL;i++)
	      printf("ici fils env[%d]=%s \n", i, env[i]);
      	printf("ici fils getenv(PWD)=%s\n", getenv("PWD"));
        exit(0);
}

