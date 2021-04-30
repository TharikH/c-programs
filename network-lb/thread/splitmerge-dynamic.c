#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

struct Arr{
    int first;
    int last;
    int *arr;
};
void *sort(void * Arg){
    struct Arr *arg=(struct Arr *)Arg;
    int temp,flag=0,first=arg->first,last=arg->last,*arr=arg->arr;
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
void copyArray(int *cpyarr,int *arr,int len){
    for (int i = 0; i < len; ++i)
    {
        cpyarr[i]=arr[i];
    }
}
void merge(int *arr,int max){
    int cpyarr[max],first1=0,last1=max/2,first2=max/2,last2=max,k=0;
    copyArray(cpyarr,arr,max);
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
    struct Arr *arg1=malloc(sizeof(struct Arr)),*arg2=malloc(sizeof(struct Arr));
    int max,*arr;
    
    printf("enter number of elements \n");
    scanf("%d",&max);
    arr=malloc(sizeof(int) * max);
    for (int i = 0; i < max; i++)
    {
        scanf("%d",&arr[i]);
    }
    
    arg1->first=0;
    arg2->first=max/2;
    arg1->last=max/2;
    arg2->last=max;

    arg1->arr=arr;
    arg2->arr=arr;

    pthread_create(&pid1,NULL,*sort,(void *)arg1);
    pthread_create(&pid2,NULL,*sort,(void *)arg2);
    pthread_join(pid1,NULL);
    pthread_join(pid2,NULL);
    merge(arr,max);
    printf("sorted merged array\n");
    for(int i=0;i<max;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 1;
}