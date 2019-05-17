 #include <fcntl.h>
 #include <stdio.h>
 #include <stdlib.h> 
 #include <unistd.h>
 #include <sys/stat.h>
 #include <sys/mman.h>
 #include <signal.h>
 #include <setjmp.h>
int segv = 0;
jmp_buf jbuf;

void action(int sig) { segv=1; printf("\n");}

static void handler(int sig, siginfo_t *si, void *c)
{
  //  ucontext_t * context = c;
    printf("Got SIGSEGV at address: 0x%lx\n",(long) si->si_addr);
    segv=1;
  //  longjmp(jbuf, 1);
    //exit(EXIT_FAILURE);
}

 int main() {
 
 int    i,r;
 // signal(SIGSEGV,action);
 // signal(SIGBUS,action);


  struct sigaction sa;

    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = handler;
    if (sigaction(SIGSEGV, &sa, NULL) == -1)
        { printf("error in sigaction"); return -1; }


char * seg =(char *) mmap(NULL, 1, PROT_READ |PROT_WRITE,  MAP_ANONYMOUS| MAP_SHARED, -1, 0);
printf("...seg= %p ...\n",seg);

// char * seg2 =(char *) mmap(NULL, 1, PROT_READ |PROT_WRITE,  MAP_ANONYMOUS| MAP_SHARED, -1, 0);
// printf("...seg2= %p, seg-seg2=%lu ...\n",seg2, seg-seg2);

seg[0]='A'; 
//r=setjmp(jbuf,1);
for (i=0; segv==0 && r==0 ; i++)
	  if(i<1) {  seg[i]='X'; printf("seg[%d]=%c ",i,seg[i]);}
          else { kill(getpid(),SIGSEGV); break;}

     printf("fin normale \n");
 return 0;
}

