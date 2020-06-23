#ifndef SERKLIENT_h
#define SERKLIENT_H
#include "msqueue.h"

//Client and server-side functions
char*   createQueueName(pid_t pid);


//Client-side functions:
char*        pidString(pid_t pid);
information*   createMessage(char* pid);
void         errorHandling(char* name, mqd_t queue);

//Server-side functions:
char*   processData(information *data[], int size);
void    clientToken(information*, char*[], int);

#endif