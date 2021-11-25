#include<stdio.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MAX 100
struct msg{
    long type;
    char buff[100];
}message;
void main(){
    strcpy(message.buff,"heelo");
    key_t key =ftok("./temp2.c",1);
    int mid=msgget(key,0666 | IPC_CREAT);
    message.type=1;
    msgsnd(mid,&message,MAX,0);
    return;
}