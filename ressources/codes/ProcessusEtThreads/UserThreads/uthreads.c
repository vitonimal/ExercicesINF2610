#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pth.h>
static unsigned long long a = 0;
#define MAX 1000000000

void* count(void *arg) {
    volatile unsigned long long*var = (unsigned long long*) arg;
    volatile unsigned long long i;
    for (i = 0; i < MAX; i++) {
        *var = *var + 1;
    }
    return NULL;
}

int main( ) {
    pth_t t1, t2;
    
    pth_init();
    
    t1=pth_spawn(PTH_ATTR_DEFAULT,count, &a);
    t2=pth_spawn(PTH_ATTR_DEFAULT,count, &a);

    pth_join(t1,NULL);
    pth_join(t2,NULL);
    
    printf("pid= %d a=%llu\n", getpid(), a); 
    
    return 0;
} 
