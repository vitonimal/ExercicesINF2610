// programme second.c
#include <stdio.h>
#include <unistd.h>
int main(int argc, char* argv[], char*env[]) {
      printf("ici %s: argc = %d \n", argv[0], argc);
      int i;
      for(i=0; i<argc;i++)
             printf("ici %s:  argv[%d]=%s \n", argv[0],  i, argv[i]);
      for(i=0;env[i]!=NULL;i++)
              printf("ici %s: env[%d]= %s \n", argv[0], i, env[i]);
      _exit(0);
}

