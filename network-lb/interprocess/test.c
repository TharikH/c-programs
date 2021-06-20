#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

#define MAX 30
void main(){
    int fd[2];
    char buf[MAX];
    pid_t pid;
    if(pipe(fd) == -1){
        exit(0);
    }
    pid=fork();
    if (pid == -1)exit(0);
    if(pid > 0){
        strcpy(buf,"hello");
        write(fd[1],buf,MAX);
        close(fd[1]);
        wait(NULL);
        read(fd[0],buf,MAX);
        close(fd[0]);
        printf("%s\n",buf);
    }
    else{
        read(fd[0],buf,MAX);
        close(fd[0]);
        strcat(buf,"world");
        write(fd[1],buf,MAX);
        close(fd[1]);

    }

}