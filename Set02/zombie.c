#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "procinfo.h"


int main(int argc, char* argv[]){
    procinfo(argv[0]);
    pid_t pid = fork();
    if (pid==-1) { perror("FORK ERROR!\n"); exit(1); }
    if (pid==0) { procinfo(argv[0]); exit(0); }
    else{
        sleep(1);
        printf("%d\n", system("watch -n 1 \"ps -HFC zombi.x\""));
    }
    return 0;
}