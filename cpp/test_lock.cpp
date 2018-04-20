#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/time.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
void* thread1(void*);
void* thread2(void*);
void* thread3(void*);
int alex=0;
sem_t sem12;
int main()
{
    pthread_t pid1,pid2,pid3;
    int ret=sem_init(&sem12,0,0);
    pthread_create(&pid1,NULL,thread1,NULL);
    pthread_create(&pid2,NULL,thread2,NULL);
    pthread_create(&pid3,NULL,thread3,NULL);
    sleep(100);
    sem_destroy(&sem12);
    printf("--end:\n");
    exit(0);
}
void* thread1(void* arg)
{
    sem_post(&sem12);
    printf("leave thread1\n");
    pthread_exit(0);
}
void* thread2(void* arg)
{
    if(sem_trywait(&sem12)== -1){
        printf("wait thread3\n");
        sem_wait(&sem12);
    }
    sleep(10);
    sem_post(&sem12);
    printf("leave thread2\n");
    pthread_exit(0);
}
void* thread3(void* arg)
{
    if(sem_trywait(&sem12)==-1){

        printf("wait thread2\n");
        sem_wait(&sem12);
    }
    sleep(10);
    sem_post(&sem12);
    printf("leave thread3\n");
    pthread_exit(0);
}
