#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
 
int main()
{
    pid_t cpid;
    if (fork()== 0){
        for (int i = 0; i < 5; i++)
        {
           printf("hello from child\n");
        }
        exit(0);
    }
    else
        cpid = wait(NULL);
    printf("Parent pid = %d\n", getpid());
    printf("Child pid = %d\n", cpid);
 
    return 0;
}