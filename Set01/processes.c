#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "procinfo.h"

int child_number=0;

int main(int argc, char* argv[]){
    procinfo(argv[0]);
    for (int i=0; i<3; i++){
        pid_t pid = fork();
        if (pid==-1) { perror("FORK ERROR!\n"); exit(1); };
        if (pid == 0){ child_number=0; procinfo(argv[0]); sleep(5);}
        else { child_number++; sleep(0); }
    }

    for (int i=0; i<child_number; i++) wait(NULL);
    return 0;
}
