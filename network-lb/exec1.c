#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,char* argv[]){
    printf("id of exe1 program is %d\n",getpid());
    char *args[]={"hello","kutta",NULL};
    execvp("./exec2",args);
    printf("back in exec1\n");
    return 0;
}