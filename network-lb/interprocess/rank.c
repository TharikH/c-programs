#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/msg.h>
#include <sys/shm.h>
#include<string.h>

#define MAX 3
struct student{
    char name[30];
    int mark;
};

void main(){
    struct student *memory;

    key_t key;
    int shmid;

    key=ftok("student.c",5);
    shmid = shmget(key, sizeof(struct student)*MAX, 0666|IPC_CREAT);

    if(shmid == -1){
        printf("error");
        exit(0);
    }
    memory=(struct student *)shmat(shmid,NULL,0);
    // memcpy(memory,class,sizeof(struct student)*MAX);
    printf("name is :%s",memory->name);
    shmdt(memory);

}