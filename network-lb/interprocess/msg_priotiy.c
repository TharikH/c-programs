#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct buf{
    long type;
    char msg[100];
};

void main(){
    struct buf message1,message2;
    key_t key;
    int msgid;

    key=ftok("msg_send_pal.c",5);

    msgid=msgget(key,0666 | IPC_CREAT);
    message1.type=1;
    message2.type=2;
    printf("enter string : ");
    scanf("%s",message1.msg);
    scanf("%s",message2.msg);

    msgsnd(msgid,&message1,sizeof(message1),1);
    msgsnd(msgid,&message2,sizeof(message2),2);

    printf("Data send \n");
}