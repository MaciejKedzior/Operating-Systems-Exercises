#define _GNU_SOURCE
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>

typedef sem_t *semid;

semid semCreate(const char *name, int val){
    semid temp = sem_open(name, O_CREAT | O_EXCL, S_IRWXU, val);
    if (temp == SEM_FAILED){
        perror("Creating new semaphore failed.");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Semaphore %s created correctly, its address is %p, and its value is %d!\n", name, temp, val);
        printf("Content of dev/shm folder: \n");
        if (system("cd /; cd dev/shm; ls")==-1){
            perror("error: ");
            exit(EXIT_FAILURE);
        }
        return temp;
    }
}

void semRemove(const char * name){
    if(sem_unlink(name) == -1) {
        perror("Removing semaphore error:");
        exit(EXIT_FAILURE);
    }
    else printf("Semaphore %s removed correctly!\n", name);
}

semid semOpen(const char *name){
    semid temp = sem_open(name, O_CREAT);
    if (temp == SEM_FAILED){
        perror("Opening semaphore failed:");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Correctly opened %s semaphore!\n", name);
        printf("Content of dev/shm folder: \n");
        if (system("cd /; cd dev/shm; ls")==-1){
            perror("error: ");
            exit(EXIT_FAILURE);
        }
        return temp;
    }
}

void semClose(semid sem){
    if (sem_close(sem) == -1){
        perror("Closing semaphore ended with fail:");
        exit(EXIT_FAILURE);
    }
    else printf("Correctly closed %p semaphore\n", sem);
}

void semP(semid sem){
    if(sem_wait(sem)==-1){
        perror("P operation failed!");
        exit(EXIT_FAILURE);
    }
    else printf("Semaphore %p did P operation correctly\n", sem); 
}

void semV(semid sem){
    if(sem_post(sem)==-1){
        perror("V operation failed!");
        exit(EXIT_FAILURE);
    }
    else printf("Semaphore %p did V operation correctly\n", sem);
}

void semInfo(semid sem){
    int state;
    if(sem_getvalue(sem, &state) == -1){
        perror("Error getting info about given semaphore:");
        exit(EXIT_FAILURE);
    }
    else printf("Correctly got value of %p semaphore, here it is: %d\n", sem, state);
}

