#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <pth.h>
static unsigned long long a = 0ULL;
#define MAX 1000000000
void *count(void *arg);
pth_mutex_t mutex;
int main(int argc, char **argv) {
        pth_init();
        pth_t t1, t2;
	char mess[200];
	pth_mutex_init(&mutex);
        t1 = pth_spawn(PTH_ATTR_DEFAULT, count, &a);
        t2 = pth_spawn(PTH_ATTR_DEFAULT, count, &a); 
       // sprintf(mess,"uth %d is going to wait for %d and %d\n\0", pth_self(), t1, t2);
	//pth_write(1,mess, sizeof(mess));
	a=a+1;
	a=a+1;
      	pth_join(t1, NULL);
        pth_join(t2, NULL);
        printf("a=%llu\n", a);
        return EXIT_SUCCESS;
}
void *count(void *arg) {
  volatile unsigned long long*var = (unsigned long long*) arg;
  volatile unsigned long long i, r;
  char mess[100];
//  sprintf(mess,"uth %d is going to sleep for 1s \n", pth_self());
  for (i = 0; i < MAX; i++) 
 {     pth_mutex_acquire(&mutex, 0, NULL);	
	 r = *var;
	 if(i%200000000==0) { sprintf(mess,"uth %d is going to sleep for 1s, r=%d \n", pth_self(),r);
				pth_write (1,mess, sizeof(mess));  pth_sleep(1);} 
	 *var=r+1;
       pth_mutex_release(&mutex);
 }
  return NULL;
}
