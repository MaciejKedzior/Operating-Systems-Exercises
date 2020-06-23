#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(int argc, char* argv[]){
    printf("First comment");
    execl("./child.x", "child.x", NULL);
    printf("Second comment");
    return 0;
}
