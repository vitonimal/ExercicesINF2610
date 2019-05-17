#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <pth.h>
#include <string.h>
static unsigned long long a = 0;
#define MAX 1000000000
void *count(void *arg);
int t3=-1; pth_t t4;
int main(int argc, char **argv) {
    pth_init();
    pth_t t1, t2;
    t1 = pth_spawn(PTH_ATTR_DEFAULT, count, &a);
    t2 = pth_spawn(PTH_ATTR_DEFAULT, count, &a);
    pth_join(t1,NULL);
    printf("a=%llu, uth %d\n", a, pth_self());
    pth_join(t2,NULL);
    //pth_join(t4,NULL));
   
    printf("a=%llu\n", a);
    return EXIT_SUCCESS;
}
void *count(void *arg) {
    volatile unsigned long long*var = (unsigned long long*) arg;
    volatile unsigned long long i, r;
    char mess[100]; pth_t t4; int stop=1;
    if(t3<2) {t3++; t4 = pth_spawn(PTH_ATTR_DEFAULT, count, &a);} else stop=0;
    sprintf(mess,"uth %d is going to sleep for 1s , with t3=%d \n", pth_self(), t3);
    for (i = 0; i < MAX; i++)
    {
        r = *var;
        if(i%500000000==0)  { pth_write(1,mess, strlen(mess)+1);  pth_sleep(1); }
        *var=r+1;
    
     }
     if(stop) pth_join(t4, NULL);
}
