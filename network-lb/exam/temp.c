#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX 30

int *sort(int last, int *arr)
{
    int temp, flag = 0;
    for (int i = 0; i < last - 1; i++)
    {
        flag = 0;
        for (int j = i + 1; j < last; j++)
        {
            if (arr[i] > arr[j])
            {
                flag = 1;
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        if (flag == 0)
            break;
    }
    return arr;
}

int main()
{
    int length;
    printf("Enter length :");
    scanf("%d", &length);
    int *arr = malloc(sizeof(int) * length);
    int *ar1 = malloc(sizeof(int) * length/3), *ar2 = malloc(sizeof(int) * length/3), *ar3 = malloc(sizeof(int) * length/3);
    ;
    int *r1=malloc(sizeof(int) * length/3), *r2=malloc(sizeof(int) * length/3), *r3=malloc(sizeof(int) * length/3);
    int *sorted1, *sorted2, *sorted3;
    int i, index1 = 0, index2 = 0, index3 = 0;
    int fd1[2], fd2[2], fd3[2], fd4[2], fd5[2], fd6[2];
    if (pipe(fd1) < 0 || pipe(fd2) < 0 || pipe(fd3) < 0 || pipe(fd4) < 0 || pipe(fd5) < 0 || pipe(fd6) < 0)
    {
        printf("Error in creating pipe!\n");
        return 1;
    }
    pid_t pid1, pid2, pid3;
    pid1 = fork();
    if (pid1 < 0)
        printf("Failed to create child process1!\n");
    else if (pid1 == 0)
    {
        close(fd1[1]);close(fd2[0]);close(fd3[1]);close(fd3[0]);close(fd4[1]);
        close(fd4[0]);close(fd5[0]);close(fd5[1]);close(fd6[0]);close(fd6[1]);
        read(fd1[0], r1, length);
        printf("Child1 read %d from pipe1\n", r1[0]);
                sorted1 = sort(length / 3, r1);
                printf("Child1 read %d from pipe1\n", sorted1[0]);
                write(fd2[1],sorted1,length/3);
    }
    else
    {
        pid2 = fork();
        if (pid2 < 0)
            printf("Failed to create child process2!\n");
        else if (pid2 == 0)
        {
            close(fd1[1]);close(fd2[0]);close(fd3[1]);close(fd1[0]);close(fd2[1]);
            close(fd4[0]);close(fd5[0]);close(fd5[1]);close(fd6[0]);close(fd6[1]);
            read(fd3[0],r2, length/3);
            for (int i = 0; i < length/3; i++)
            {
            printf("test Child2 reads %d\n", r2[i]);    
            }
            
                sorted2 = sort(length / 3, r2);
                write(fd4[1],sorted2,length/3);
        }
        else
        {
            pid3 = fork();
            if (pid3 < 0)
                printf("Failed to create child process3!\n");
            else if (pid3 == 0)
            {
                close(fd1[1]);close(fd2[0]);close(fd3[1]);close(fd3[0]);close(fd4[1]);
                close(fd4[0]);close(fd1[0]);close(fd5[1]);close(fd6[0]);close(fd2[1]);
                read(fd5[0], r3, length/3);
                printf("Child3 read %d from pipe3\n", r3[0]);
                sorted3 = sort(length / 3, r3);
                write(fd6[1],sorted3,length/3);
            }
            else
            {
                // printf("Accepting input from parent process %d",getpid());
                for (i = 0; i < length; i++)
                {
                    int inp;
                    scanf("%d", &inp);
                    arr[i] = inp;
                    if (i % 3 == 0)
                        ar1[index1++] = inp;
                    else if (i % 3 == 1)
                        ar2[index2++] = inp;
                    else
                        ar3[index3++] = inp;
                }
                
                write(fd1[1],ar1,length/3);
                write(fd3[1],ar2,length/3);
                write(fd5[1],ar3,length/3);
                read(fd2[0],ar1,length/3);
                read(fd4[0],ar2,length/3);
                read(fd6[0],ar3,length/3);
                index1=index2=index3=0;
                for (int i = 0; i < length; i++)
                {
                    if (i % 3 == 0)
                        printf("%d ",ar1[index1++]);
                    else if (i % 3 == 1)
                        printf("%d ",ar2[index1++]);
                    else
                        printf("%d ",ar3[index1++]);
                }
                
            }
        }
    }
}