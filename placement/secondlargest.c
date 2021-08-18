#include<stdio.h>
#include<stdlib.h>

void main(int arg_count,char **args){
    int n=atoi(args[1]),large,s_large;
    int *arr=malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        arr[i]=atoi(args[i+2]);
    }
    large=s_large=arr[0];
    for (int i = 0; i < n; i++)
    {
        if(arr[i] > large){
            s_large=large;
            large=arr[i];
        }else if(arr[i] > s_large){
            s_large=arr[i];
        }
    }
    printf("%d\n",s_large);
    
}