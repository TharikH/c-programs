#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,char *argv[]){
    printf("exec3 is called with pid :%d\n",getpid());
    char *args[]={"hello","world",NULL};
    execv("./exec2",args);
    return 0;
}