#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "msqueue.h"
#include "serclient.h"


int main(void){
    char        *name=createQueueName(getpid());        //queue name server->client
    char        *pid=pidString(getpid());               //string-form PID
    mqd_t       msg_comm;                               //message queue object server->client
    mqd_t       msg_server;                             //message queue object server<->client
    


    msg_comm = msgCreate(name, O_RDONLY);
    msgInfo(msg_comm);
    printf("\n");
    
    msg_server = msgOpen(QUEUE_NAME, O_WRONLY);
    msgInfo(msg_server);
    printf("\n\n");

    while(1){
        information   *message;                 //information sent to server
        char           answer[BUFSIZ];          //buffer which holds information sent to server
        
        printf("\n");
        message = createMessage(pid);
        if (strcmp(message, "End") == 0){
            msgClose(msg_comm);
            msgClose(msg_server);
            msgRm(name);
            exit(EXIT_SUCCESS);
        }

        msgSend(msg_server, message);           //sending message to server
        //msgRecv(msg_comm, answer, name);     
        //memset(answer, 0, BUFSIZ);
        msgRecv(msg_comm, answer, name);     //receiving and printing message from server
        memset(answer, 0, BUFSIZ);           //clearing buffer
        free(message);                          //message memory deallocation
    }

    msgClose(msg_comm);                         //closing queue
    msgClose(msg_server);   
    close(msg_comm);
    close(msg_server);
    free(name); free(pid);                      //name, PID memory deallocation
    return 0;
}