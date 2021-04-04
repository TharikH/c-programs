#include<stdio.h>

void main(){
    int arr[]={1,2,3,4,5,6,7,8};
    int start=0,end=7,num=7,flag=0;
    while(start <= end){
        if(arr[start] + arr[end] > num){
            end--;
        }
        else if(arr[start] + arr[end] < num){
            start++;
        }
        else{
            flag=1;
            break;
        }
    }
    if(flag == 0){
        printf("not found");
    }
    else{
        printf("found");
    }
}