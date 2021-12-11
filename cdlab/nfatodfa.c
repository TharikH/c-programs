#include<stdio.h>
#include<stdlib.h>


int convertToDec(int *inp,int m){
    int mul=2,val=0;
    for (int i = m-1; i >= 0; i--)
    {
        val=val*mul+inp[i];
    }
    return val;

}
void print(int **output,int m,int n,int k,int *finalstate){
    printf("OUTPUT\n");
    int val,count,flag,x,final;
    char str[10];
    // for(int i=0;i<n+1;i++){
    //     printf("%s ",)
    // }
    for (int i = 0; i < 16; i++)
    {
        printf("--");
    }
    printf("\n");
    printf("State\t");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t",i);
    }
    printf("\n");
    for (int i = 0; i < 20; i++)
    {
        printf("--");
    }
    printf("\n");
    for(int i=0;i<k;i++){
        // printf("q%d ",)
        for(int j=0;j<n+1;j++){
            // printf("%d ",output[i][j]);
            val=output[i][j];
            flag=0;
            count=0;
            final=0;
            x=0;
            while(val){
                if(val % 2 == 1){
                    flag=1;
                    str[x++]='q';
                    str[x++]='0' + count;
                    if(finalstate[count] == 1 && j==0){
                        final=1;
                    }
                }
                count++;
                val/=2;
            }
            if(flag == 0){
                str[x++]='D';
            }
            str[x]='\0';
            if(final == 1){
                printf("*%s\t",str);
            }
            else{
                printf("%s\t",str);
            }
        }
        printf("\n");
    }
}
void nfaToDfa(int ** input,int **output,int k,int *check,int m,int n,int pow,int * finalstate){
    int val,*temp,count,tempval;
    check[1]=1;
    output[0][0]=1;
    for (int i = 0; i < k; i++)
    {
        for (int j = 1; j < n+1; j++)
        {
            count=0;
            val=output[i][j];
            tempval=val;
            if(check[val] == 0){
                check[val] = 1;
                output=realloc(output,sizeof(int*) * k+1);
                temp=calloc(n+1,sizeof(int));
                while(val){
                    if(val % 2 == 1){
                       
                        for (int x = 1; x < n+1 ; x++)
                        {
                            temp[x]|=input[count][x-1];
                        }
                    }
                count++;
                val/=2;
                }
                temp[0]=tempval;
                output[k]=temp;
                k++;
            }
        }
       
    }
    print(output,m,n,k,finalstate);
   
}
int mthPower(int m){
    int pow=1;
    while(m--){
        pow*=2;
    }
    return pow;
}
void clearUI(int *input,int m){
    for (int i = 0; i < m; i++)
    {
        input[i]=0;
    }
    
}
void preProcessInput(int *arr,char *string,int m){
    int i=0;
    while(string[i] != '\0'){
    if(string[i] != 'q' && string[i] != 'N'){
            arr[string[i] - '0']=1;
        }
        i++;
    }
}
void main(){
    int n,m;
    printf("enter number of state and number of symbols :");
    scanf("%d %d",&m,&n);
    char *inputstring=malloc(sizeof(char) * 20);
    int **input=malloc(sizeof(int *) * m),**output=malloc(sizeof(int *)),k=1,pow=mthPower(m);
    int *check=calloc(pow,sizeof(int)),*ui_input=malloc(sizeof(int) * m),*finalstate=malloc(sizeof(int) * m);
    output[0]=malloc(sizeof(int) * (n+1));
    for (int i = 0; i < m; i++)
    {
        input[i]=malloc(sizeof(int) * n);
        printf("is q%d final state (YES-1,NO-0)",i);
        scanf("%d",&finalstate[i]);
        for (int j = 0; j < n; j++)
        {
            printf("q%d on symbol %d goes to:",i,j);
            scanf("%s",inputstring);
            clearUI(ui_input,m);
            preProcessInput(ui_input,inputstring,m);
            input[i][j]=convertToDec(ui_input,m);
        }
       
    }
    for (int i = 1; i < n+1; i++)
    {
        output[0][i]=input[0][i-1];
    }
    nfaToDfa(input,output,k,check,m,n,pow,finalstate);

}
