#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include "msqueue.h"
#include "serclient.h"


volatile sig_atomic_t stop;

void sig_handler(int signum){
    stop = 1;
}


int main(void){                                             
    mqd_t   msg_receiving;                     //Message queue object server <-> client
    char    answer[BUFSIZ];                    //temporary buffer

    msg_receiving=msgCreate(QUEUE_NAME, O_RDONLY);
    signal(SIGINT, sig_handler);                            
    msgInfo(msg_receiving);                    //Printing info about shared queue
    printf("\n\n");


    while(!stop){
        information   *tokenized[4];           //Array: [0]-PID [1]-number [2]-sign [3]-number
        information   *send_to_client;         //Information ready to be sent to the client
        char          *pid_name;               //Single client queue name /PID
        mqd_t         queue_serv;              //Queue object serwer -> klient

        printf("\n");
        msgRecv(msg_receiving, answer, QUEUE_NAME);       //receiving message from shared queue


        clientToken(answer, tokenized, 4);                //Information tokenizing
        memset(answer, 0, BUFSIZ);                        //Clearing buffer


        pid_name = createQueueName(atoi(tokenized[0]));
        queue_serv = msgCreate(pid_name, O_WRONLY);

        send_to_client = processData(tokenized, 4);
        msgSend(queue_serv, send_to_client);

        for (int i=0; i<4; i++) free(tokenized[i]);         //Deallocating memory for information
        sleep(1);
        
        msgClose(queue_serv);
        close(queue_serv);
        msgRm(pid_name);
        printf("\n");
    }
    
    return 0;
}