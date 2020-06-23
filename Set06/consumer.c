#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "sem.h"
#include "shmem.h"
#include "circbuf.h"


int writeToFile(char* message, int code){
    int write_code;
    if( (write_code=write(code, message, strlen(message))) == -1){
        perror("Writing error");
        exit(EXIT_FAILURE);
    }
    return write_code;
}


int main(int argc, char* argv[]){
    semid       prod_sem, con_sem;
    int         file_descr, i=0, new_file;
    Circular*   shared_mem_object;    
    char        temporary[BUFSIZ];

    signal(SIGTERM, SIG_DFL);
    new_file = open("storage.txt", O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, S_IRWXU);
    
    prod_sem = semOpen(argv[2]);
    con_sem = semOpen(argv[3]);

    file_descr = shmOpen(argv[1]);
    shared_mem_object = shmMap(file_descr, sizeof(Circular));
    
    while (1){
        semP(con_sem);
        temporary[i] = readChar(shared_mem_object);
        if( write(new_file, &temporary[i], 1) == -1){
            perror("Write error: ");
            exit(EXIT_FAILURE);
        }

        i++;
        usleep(10000);
        semV(prod_sem);
    }
    
    
    return 0;
}