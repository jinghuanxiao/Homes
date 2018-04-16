#include<iostream>
#include<semaphore.h>
#include<pthread.h>
#include<errno.h>
#include<cstring>
#include <unistd.h>
sem_t semLock;
void *func(void* arg)
{
	sleep(10);
	std::cout<<"func"<<std::endl;
	pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
	pthread_t thread;
	sem_init(&semLock,0,1);
	int ret = pthread_create(&thread,NULL,func,NULL);
	if(ret != 0){
		printf("err =%s",strerror(errno));

	}
	pthread_join(thread,NULL);
	sem_destroy(&semLock);
	return 0;
}

