#include<stdio.h>

int fib(int *arr,int n){
    int temp;
    if(arr[n-1] != -1){
        return arr[n-1];
    }
    if(n <= 2){
        arr[n-1]=1;
        return 1;
    }else{
        temp=fib(arr,n-1) + fib(arr,n-2);
        arr[n-1]=temp;
        return temp;
    }
}
void main(){
    int n;
    scanf("%d",&n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        arr[i]=-1;
    }
    
    printf("%d\n",fib(arr,n));
}