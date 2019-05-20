#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>        
#include <fcntl.h>   
#include <sys/mman.h>    



int main( ) {

        char   *nom   = "/inf2610shm";
	int     fd = shm_open(nom, O_RDWR, 0644 );
        if(fd==-1) {
                printf("Failed to shm open\n");
                exit(1);
        }
        printf ("Processus %d a ouvert le segment %s\n", getpid(), nom);
        struct stat info;
	fstat(fd, &info);
	off_t taille = info.st_size ;
        char* ptr = (char *) mmap(NULL, taille, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
        close(fd);
	printf ("Processus %d a attache le segment %s a son espace d'adressage :%p \n", getpid(), nom,ptr);
        if(ptr==NULL) exit(1);
	sleep(1);
        printf("Processus %d lit du segment le message  %p", getpid(), ptr); // SEGFAULT HERE
        munmap(ptr,taille);
	shm_unlink(nom);
        exit(0);
}
