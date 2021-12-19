#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define CHARLENGTH 20

int isTerminal(char *terminals,char terminal,int n){
    for (int i = 0; i < n; i++)
    {
        if(terminals[i] == terminal){
            return 1;
        }
    }
    return 0;
}
int findIndexOfNonterminal(char *nonterminals,char nonterminal,int m){
    for (int i = 0; i < m; i++)
    {
        if (nonterminals[i] == nonterminal)
        {
            return i;
        }
        
    }
    return -1;
}
void addToFirst(char terminal,char **first,int index){
    int i=0;
    while (first[index][i] != '\0' && first[index][i] != terminal)
    {
        i++;
    }
    if(first[index][i] == '\0'){
        first[index][i]=terminal;
        i++;
        first[index][i]='\0';
    }
    
}
void copyFirst(int index,int tempindex,char **first){
    int i=0,j=0;
    while (first[tempindex][j] != '\0')
    {
        if(first[tempindex][j] == 'e'){
            j++;
            continue;
        }
        i=0;
        while (first[index][i] != '\0' && first[index][i] != first[tempindex][j])
        {
            i++;
        }
        if(first[index][i] == '\0'){
            first[index][i]=first[tempindex][j];
            i++;
            first[index][i]='\0';
        }
        j++;
        
    }
    

}
int haveEpsilon(int index,char **first){
    int i=0;
    while (first[index][i] != '\0')
    {
        if(first[index][i] == 'e'){
            return 1;
        }
        i++;
    }
    return 0;
    
}
void firstOfNonTerminal(char *nonterminals,int index,char **production,char *terminals,char ** first,int m,int n,int num,int check){
    int tempindex;
    char *temp;
    if(first[index][0] != '\0'){
        return;
    }else{
        for (int i = 0; i < num; i++)
        {
            if(production[i][0] == nonterminals[index]){
                temp=production[i]+3;
                if(isTerminal(terminals,temp[0],n) || temp[0] == 'e'){
                addToFirst(temp[0],first,index);
                }
                else{
                    L1:
                    if(temp[0] == '\0'){
                        addToFirst('e',first,index);
                        continue;
                    }
                    // printf("%c ",temp[0]);
                    tempindex=findIndexOfNonterminal(nonterminals,temp[0],m);
                if(first[tempindex][0] != '\0'){
                    copyFirst(index,tempindex,first);
                    if(haveEpsilon(tempindex,first)){
                        temp++;
                        goto L1;
                    }
                }
                else{
                    if(check != -1 && first[check][0] == '\0'){
                        return;
                    }
                    firstOfNonTerminal(nonterminals,tempindex,production,terminals,first,m,n,num,index);
                    copyFirst(index,tempindex,first);
                    if(haveEpsilon(tempindex,first)){
                        temp++;
                        goto L1;
                    }
                }
                }
            }
        }
        
    }
}
void followOfNonTerminal(char *nonterminals,int index,char **production,char *terminals,char ** first,int m,int n,int num,int check){
    char *temp;
    int tempindex;
    if(follow[index][0] != '\0' && index != 0){
        return;
    }else{
        for (int i = 0; i < num; i++)
        {
        int j=0;
        temp=production[i]+3;
        while(temp[j] != '\0'){
            if(nonterminals[index] == temp[j]){
                L2:
                if(isTerminal(terminals,temp[j+1]),n){
                    addToFirst(temp[j+1],follow,index);
                }else{
                    if(temp[j+1] == '\0'){
                        tempindex=findIndexOfNonterminal(nonterminals,producion[i][0],m);
                        followOfNonTerminal(nonterminals,tempindex,production,terminals,first,m,n,num,index);
                        copyFirst(i,index,follow);
                    }else{
                        tempindex=findIndexOfNonterminal(nonterminals,temp[j+1],m);
                        copyFollow(tempindex,index,follow,first);
                        if(haveEpsilon(tempindex,first)){
                            j++;
                            goto L2;
                        }
                    }
                }
            }
            j++;
        }
        }
    }
    
    

}
void findFirsts(char *nonterminals,char *terminals,char **production,char **first,int m,int n,int num){
    for (int i = 0; i < m; i++)
    {
        firstOfNonTerminal(nonterminals,i,production,terminals,first,m,n,num,-1);
    }
    
}
void findFollow(char *nonterminals,char *terminals,char **production,char **first,char **follow,int m,int n,int num){
    
    follow[0][0]='$';follow[0][1]='\0';
    for (int i = 0; i < m; i++)
    {
        followOfNonTerminal(nonterminals,i,production,terminals,first,m,n,num,-1);
    }
    
}
void main(){
    int m=6,n=6,num=9;
    char *terminals=malloc(sizeof(char) * n),*nonterminals=malloc(sizeof(char)*m),**production=malloc(sizeof(char *) * num),**first=malloc(sizeof(char *) * m),**follow=malloc(sizeof(char *) * m);
    for (int i = 0; i < num; i++)
    {
        production[i]=malloc(sizeof(char) * CHARLENGTH);
    }
    for (int i = 0; i < m; i++)
    {
        first[i]=malloc(sizeof(char) *CHARLENGTH);
        first[i][0]='\0';
        follow[i]=malloc(sizeof(char) * CHARLENGTH);
        follow[i][0]='\0';
    }
    
    terminals[0]='a';terminals[1]='h';terminals[2]='c';terminals[3]='b';terminals[4]='g';terminals[5]='f';
    nonterminals[0]='S';nonterminals[1]='B';nonterminals[2]='C';nonterminals[3]='D';nonterminals[4]='E';nonterminals[5]='F';
    strcpy(production[0],"S->aBDh");strcpy(production[1],"B->cC");
    strcpy(production[2],"C->bC");strcpy(production[3],"C->e");strcpy(production[4],"D->EF");
    strcpy(production[5],"E->g");strcpy(production[6],"E->e");strcpy(production[7],"F->f");strcpy(production[8],"F->e");

    findFirsts(nonterminals,terminals,production,first,m,n,num);
    findFollow(nonterminals,terminals,production,first,follow,m,n,num);
    int j=0;
    printf("FIRST \n");
    for (int i = 0; i < m; i++)
    {
        printf("%c = {",nonterminals[i]);
        j=0;
        while (first[i][j] != '\0')
        {
            printf("%c,",first[i][j]);
            j++;
        }
        
        printf("}\n");
    }
    printf("FOLLOW \n");
    for (int i = 0; i < m; i++)
    {
        printf("%c = {",nonterminals[i]);
        j=0;
        while (follow[i][j] != '\0')
        {
            printf("%c,",follow[i][j]);
            j++;
        }
        
        printf("}\n");
    }
}