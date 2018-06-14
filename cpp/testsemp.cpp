#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
class C1
{
public:
void print(int i ){
	sem_wait(mutex1);
    printf("mutex_share child i = %d\n", i);        
	sem_post(mutex1);
	}
sem_t * mutex1;	
};
class C2
{
public:
void print(int i ){
	sem_wait(mutex2);
            printf("mutex_share parent i = %d\n", i);
			sem_post(mutex2);
	}
sem_t * mutex2;	
};


void *createSharedMemory(size_t size) {
    void *addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    if (addr == MAP_FAILED) {
        return NULL;
    }
    return addr;
}

void freeSharedMemory(void *addr, size_t size)
{
    if (munmap(addr, size) == -1) {
        printf("munmap(%p, %d) failed", addr, (int)size);
    }
}

int main(int argc, char *argv[] ) {

    sem_t* mutex_share = (sem_t*)createSharedMemory(sizeof(sem_t));
	
    if (mutex_share == NULL) {
        printf("creat share memory error\n");
        return 0;
    }
    if( sem_init(mutex_share,1,1) < 0) {
      printf("semaphore initilization\n");
      return 0;
    }
    if (fork() == 0) {
		C1 c1;
		c1.mutex1 = mutex_share;
        for (int i = 0;i<5;i++) {
			c1.print();
            usleep(50000);
        }    

    }
    else {
        C2 c2;
		c2.mutex2 = mutex_share;
        for (int i = 0;i<5;i++) {
			c2.print();
            usleep(50000);
        }
    }
    freeSharedMemory(mutex_share,sizeof(sem_t));
    return 0;
}
