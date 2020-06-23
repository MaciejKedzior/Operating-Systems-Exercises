#define _GNU_SOURCE
#include <stdio.h>          // printf, perror
#include <stdlib.h>         // EXIT_FAILURE
#include <fcntl.h>          // open, close, O_CREAT and others flagi
#include <sys/stat.h>       // fstat
#include <sys/mman.h>       // mmap, shm_open, shm_unlink, PROT_READ and others, MAP_SHARED and others, munmap
#include <unistd.h>         // fstat, ftruncate
#include <sys/types.h>      // fstat, ftruncate


int shmCreate(const char* name, int size){
    int temp;
    if ((temp=shm_open(name, O_CREAT | O_RDWR, S_IRWXU)) == -1){
        perror("Creating shared memory object failed: ");
        exit(EXIT_FAILURE);
    }
    printf("Correctly created shared memory descriptor\n");

    if (ftruncate(temp, size) == -1){
        perror("Allocating memory fail: ");
        exit(EXIT_FAILURE);
    }
    printf("Correclty set size of sharad memoty object, size: %d\n", size);
    return temp;
}

int shmOpen(const char* name){
    int temp;
    if ((temp=shm_open(name, O_RDWR, S_IRWXU)) == -1){
        perror("Opening shmem object fail: ");
        exit(EXIT_FAILURE);
    }
    printf("Correctly opened shmem object dz\n");
    return temp;
}

void shmRm(const char* name){
    if (shm_unlink(name) == -1){
        perror("Error removing shmem object: ");
        exit(EXIT_FAILURE);
    }
    printf("Correctly removed shmem object\n");
}

void* shmMap(int fd, int size){
    void* temp;
    if ((temp=mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED){
        perror("Mapping error: ");
        exit(EXIT_FAILURE);
    }
    printf("Correctly created address space mapping of %d size\n", size);
    return temp;
}

void shmClose(void *ptr, int fd, int size){
    if (munmap(ptr, size) == -1){
        perror("Deleting address space mapping error: ");
        exit(EXIT_FAILURE);
    }
    printf("Correctly deleted adress space mapping\n");

    if (close(fd) == -1){
        perror("Descriptor closing fail: ");
        exit(EXIT_FAILURE);
    }
    printf("Correctly closed file descriptor\n");
}


int shmSize(int fd){
    struct stat buf;
    if (fstat(fd, &buf) == -1){
        perror("Reading shmem stats failed: ");
        exit(EXIT_FAILURE);
    }
    printf("Correctly read shmem object size\n");
    return buf.st_size;
}

void shmInfo(int fd){
    struct stat buf;
    if (fstat(fd, &buf) == -1){
        perror("Error reading shmem object data: ");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory data: \n");
    printf("Access mode -> %d\n", buf.st_mode);
    printf("Memory size -> %ld\n", buf.st_size);
    printf("Owner -> %ld\n", buf.st_dev);
}