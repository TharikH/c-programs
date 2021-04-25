#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

#define MAX 15
int arr[MAX]={11,7,2,1,9,8,10,78,6,12,99,89,54,0,-9};
void *sort(void * arg){
    int first,last,temp,flag=0;
    if(*(int *)arg == 0){
        first=0;
        last=(MAX)/2;
    }else{
        first=(MAX)/2;
        last=MAX;
    }
        for (int i = first; i < last-1; i++)
        {
            flag=0;
            for (int j = i+1; j < last; j++)
            {
                if(arr[i] > arr[j]){
                    flag=1;
                    temp=arr[i];
                    arr[i]=arr[j];
                    arr[j]=temp;
                }
            }
            if(flag == 0)
                break;
        }
}
void copyArray(int *cpyarr){
    for (int i = 0; i < MAX; ++i)
    {
        cpyarr[i]=arr[i];
    }
    
}
void merge(){
    int cpyarr[MAX],first1=0,last1=MAX/2,first2=MAX/2,last2=MAX,k=0;
    copyArray(cpyarr);
    while(first1<last1 && first2<last2){
        if(cpyarr[first1] <= cpyarr[first2]){
            arr[k]=cpyarr[first1];
            ++first1;
            ++k;
        }else{
            arr[k]=cpyarr[first2];
            ++first2;
            ++k;
        }
    }
    while(first1<last1){
        arr[k]=cpyarr[first1];
            ++first1;
            ++k;
    }
    while(first2<last2){
        arr[k]=cpyarr[first2];
            ++first2;
            ++k;
    }
}
int main(){
    pthread_t pid1,pid2;
    int arg1=0,arg2=1;
    pthread_create(&pid1,NULL,*sort,(void *)&arg1);
    pthread_create(&pid2,NULL,*sort,(void *)&arg2);
    pthread_join(pid1,NULL);
    pthread_join(pid2,NULL);
    merge();
    printf("sorted merged array\n");
    for(int i=0;i<MAX;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 1;
}