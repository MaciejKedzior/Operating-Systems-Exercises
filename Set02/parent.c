#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "procinfo.h"
#define N 3


pid_t child_pid=0;

int main(int argc, char* argv[]){
    procinfo(argv[0]);
    char* arguments[] = {"child.x", NULL};
    for (int i=0; i<N; i++){
        pid_t pid = fork();
        if (pid==-1) { perror("FORK ERROR!\n"); exit(1); };
        if (pid == 0){ execv("./child.x", arguments); sleep(5);}
        else sleep(0);
    }

    while((child_pid=wait(NULL))>0) printf("Process %d closed!\n", child_pid); 
    return 0;
}
