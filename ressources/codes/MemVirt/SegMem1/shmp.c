#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>        
#include <fcntl.h>       
#include <unistd.h>
#include <string.h>


int main( ) {

	off_t   taille = 4096;
	char   *nom   = "/inf2610shm";
	int     fd = shm_open(nom, O_RDWR|O_CREAT, 0600 );
        
	if(fd==-1) exit(1);
	printf ("Processus %d : a cree  ou ouvert un segment\n", getpid());
	ftruncate(fd, taille);
	char *ptr = (char *) mmap(NULL, taille, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if(ptr==NULL) exit(1);
	close(fd);
	printf("Processus %d : a attache le segment %s  a son espace d'adressage: %p\n", getpid(), nom, ptr);
	char msg[100]; 
        sprintf(msg, "bonjour du processus %d\n",getpid());
        printf("Processus %d ecrit dans le segment le message %s\n", getpid(),msg);
	strcpy((char*)ptr,msg);
	munmap(ptr,taille);
	exit(0);
}
