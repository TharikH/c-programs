#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void initializeOutput(int **output,int m){
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j<m; j++)
        {
            output[i][j]=0;
        }
    }
    
}
void printOutput(int **output,int m){
    for (int i = 1; i < m; i++)
    {
        for (int j = 0; j<i; j++)
        {
            printf("%d ",output[i][j]);
        }
        printf("\n");
    }
}
void markFinalState(int **output,int m,int *finalstate){
    for (int i = 1; i < m; i++)
    {
        for (int j = 0; j<i; j++)
        {
            if(finalstate[i]^finalstate[j]){
                output[i][j]=1;
            }
        }
    }
    // printOutput(output,m);
}
int checked(int **output,int i,int j,int ** input,int n){
    for (int x = 0; x < n; x++)
    {
        if(output[input[i][x]][input[j][x]] == 1 || output[input[j][x]][input[i][x]] == 1){
            return 1;
        }
    }
    return 0;
}
void getState(char *str,int *arr){
    int i=0;
    while(str[i] != '\0'){
        if(str[i] != 'q'){
            arr[str[i] - '0']=1;
        }
        i++;
    }
}
int isFinal(int *finalstate,int *arr,int m){
    for (int i = 0; i < m; i++)
    {
        if(arr[i] == 1 && finalstate[i]==1){
            return 1;
        }
    }
    return 0;
}
void printTransition(int *states,int **input,int m,int n,int *finalstate){
    char output[m][n+1][10],k=0;
    printf("\n");
    for (int i = 0; i < m; i++)
    {
        if(states[i] == -2)continue;
        if(states[i] == -1){
            output[k][0][0]='\0';
            sprintf(output[k][0],"q%d",i);
            // printf("hello -%s %d",output[k][0],i);
            for (int x = 0; x < n; x++)
            {
                sprintf(output[k][x+1],"q%d",input[i][x]);
            }
            k++;
        }else{
            char temp[10];
            int y=0;
            temp[y++]='q';temp[y++]=i+'0';
            for (int j = i+1; j < m; j++)
            {
                if(states[i] == states[j]){
                    temp[y++]='q';
                    temp[y++]=j+'0';
                    states[j]=-2;
                }
            }
            temp[y]='\0';
            // sprintf(output[k][0],"%s",temp);
            strcpy(output[k][0],temp);
            // printf("hello -%s %d",output[0][2],i);
            for (int x = 0; x < n; x++)
            {
                sprintf(output[k][x+1],"q%d",input[i][x]);
            }
            k++;
        }
    }
    char *temp1=malloc(sizeof(char) * 10);
    for (int x = 0; x<k; x++){
    int *arr=calloc(m,sizeof(int));
    strcpy(temp1,output[x][0]);
    getState(temp1,arr);
    if(isFinal(finalstate,arr,m)){
        sprintf(output[x][0],"*%s",temp1);
    }
    for (int i = 0; i < k; i++)
    {
        for (int j = 1; j < n+1; j++)
        {
            if(arr[output[i][j][1] - '0']){
                strcpy(output[i][j],temp1);
            }
        }
        
    }
    free(arr);
    }
    printf("------------------------------\n");
    printf("state\t");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t",i);
    }
    printf("\n");
    printf("------------------------------\n");
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n+1; j++)
        {
            printf("%s\t",output[i][j]);
        }
        printf("\n");
    }
    

}
void mixstate(int **output,int m,int n,int* states){
    int k=0;
    for (int i = 1; i < m; i++)
    {
        for (int j = 0; j<i; j++)
        {
            if(output[i][j] == 0){
                if(states[i] != -1){
                    states[j]=states[i];
                }else if(states[j] != -1){
                    states[i]=states[j];
                }else{
                    states[i]=k;
                    states[j]=k;
                    k++;
                }
            }
        }
    }
}
void myhillNerode(int **output,int m,int **input,int n,int *finalstate){
    int flag=1,*states=malloc(sizeof(int) * m);
    while (flag)
    {
        flag=0;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if(output[i][j] == 0 && checked(output,i,j,input,n)){
                    output[i][j]=1;
                    flag=1;
                }
            }
            
        }
        
    }
    printOutput(output,m);
    for (int i = 0; i < m; i++)
    {
        states[i]=-1;
    }
    
    mixstate(output,m,n,states);
    for (int i = 0; i < m; i++)
    {
        printf("%d ",states[i]);
    }
    
    printTransition(states,input,m,n,finalstate);
}
void addToInput(int **input,char * inputstring,int i,int j){
    if(inputstring[0] == 'q'){
        input[i][j]=inputstring[1] - '0';
    }
}
void main(){
    int m,n;
    // printf("enter number of state and number of symbols :");
    // scanf("%d %d",&m,&n);
    m=6;n=2;
    char *inputstring=malloc(sizeof(char) * 20);
    int **input=malloc(sizeof(int *) * m),*finalstate=malloc(sizeof(int) * m),**output=malloc(sizeof(int *) * m);
    for (int i = 0; i < m; i++)
    {
        // printf("is q%d final state (YES-1,NO-0)",i);
        // scanf("%d",&finalstate[i]);
        input[i]=malloc(sizeof(int) * n);
        output[i]=malloc(sizeof(int) * m);
        for (int j = 0; j < n; j++)
        {
            // printf("q%d on symbol %d goes to:",i,j);
            // scanf("%s",inputstring);
            // addToInput(input,inputstring,i,j);
        }
    }
    input[0][0]=1;input[0][1]=2;input[1][0]=0;input[1][1]=3;input[2][0]=4;input[2][1]=5;input[3][0]=4;
    input[3][1]=5;input[4][0]=3;input[4][1]=5;input[5][0]=5;input[5][1]=5;
    finalstate[0]=0;finalstate[1]=0;finalstate[2]=1;finalstate[3]=1;finalstate[4]=1;finalstate[5]=0;
    initializeOutput(output,m);
    markFinalState(output,m,finalstate);
    myhillNerode(output,m,input,n,finalstate);
    // for (int i = 0; i < m; i++)
    // {
    //     for (int j = 0; j<n; j++)
    //     {
    //         printf("%d ",input[i][j]);
    //     }
        
    // }
    
}