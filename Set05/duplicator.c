#define _GNU_SOURCEs
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "sem.h"
#include "procinfo.h"


int main(int argc, char* argv[]){
    pid_t   pid;                            //PID holding variable
    int     n=atoi(argv[2]);                //number of created processes
    char*   name="/semafor_powielacz";      //Semaphore name
    semid   semafor;                        //Semaphore descriptor
    int     open_code;                      //File numer.txt descriptor


    if ((open_code=open("numer.txt", O_RDWR | O_CREAT | O_APPEND, S_IRWXU))==-1){
        perror("Error creating text file");
        exit(EXIT_FAILURE);
    }
    else{
        printf("File made properly!");
        if (write(open_code, "0", sizeof("0"))==-1){
            perror("Write error");
            exit(EXIT_FAILURE);
        }
    }
    close(open_code);

    procinfo(argv[0]);
    semafor = semCreate(name, 1);

    for(int i=0; i<n; i++){
        pid = fork();
        if (pid == -1){
            perror("FORK ERROR");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) execl(argv[1], argv[1], name, NULL);
        sleep(5);
    }

    printf("\nNow waiting and closing semaphore\n");
    while(wait(NULL)>0) printf("Waiting for child\n");
    semClose(semafor);
    semRemove(name);
    return 0;
}