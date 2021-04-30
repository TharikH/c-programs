#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

struct matrix{
    int k;
    int a;
    int b;
    int *arr;
};
void *mul(void *Arg){
    struct matrix *arg=(struct matrix *)Arg;
    int res=arg->a * arg->b;
    arg->arr[arg->k]=res;
}
void main(){
    int r1,r2,c1,c2,**arr1,**arr2,**res,*val;
    printf("enter rows and columns of matrix 1\n");
    scanf("%d %d",&r1,&c1);
    arr1=(int **)malloc(sizeof(int *) * r1);
    for(int i=0;i<r1;i++){
        arr1[i]=(int *)malloc(sizeof(int) * c1);
    }
    printf("enter elements\n");
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c1; j++)
        {
            scanf("%d",&arr1[i][j]);
        }
        
    }
    printf("enter rows and columns\n");
    scanf("%d %d",&r2,&c2);
    if(r2 != c1){
        printf("Multiplication not possible\n");
        exit(0);
    }
    arr2=(int **)malloc(sizeof(int *) * r2);
    for(int i=0;i<r2;i++){
        arr2[i]=(int *)malloc(sizeof(int) * c2);
    }
    printf("enter elements\n");
    for (int i = 0; i < r2; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            scanf("%d",&arr2[i][j]);
        }
    }
    

    res=(int **)malloc(sizeof(int *) * r1);
    for(int i=0;i<r1;i++){
        res[i]=(int *)malloc(sizeof(int) * c2);
    }
    struct matrix **arg=malloc(sizeof(struct matrix *) * c1);
    pthread_t *thread_result=malloc(sizeof(pthread_t) * c1);
    int *data=malloc(sizeof(int) * c1);

    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            for (int k = 0; k < c1; k++)
            {
                arg[k]=malloc(sizeof(struct matrix));
                arg[k]->arr=data;
                arg[k]->a=arr1[i][k];
                arg[k]->b=arr2[k][j];
                arg[k]->k=k;
                pthread_create(&thread_result[k],NULL,*mul,(void *)arg[k]);
            }
            for (int k = 0; k < c1; k++)
            {
                pthread_join(thread_result[k],NULL);
                res[i][j]+=(data[k]);
            }
        }
        
    }
    printf("resultant matrix\n");
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            printf("%d ",res[i][j]);
        }
        printf("\n");
    }
    
}