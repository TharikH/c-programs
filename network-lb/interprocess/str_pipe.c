#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#define MAX 100

int countchar(char *str){
    int count=0;
    for(int i=0;str[i]!='\0';i++){
        if(str[i] == '\n')
            continue;
        count++;
    }
    return count;
}
int countWord(char *str){
    int count=0;
    for(int i=0;str[i] != '\0';i++){
        if(str[i] == ' ' || (str[i] == '\n')){
            count++;
        }
    }
    return ++count;
}
int countLines(char *str){
    int count=0;
    for(int i=0;str[i] != '\0';i++){
        if(str[i] == '\n'){
            count++;
        }
    }
    return ++count;
}
void main(){
    char str[MAX];
    printf("enter input :");
    scanf("%[^~]s",str);
    // printf("input :%s:",str);
    int fd1[2],fd2[2];
    pid_t pid;
    if(pipe(fd1) < 0 || pipe(fd2) < 0){
        printf("failed\n");
        exit(0);
    }
    pid=fork();
    if(pid < 0){
        printf("failed\n");
        exit(0);
    }else if(pid > 0){
        close(fd1[0]);
        close(fd2[1]);
        write(fd1[1],str,MAX);
        close(fd1[1]);
        read(fd2[0],str,MAX);
        close(fd2[1]);
        printf("%s\n",str);
        wait(NULL);
    }
    else{
        FILE *f;
        close(fd1[1]);
        close(fd2[0]);
        char str[MAX];
        read(fd1[0],str,MAX);
        close(fd1[0]);
        int char_count,line_count,word_count;

        char_count=countchar(str);
        line_count=countLines(str);
        word_count=countWord(str);

        f=fopen("demo.txt","w");
        fprintf(f,"characters: %d words: %d lines:%d",char_count,word_count,line_count);
        fclose(f);
        f=fopen("demo.txt","r");
        fgets(str,MAX,f);
        write(fd2[1],str,MAX);
        close(fd2[1]);
    }

}