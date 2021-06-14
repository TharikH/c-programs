#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct buf{
    long type;
    char msg[100];
};

void main(){
    struct buf msg1,msg2,msg3;
    key_t key;
    int msgid;

    key=ftok("temp.c",5);

    msgid=msgget(key,0666 | IPC_CREAT);
    
    printf("enter string :");
    scanf("%s",msg1.msg);

    printf("enter priority :");
    scanf("%ld",&msg1.type);

    printf("enter string :");
    scanf("%s",msg2.msg);

    printf("enter priority :");
    scanf("%ld",&msg2.type);

    printf("enter string :");
    scanf("%s",msg3.msg);

    printf("enter priority :");
    scanf("%ld",&msg3.type);
    
    // printf("enter string : ");
    // scanf("%s",message.msg);

    msgsnd(msgid,&msg1,sizeof(struct buf),0);
    msgsnd(msgid,&msg2,sizeof(struct buf),0);
    msgsnd(msgid,&msg3,sizeof(struct buf),0);

    printf("Data send \n");
}