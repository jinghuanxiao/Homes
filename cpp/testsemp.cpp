#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

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
        for (int i = 0;i<5;i++) {
			sem_wait(mutex_share);
            printf("mutex_share child i = %d\n", i);
			sem_post(mutex_share);
            usleep(50000);
        }
        

    }
    else {
        
        for (int i = 0;i<5;i++) {
			sem_wait(mutex_share);
            printf("mutex_share parent i = %d\n", i);
			sem_post(mutex_share);
            usleep(50000);
        }
    }
    freeSharedMemory(mutex_share,sizeof(sem_t));
    return 0;
}
