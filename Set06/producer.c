#define _GNU_SOURCE
#include <stdio.h>      //printf, perror
#include <stdlib.h>     //EXIT_FAILURE, malloc
#include <unistd.h>     //read, write, open
#include <fcntl.h>      //flags
#include <string.h>     //strlen
#include <signal.h>
#include <sys/types.h>
#include "sem.h"
#include "shmem.h"
#include "circbuf.h"


char* readFromFile(char* path){
    int open_code = open(path, O_RDONLY), read_code, i=0;
    char* text = malloc(BUFSIZ * sizeof(char));
    char* letter = malloc(sizeof(char));

    while((read_code=read(open_code, letter, 1)) > 0){
        text[i] = *letter;
        i++;
    }
    free(letter);
    close(open_code);
    return text;
}


int main(int argc, char* argv[]){
    semid       prod_sem, con_sem;
    int         file_descr;
    Circular*   shared_mem_object;    
    char*       temporary;


    temporary = readFromFile("warehouse.txt");
    
    prod_sem = semOpen(argv[2]);
    con_sem = semOpen(argv[3]);

    file_descr = shmOpen(argv[1]);
    shared_mem_object = shmMap(file_descr, sizeof(Circular));

    for (int iter=0; iter < strlen(temporary); iter++){
        char temp = temporary[iter];

        semP(prod_sem);
        writeChar(shared_mem_object, temp);
        usleep(10000);
        semV(con_sem);
    }

    sleep(5);

    if (kill(0,0) == -1){
        perror("Kill test error: ");
        exit(EXIT_FAILURE);
    }
    if (kill(0, SIGTERM)==-1){
        perror("Signal sending error: ");
        exit(EXIT_FAILURE);
    }

    free(temporary);
    return 0;
}