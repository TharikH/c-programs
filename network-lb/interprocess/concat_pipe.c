#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include <sys/wait.h>

#define MAX 30

void main(){
    char buf[MAX],str1[MAX],str2[MAX];
    int fd1[2],fd2[2];
    pid_t pid;
    if(pipe(fd1) < 0 || pipe(fd2) < 0){
        exit(0);
    }
    pid=fork();
    if(pid > 0){
        close(fd1[0]);
        close(fd2[1]);
        printf("enter string :");
        scanf("%s",str1);
        write(fd1[1],str1,MAX);
        close(fd1[1]);
        read(fd2[0],buf,MAX);
        close(fd2[0]);
        printf("concatenated string is %s:\n",buf);
        wait(NULL);
    }else{
        close(fd2[0]);
        close(fd1[1]);
        read(fd1[0],buf,MAX);
        close(fd1[0]);
        printf("enter next string :");
        scanf("%s",str2);
        int len=strlen(buf),i=0;
        while(str2[i] != '\0'){
            // printf("\n%s ---\n",buf);
            buf[len++]=str2[i++];
        }
        buf[len]='\0';
        write(fd2[1],buf,MAX);
        close(fd2[1]);
    }
}