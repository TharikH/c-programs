#include <stdlib.h>
#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    pid_t child_pid = fork();
  
    // Parent process 
    if (child_pid > 0){
        printf("parent\n");
        sleep(5);
    }
    // Child process
    else{
        printf("child\n");
        exit(0);
    }
    return 0;
}