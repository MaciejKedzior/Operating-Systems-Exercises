#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "msqueue.h"

//Client and server-side functions
char* createQueueName(pid_t pid){
    int     letter=1;
    char    pid_str[12];
    char*   temp=malloc(12*sizeof(char));
    sprintf(pid_str, "%d", pid);
    temp[0] = '/';
    for (int i=0; i < strlen(pid_str); i++){
        temp[letter] = pid_str[i];
        letter++;
    }
    return temp;
}



//Server-side functions:
void clientToken(information* message, char* words[], size_t size){
    for (int i=0; i<size; i++) words[i] = malloc(12*sizeof(char));
    int i=0;
    char buffer[25];
    strcpy(buffer, message);


    char *token = strtok(buffer, ",");

    while(token){
        strcpy(words[i], token);
        i++;
        token = strtok(NULL, ",");
    }
}


char* processData(char *data[], int size){
    int first_num=atoi(data[1]), second_num=atoi(data[3]);
    double result;
    char sign = data[2][0];
    char *returned_value=malloc(12*sizeof(char));

    switch (sign)
    {
    case '+':
        result = first_num + second_num;
        sprintf(returned_value, "%f", result);
        return returned_value;
    case '-':
        result = first_num - second_num;
        sprintf(returned_value, "%f", result);
        return returned_value;
    case '*':
        result = first_num * second_num;
        sprintf(returned_value, "%f", result);
        return returned_value;
    case '/':
        if (second_num == 0){
            printf("Zero is the second number thus divsion cannot be made");
            return "Nie mozna dzielic przez zero!";
        }
        else{
            result = (double)first_num / (double)second_num;
            sprintf(returned_value, "%f", result);
            return returned_value;
        }
    default:
        printf("there was an error");
        return "error";
    }
}


//Client-side functions:
char* pidString(pid_t pid){
    char *pid_str=malloc(12*sizeof(char));
    sprintf(pid_str, "%d", pid);
    return pid_str;
}


information* createMessage(char* pid){
    char *temp = malloc(43*sizeof(char));
    char buffer[30];
    char  *result;
    int counter=0;

    for (int i=0; i<strlen(pid); i++){
        temp[i]=pid[i]; 
        ++counter; 
    };

    temp[counter] = ',';
    ++counter;

    
    for (int i=1; i<4; i++){
        if (i == 1){
            printf("Write first number: ");
            result = fgets(buffer, 30, stdin);
            if (result == NULL){
                printf("Client program will be finished!\n");
                return "End";
            }
            for (int j=0; j < strlen(result); ++j){
                if (result[j] == '\n') continue;
                temp[counter] = result[j];
                ++counter;
            }
            temp[counter] = ',';
            ++counter;
        }
        if (i == 2){
            printf("Write sign: ");
            result = fgets(buffer, 30, stdin);
            if (result == NULL){
                printf("Client program will be finished!\n");
                return "End";
            }
            for (int j=0; j < strlen(result); ++j){
                if (result[j] == '\n') continue;
                temp[counter] = result[j];
                ++counter;
            }
            temp[counter] = ',';
            ++counter;
        }
        if (i == 3){
            printf("Write second number: ");
            result = fgets(buffer, 30, stdin);
            if (result == NULL){
                printf("Client program will be finished!\n");
                return "End";
            }
            for (int j=0; j < strlen(result); ++j){
                if (result[j] == '\n') continue;
                temp[counter] = result[j];
                ++counter;
            }
        }
    }
    return temp;
}