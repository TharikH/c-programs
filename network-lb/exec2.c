#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,char *argv[]){
    printf("in exec2 with process id :%d\n",getpid());
    return 0;
}