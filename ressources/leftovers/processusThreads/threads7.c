// threads7.c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/syscall.h>
//#include <pth.h>
#include "/usr/local/cours/INF2610/pth/include/pth.h"
static unsigned long long a = 0;
#define MAX 1000000000
void *count(void *arg);

int main(int argc, char **argv) {
        pth_init();
        pth_t t1, t2;
        t1 = pth_spawn(PTH_ATTR_DEFAULT, count, &a);
        t2 = pth_spawn(PTH_ATTR_DEFAULT, count, &a); 
        //t1 = npth_create(&t1, NULL, count, &a);
        //t2 = npth_create(&t2, NULL, count, &a);
	pth_join(t1, NULL);
        pth_join(t2, NULL);
        printf("pid=%d, tid=%d,  a=%llu\n", getpid(), syscall(SYS_gettid), a);
        return EXIT_SUCCESS;
}
void *count(void *arg) {
  volatile unsigned long long*var = (unsigned long long*) arg;
  volatile unsigned long long i;
  for (i = 0; i < MAX; i++)
        *var = *var + 1;
   printf("pid=%d, tid=%d, a=%llu\n", getpid(), syscall(SYS_gettid),a);
  return NULL;
}

