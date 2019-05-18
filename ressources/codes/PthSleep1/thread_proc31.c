#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <pth.h>
static unsigned long long a = 0;
#define MAX 1000000000
void *count(void *arg);
int main(int argc, char **argv) {
    pth_init();
    pth_t t1, t2;
    t1 = pth_spawn(PTH_ATTR_DEFAULT, count, &a);
    t2 = pth_spawn(PTH_ATTR_DEFAULT, count, &a);
    pth_join(t1,NULL);
    pth_join(t2,NULL);
    printf("a=%llu\n", a);
    return EXIT_SUCCESS;
}
void *count(void *arg) {
    volatile unsigned long long*var = (unsigned long long*) arg;
    volatile unsigned long long i, r;
    char mess[100];
    sprintf(mess,"uth %d is going to sleep for 1s \n", pth_self());
    for (i = 0; i < MAX; i++)
    {
        r = *var;
        if(i%200000000==0)  { 
            printf("mess: %s\n", mess);
            pth_sleep(1);
        }
        *var=r+1;
    
    }
    return NULL;
}
