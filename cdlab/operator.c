#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define CHARLENGTH 20

#define MAX 20
char stack[MAX];
int top = -1;

void push(char value){
    if(top == MAX - 1){
        printf("underflow");
    }else{
        stack[++top] = value;
    }
}
char pop(){
    char temp ='\0';
    if(top == -1){
        printf("underflow");
    }else{
        temp=stack[top];
        stack[top] = '\0';
        top--;
    }
    return temp;
}


int isPresent(char *arr,char value,int n){
    for (int i = 0; i < n; i++)
    {
        // printf("---%c-%c--- ",arr[i],value);
        if(arr[i] == value){
            
            return 1;
        }
    }
    return 0;
}
int getIndex(char value,char *arr,int count){
    for (int i = 0; i < count; i++)
    {
        if(arr[i] == value){
            return i;
        }
    }
    return -1;
}
void addToarr(char *arr,int value){
    int i=0;
    while(arr[i] != '\0'){
        if(arr[i] == value){
            return;
        }
        i++;
    }
    arr[i++]=value;
    arr[i]='\0';
}
void copyArray(char *dest,char *src){
    int i=0,j=0;
    while (src[i] != '\0')
    {
        j=0;
        while (dest[j] != '\0')
        {
            if(dest[j] == src[i]){
                break;
            }
            j++;
        }
        if(dest[j] == '\0'){
            dest[j++] = src[i];
            dest[j] = '\0';
        }
        i++;
    }
    
}
void findLeading(char *terminals,char *nonterminals,char **productions,int m,int n,int num,char ** leading){
    char *ptr;
    int index,tempindex;
    for (int i = 0; i < num; i++)
    {
        ptr=productions[i]+3;
        index=getIndex(productions[i][0],nonterminals,m);
        // printf("%s %d   ",ptr,isPresent(terminals,ptr[0],n));
        if(isPresent(terminals,ptr[0],n)){
            addToarr(leading[index],ptr[0]);
        }
        else{
            if(ptr[1] != '\0'){
                addToarr(leading[index],ptr[1]);
            }
            tempindex=getIndex(ptr[0],nonterminals,m);
            // printf("%d %d",tempindex,index);
            if(tempindex != index)
                copyArray(leading[index],leading[tempindex]);
        }
    }
    
}
void findTrailing(char *terminals,char *nonterminals,char **productions,int m,int n,int num,char **trailing){
    char *ptr;
    int index,tempindex,len;
    for (int i = 0; i < num; i++)
    {
        ptr=productions[i]+3;
        len=strlen(ptr);
        index=getIndex(productions[i][0],nonterminals,m);
        // printf("%c %d",ptr[len - 1],isPresent(terminals,ptr[len - 1],n));
        if(isPresent(terminals,ptr[len - 1],n)){
            addToarr(trailing[index],ptr[len - 1]);
        }else{
            if(len > 2){
                addToarr(trailing[index],ptr[len - 2]);
            }
            
            tempindex=getIndex(ptr[len - 1],nonterminals,m);
            if(tempindex != index)copyArray(trailing[index],trailing[tempindex]);
        }
    }
}
void initializeTable(char **table,char *terminal,char *nonterminal,int n){
    int i=0,j=0;
    table[0][0]='\\';
    table[0][1] = '$';table[1][0] = '$';
    for (i = 2; i < n+2; i++)
    {
        table[i][0] = terminal[i-2];
        table[0][i] = terminal[i-2];
    }
    // for (i=n+2; i < n+m+2; i++)
    // {
    //     table[i][0] = nonterminal[i-n-2];
    //     table[0][i] = nonterminal[i-n-2];
    // }
    for (int i = 1; i < n+2; i++)
    {
        for (int j = 1; j < n+2; j++)
        {
            table[i][j] = '-';
        }
        
    }
    
}
int getTableIndex(char ** table,char value,int n){
    for (int i = 1; i < n+2; i++)
    {
        if(table[0][i] == value){
            return i;
        }
    }
    return -1;
}
void putSymbolOnTable(char **table,char *arr,char op,char symbol,int n,int l){
    int index1,index2,i=0;
    index1=getTableIndex(table,symbol,n);
    while(arr[i] != '\0')
    {
        index2=getTableIndex(table,arr[i],n);
        // printf("%d ",index1);
        if(l)table[index1][index2]=op;
        else table[index2][index1]=op;

        i++;
    }
    
}
void constructRelationTable(char ** table,char *terminals,char *nonterminals,char **production,char **leading,char **trailing,int m,int n,int num){
    int j=0,index1,index2;
    char *ptr,x1,x2,x3;

    initializeTable(table,terminals,nonterminals,n);

    putSymbolOnTable(table,leading[0],'<','$',n,1);
    putSymbolOnTable(table,trailing[0],'>','$',n,0);
    for (int i = 0; i < num; i++)
    {
        j=0;
        ptr=production[i]+3;
        while(ptr[j] != '\0'){
            x1=ptr[j];
            x2=ptr[j+1];
            if(isPresent(terminals,x1,n) && isPresent(terminals,x2,n)){
                index1=getTableIndex(table,x1,n);
                index2=getTableIndex(table,x2,n);
                table[index1][index2] = '=';
            }
            if(x2 != '\0' && isPresent(terminals,x1,n) &&  isPresent(terminals,ptr[j+2],n) && isPresent(nonterminals,x2,m)){
                index1=getTableIndex(table,x1,n);
                index2=getTableIndex(table,ptr[j+2],n);
                table[index1][index2] = '=';
            }
            if(isPresent(terminals,x1,n) && isPresent(nonterminals,x2,m)){
                index1 = getIndex(x2,nonterminals,m);
                putSymbolOnTable(table,leading[index1],'<',x1,n,1);
            }
            if(isPresent(nonterminals,x1,m) && isPresent(terminals,x2,n)){
                index1 = getIndex(x1,nonterminals,m);
                putSymbolOnTable(table,trailing[index1],'>',x2,n,0);
            }
            j++;
        }
    }
    for (int i = 0; i < n+2; i++)
    {
        for (int j = 0; j < n+2; j++)
        {
            printf("%c   ",table[i][j]);
        }
        printf("\n");
    }
}
int findIndexOfHandle(char ** production,int num,char *handle){
    int i=0,j,len=strlen(handle);
    char *prod;
    for (int i = 0; i < num; i++)
    {
        prod=production[i]+3;
        j=0;
        while(prod[j] != '\0'){
            // printf(" == %d %d\n",top,len);
            if(handle[len  - j - 1] == prod[j]){
                j++;
            }else{
                break;
            }
        }
        if(prod[j] == '\0'){
            return i;
        }
    }
    return -1;
}
int isReducible(char ** production,int num){
    char *prod;
    int j=0,flag,len,max=-1;
    for (int i = 0; i < num; i++)
    {
        prod=production[i]+3;
        j=0;
        flag = 0;
        len = strlen(prod);
        while(prod[j] != '\0'){
            // printf(" == %d %d\n",top,len);
            if(stack[top -  len +j+1] == prod[j]){
                j++;
            }else{
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            // printf("%s -- %s\n",production[i],stack);
            if(max == -1 || strlen(production[max]) < strlen(production[i])){
                max=i;
            }
        }
    }
    return max;
}
void reduce(char **production,int num,char *input){
    int len,index;
    char temp;
    index=isReducible(production,num);
    if(index > -1){
        len=strlen(production[index] + 3);
        while(len--){
            temp = pop();
        }
        push(production[index][0]);
        printf("reduce %s\n",production[index]);
        printf("%s\t%s\t",stack,input);
        if(input[0] == '$' && stack[0] == '$' && stack[1] == production[0][0] && stack[2] == '\0'){
            return;
        }
        reduce(production,num,input);
        
    }
}
void parseInput(char **table,char *input,int n,char **production,int num,char *nonterminals,int m){
    int i=0,index1,index2,k,index=0,temp;
    char handle[CHARLENGTH];
    push('$');
    printf("%s\t%s\t",stack,input);
    while(1){
        index1 = getTableIndex(table,stack[top],n);
        index2 = getTableIndex(table,input[i],n);
        if(index1 == -1)goto L1;
        if(table[index1][index2] == '-'){
            printf("rejected\n");
            exit(0);
        }else if(table[index1][index2] == '<' || table[index1][index2] == '='){
            L1:
            printf("shift\n");
            push(input[i]);
            i++;
            printf("%s\t%s\t",stack,input+i);
        }
        else{
            k=0;
            handle[k]=pop();
            temp=top;
            while(isPresent(nonterminals,stack[temp],m))temp--;
            index1=getTableIndex(table,stack[temp],n);
            index2 =getTableIndex(table,handle[k],n);
            while(table[index1][index2] != '<' ){
                while(top - temp + 1 != 0){
                    handle[++k]=pop();
                }
                temp=top;
                while(isPresent(nonterminals,stack[temp],m))temp--;
                index1 = getTableIndex(table,stack[temp],n);
                index2 = getTableIndex(table,handle[k],n);
            }
            handle[++k]='\0';
            // printf("== %s ===",handle);
            index = findIndexOfHandle(production,num,handle);
            // printf("== %d ===",index);
            if(index == -1){
                printf("rejected\n");
                exit(0);
            }
            // printf("=== %s\n",handle);
            printf("reduce by %s\n",production[index]);;
            push(production[index][0]);
            printf("%s\t%s\t",stack,input+i);
            if(input[i] == '$' && stack[0] == '$' && stack[1] == production[0][0] && stack[2] == '\0'){
            printf("Accepted\n");
            exit(0);
            }
            reduce(production,num,input+i);
            // printf("%s\t%s\t",stack,input);
            if(stack[0] == '$' && stack[1] == production[0][0] && input[i] == '$'){
                printf("Accepted\n");
                exit(0);
            }
        }
    }
}
void main(){
    int m=1,n=9,num=7,len;
    printf("enter number of terminals,nonterminals,production");
    scanf("%d %d %d",&n,&m,&num);
    char *terminals=malloc(sizeof(char) * n),*nonterminals=malloc(sizeof(char)*m),**production=malloc(sizeof(char *) * num),**leading=malloc(sizeof(char *) * m),**trailing=malloc(sizeof(char *) * m),
    **relationtable = malloc(sizeof(char *)*(n+2)),*input=malloc(sizeof(char) * CHARLENGTH);
    for (int i = 0; i < n+2; i++)
    {
        relationtable[i]=malloc(sizeof(char)*(n+2)*(n+2));
    }
    
    
    // for (int i = 0; i < num; i++)
    // {
    //     production[i]=malloc(sizeof(char) * CHARLENGTH);
    // }
    for (int i = 0; i < m; i++)
    {
        leading[i]=malloc(sizeof(char) *CHARLENGTH);
        leading[i][0]='\0';
        trailing[i]=malloc(sizeof(char) * CHARLENGTH);
        trailing[i][0]='\0';
    }
    /*
    S->a|^|(T)
    T->T,S|T->S
    */

   printf("enter terminals:\n");
    for (int i = 0; i < n; i++)
    {
        scanf(" %c",&terminals[i]);
    }
    printf("enter nonterminals:\n");
    for (int i = 0; i < m; i++)
    {
        scanf(" %c",&nonterminals[i]);
    }
    printf("enter production:\n");
    for (int i = 0; i < num; i++)
    {
        production[i]=malloc(sizeof(char) * CHARLENGTH);
        scanf("%s",production[i]);
    }
    printf("enter input: ");
    scanf("%s",input);
    len=strlen(input);
    input[len]='$';
    input[len+1]='\0';
    // strcpy(input,"i+i$");
    // terminals[0]='+';terminals[1]='=';terminals[2]='-';terminals[3]='^';terminals[4]='*';
    // terminals[5]=')';terminals[6]='(';terminals[7]='/';terminals[8]='i';
    // nonterminals[0]='S';nonterminals[1]='T';
    // strcpy(production[0],"S->)S(");strcpy(production[1],"S->S*S");
    // strcpy(production[2],"S->S+S");strcpy(production[3],"S->S^S");strcpy(production[4],"S->S-S");
    // strcpy(production[5],"S->S/S");strcpy(production[6],"S->i");
    
    findLeading(terminals,nonterminals,production,m,n,num,leading);
    findTrailing(terminals,nonterminals,production,m,n,num,trailing);
    constructRelationTable(relationtable,terminals,nonterminals,production,leading,trailing,m,n,num);
    
    parseInput(relationtable,input,n,production,num,nonterminals,m);
    // for (int i = 0; i < m; i++)
    // {
    //     printf("%s %s\n",leading[i],trailing[i]);
    // }
    
}