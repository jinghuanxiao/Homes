#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>


#define DEFAULT_FILE  "/var/run/sigle.pid"
int main(int argc,char *argv[])
{
	int fd = -1;
	char buf[32];
	fd = open(DEFAULT_FILE,O_WRONLY|O_CREAT,0666);
	if(fd < 0){
		perror("fail to open");
		exit(1);
	}
	struct flock lock;
	bzero(&lock,sizeof(lock));
	if(fcntl(fd,F_GETLK,&lock) < 0){

		perror("fail to flock");
		exit(1);
	}
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	if(fcntl(fd,F_SETLK,&lock) < 0){

		perror("fail to flock");
		exit(1);	
	}
	pid_t pid = getpid();
	int len = snprintf(buf,32,"%d\n",(int )pid);
	write (fd,buf,len);
	while( 1 );
	return 0;
}

