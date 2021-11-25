#include<stdio.h>
#include<stdlib.h>


void nfaToDfa(int ** input,int **output,int k,int *check,int m,int n,int pow){
    // int i=0,j=0;
    int val,*temp,count;
    check[1]=1;
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            count=0;
            val=output[i][j];
            printf("%d ",val);
            if(check[val] == 0){
                check[val] = 1;
                output=realloc(output,sizeof(int*) * k+1);
                temp=calloc(n,sizeof(int));
                while(val){
                    if(val % 2 == 1){
                        
                        for (int x = 0; x < n; x++)
                        {
                            temp[x]|=input[count][x];
                        }
                    }
                count++;
                val/=2;
                }
                output[k]=temp;
                k++;
            }
        }
        
    }
    
}
int mthPower(int m){
    int pow=1;
    while(m--){
        pow*=2;
    }
    return pow;
}
void main(){
    int n,m;
    printf("enter number of state and number of symbols :");
    scanf("%d %d",&m,&n);
    int **input=malloc(sizeof(int *) * m),**output=malloc(sizeof(int *)),k=1,pow=mthPower(m);
    int *check=calloc(pow,sizeof(int));
    output[0]=malloc(sizeof(int) * n);
    for (int i = 0; i < m; i++)
    {
        input[i]=malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++)
        {
            scanf("%d",&input[i][j]);
        }
        
    }
    for (int i = 0; i < n; i++)
    {
        output[0][i]=input[0][i];
    }
    nfaToDfa(input,output,k,check,m,n,pow);
    // for (int i = 0; i < m; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%d ",input[i][j]);
    //     }
        
    // }

}