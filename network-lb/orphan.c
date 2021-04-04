#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>

  
int main()
{
    // Create a child process      
    pid_t pid = fork();
  
    if (pid > 0)
        printf("in parent process\n");
    else if (pid == 0)
    {
        sleep(5);
        printf("in child process\n");
    }
    return 0;
}
