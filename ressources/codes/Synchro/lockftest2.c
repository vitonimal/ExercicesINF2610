#include <sys/types.h>
 #include <sys/stat.h>
 #include <unistd.h>
 #include <errno.h>
 #include <string.h>
 #include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
int main()
{  int fd,fd2; char c[38]="abcdefghijklmnopqrstuvwxyz0123456789\n";
     fd= open("fich.txt",O_RDWR|O_CREAT, S_IRWXU);
     fd2= open("fich2.txt",O_RDWR|O_CREAT, S_IRWXU);
     write(fd,&c,38);write(fd2,&c,38); 
     close(fd); close(fd2);

   if (fork()==0)
    {   fd= open("fich.txt",O_RDWR);
	fd2= open("fich2.txt",O_RDWR);
        if(lockf(fd,F_LOCK,8)==-1)
        { printf("fils : %s  =>  exit(2)\n", strerror(errno)); exit(2); }
        printf( "fils : verrou sur les octets [0,8[\n");
        write(fd,"xxxxxxxx",8);
	sleep(1);
        if(lseek(fd2, 12, SEEK_SET)==-1) { printf("fils :  lseek  %s =>  exit(3)\n", strerror(errno)); exit(3);}
        if(lockf(fd2,F_LOCK,12)==-1) { printf("fils : %s  =>  exit(4)\n", strerror(errno)); exit(4); }
        printf( "fils : verrou sur les octets [18,28[\n");
       //  lseek(fd,0,SEEK_SET); 
       //  while(read(fd,&x,38)>0) write(1,&x,38);
	// close(fd);
        printf("fils : fin normale \n");
    } else {
        fd= open("fich.txt",O_RDWR);fd2= open("fich2.txt",O_RDWR);
        if(lseek(fd2, 12, SEEK_CUR)==-1) { printf("pere :  lseek  %s => exit(3) \n", strerror(errno)); exit(3); }
        if(lockf(fd2,F_LOCK,8)==-1)
        { printf("parent : %s => exit(4)\n", strerror(errno)); exit(4);}
        printf( "pere : verrou sur les octets [12,24[\n");
        write(fd2,"yyyyyyyy",8); 
	sleep(1);
        if(lseek(fd, 0, SEEK_SET)==-1) { printf("pere : lseek  %s => exit(5)\n", strerror(errno)); exit(5);}
        if(lockf(fd,F_LOCK,5)==-1) { printf("parent :  %s => exit(6) \n", strerror(errno)); exit(6);}
        printf( "pere :  verrou sur les octets [0,5[\n");
        wait(NULL); char x;
        lseek(fd,0,SEEK_SET); 
        while(read(fd,&x,1)>0) write(1,&x,1);
	lseek(fd2,0,SEEK_SET);
        while(read(fd2,&x,1)>0) write(1,&x,1);
       // write(1,"\n",2);
       close(fd);close(fd2);
       unlink("fich.txt");unlink("fich2.txt");
       printf("pere : fin normale \n");
     }

  return 0;
}
