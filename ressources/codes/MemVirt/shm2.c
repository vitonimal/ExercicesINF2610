// programme shm2.cpp
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
int main ( )
{       int *  adr2;
        int status, cle = 5;
        sleep(1);
        if( (status = shmget(cle, sizeof(int), 0))==-1)
                     exit(1);
	 printf("status = %d \n", status);
        if((adr2 =(int*) shmat(status,NULL,0)) == (int *) -1)
		exit(1);
         printf("adr2 = %p, *adr2 = %d  \n", adr2, *adr2);
        if( shmctl(status, IPC_RMID, NULL) == -1)
        	exit(1);
	exit(0);
}

