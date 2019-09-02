// programme first.c
#include <stdio.h>
#include <unistd.h>
int main(int argc, char* argv[], char*env[]) {
      printf("ici first: argc = %d \n", argc);
      int i;
      for(i=0; i<argc;i++)
           printf("ici first: argv[%d]=%s \n", i, argv[i]);
      for(i=0;env[i]!=NULL;i++)
            printf("ici first: env[%d]=%s \n", i, env[i]);
      printf("\nfirst va etre remplacer par second \n"); 
      char *envbis[] = { "maVar=allo", NULL };
     execle("./second", "second", NULL, envbis);
     _exit(0);
}
