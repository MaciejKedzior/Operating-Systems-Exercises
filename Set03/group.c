#define _POSIX_SOURCE
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "procinfo.h"
#include <sys/wait.h>
#define N 4


int main(int argc, char* argv[]){
    //Checking number of arguments
    if (argc != 3) { printf("Nieodpowiednia liczba argumentow!\n"); exit(EXIT_FAILURE); }
    pid_t pid;
    int pgid, sig_number=atoi(argv[2]);
    procinfo(argv[0]);

    switch (pid=fork()){
        //Fork error handling
        case -1:
            perror("FORK ERROR!\n");
            exit(EXIT_FAILURE);

        //Child process which becomes leader of group
        case 0:
            procinfo(argv[0]);
            setpgid(0, 0);
            for (int i=0; i<N; i++){
                int child_pid = fork();
                if (child_pid == -1){ 
                    printf("FORK ERROR!\n"); 
                    exit(EXIT_FAILURE);
                }
                else if (child_pid == 0) 
                    execl("./handling.x", "handling.x", argv[1], argv[2], NULL); 
                else signal(sig_number, SIG_IGN);
            }
            sleep(5);

            //Printing child processes status
            for (int i=0; i<N; i++){ 
                sleep(3);
                printf("Status: %d\n", wait(NULL));
            }
            exit(EXIT_SUCCESS);

        //Parent process
        default:
            sleep(5);
            pgid = getpgid(pid);
            //Checking whether group of child processes exists
            if (kill(-pgid, 0) == -1){ 
                perror("Can't send signal!\n"); 
                exit(EXIT_FAILURE);
            }
            //Sending signal to the group of child processes
            if(kill(-pgid, sig_number) == -1) { 
                printf("Sending error!\n"); 
                exit(EXIT_FAILURE); 
            }
            else{ 
                wait(NULL); 
                exit(EXIT_SUCCESS); 
            }
    }
    return 0;
}