#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "procinfo.h"


int main(int argc, char* argv[]){

    procinfo(argv[0]);
    for (int i=0; i<3; i++){
        pid_t pid = fork();
        if (pid==-1) {perror("FORK ERROR!\n"); exit(1); };
        if (pid == 0){  
            procinfo(argv[0]); 
            setpgid(0, 0); 
            sleep(5);
        }
        else sleep(0);
    }
    for (int j=0; j<3;j++) wait(NULL); 
    return 0;
}
