#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#define N 1000

char buf[N];

void producer(int fd[], int file_descr){
    if (close(fd[0])==-1) { perror("Error closing read descriptor\n"); exit(EXIT_FAILURE); }
    while (read(file_descr, buf, 1) > 0){
        usleep(10000);
        if(write(STDOUT_FILENO, "[Sending]: ", sizeof("[Sending]: ")) == -1){
            perror(""); 
            exit(EXIT_FAILURE);
        }
        if( write(STDOUT_FILENO, buf, 1) == -1){
            perror(""); 
            exit(EXIT_FAILURE);
        }

        if(write(STDOUT_FILENO, "\n", 1)==-1){
            perror(""); 
            exit(EXIT_FAILURE);
        }
        
        if(write(fd[1], buf, 1) == -1) {
            perror(""); 
            exit(EXIT_FAILURE);
        }
        
    }
    if(close(fd[1])==-1) { 
        perror("Error closing write descriptor\n"); 
        exit(EXIT_FAILURE); 
    }
}

void consumer(int fd[], int file_descr){
    if(close(fd[1])==-1) { perror("Error closing write descriptor\n"); exit(EXIT_FAILURE); }
    while (read(fd[0], buf, 1) > 0){
        
        if(write(STDOUT_FILENO, "[Obtains]: ", sizeof("[Obtains]: ")) == -1){
            perror(""); 
            exit(EXIT_FAILURE);
        }
        if(write(STDOUT_FILENO, buf, 1)==-1){
            perror(""); 
            exit(EXIT_FAILURE);
        }

        if(write(STDOUT_FILENO, "\n", 1)==-1){
            perror(""); 
            exit(EXIT_FAILURE);
        }

        if(write(file_descr, buf, 1)==-1){
            perror(""); 
            exit(EXIT_FAILURE);
        }
        usleep(10000);
    }
    if (close(fd[0])==-1) { 
        perror("Error closing read descriptor\n"); 
        exit(EXIT_FAILURE); 
    }
}


int main(int argc, char* argv[]){
    pid_t pid;
    int warehouse, storage;
    int pipefd[2];

    if( 
        ( (warehouse = open("warehouse.txt", O_RDONLY)) == -1 )
            ||
        ( (storage = open("storage.txt", O_RDWR | O_CREAT | O_APPEND, S_IRWXU)) == -1 )
    ){
        perror("OPEN ERROR");
        exit(EXIT_FAILURE);
    }
    else
        printf("Files opened correctly! warehouse=%d\tstorage=%d\n", warehouse, storage);
    

    if(pipe(pipefd) == -1){
        perror("Error creating pipe!\n");
        exit(EXIT_FAILURE);
    }
    
    pid = fork();
    
    if (pid == -1){  
        perror("FORK ERROR!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0){  //parent
        producer(pipefd, warehouse);
        close(warehouse);
        wait(NULL);
        if(system("diff -s storage.txt warehouse.txt")==-1) {perror(""); exit(EXIT_FAILURE);}
        exit(EXIT_SUCCESS);
    }
    else {  //child
        consumer(pipefd, storage);
        close(storage);
        exit(EXIT_SUCCESS);
    }
}