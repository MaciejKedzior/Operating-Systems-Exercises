#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "procinfo.h"


void signal_handler(int sig){
    printf("Signal received; its code is: %d\n", sig);
}

int main(int argc, const char* argv[]){
    //Checking if there is correct number of cmd args
    if (argc != 3) { printf("Improper number of args!\n"); exit(EXIT_FAILURE); }

    char method = argv[1][0];
    int sig_number = atoi(argv[2]);
    procinfo(argv[0]);
    switch (method){
        //Default signal handling
        case 'd':
            signal(sig_number, SIG_DFL);
            pause();
            exit(EXIT_SUCCESS);
        //Ignoring signal
        case 'i':
            signal(sig_number, SIG_IGN);
            pause();
            exit(EXIT_SUCCESS);
        //Handling using custom function
        case 'p':
            signal(sig_number, signal_handler);
            pause();
            exit(EXIT_SUCCESS);
        default:
            printf("error!\n");
            exit(EXIT_FAILURE);
    }
    return 0;
}