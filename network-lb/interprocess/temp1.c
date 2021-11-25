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
    msgrcv(mid,&message,MAX,1,0);
    printf("%s \n",message.buff);
    msgctl(mid,IPC_RMID,NULL);
    return;
}