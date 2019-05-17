// programme shm1.c
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
int main ( )
{      int *    adr1 ;
        int status, cle = 5;
        if( (status = shmget(cle, sizeof(int), IPC_CREAT | IPC_EXCL | 0600))==-1)
        	exit(1);
	 printf( "status = %d \n", status);
       if((adr1 =(int *) shmat(status,NULL,0)) == (int *)-1)
		exit(1);
     *adr1 = 1190;
    printf("adr1 = %p, *adr1 = %d \n", adr1, *adr1);
	sleep(2);
  	if( shmctl(status, IPC_RMID, NULL) == -1)
      	exit(1);
	exit(0);
}

