#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "procinfo.h"


pid_t child_pid=0;

int main(int argc, char* argv[]){
    procinfo(argv[0]);
    for (int i=0; i<3; i++){
        pid_t pid = fork();
        if (pid==-1) { perror("FORK ERROR!\n"); exit(1); };
        if (pid == 0){ procinfo(argv[0]); sleep(5); continue;}
        break;
    }
    
    while((child_pid=wait(NULL))>0) printf("Process %d finished!\n", child_pid);
    return 0;
}
