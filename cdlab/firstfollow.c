#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CHARLENGTH 20
/*
S->aA
S->Ab
A->Ba
B->b
*/
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
void firstOfNonTerminal(char *nonterminals,int index,char **production,char *terminals,char ** first,int m,int n,int num){
    int tempindex;
    char *temp;
    if(first[index][0] != '\0'){
        return;
    }else{
        for (int i = 0; i < num; i++)
        {
            if(production[i][0] == nonterminals[index]){
                temp=production[i]+3;
                if(isTerminal(terminals,temp[0],n)){
                addToFirst(temp[0],first,index);
                }else{
                    tempindex=findIndexOfNonterminal(nonterminals,temp[0],m);
                if(first[tempindex][0] != '\0'){
                    copyFirst(index,tempindex,first);
                }else{
                    firstOfNonTerminal(nonterminals,tempindex,production,terminals,first,m,n,num);
                    copyFirst(index,tempindex,first);
                }
                }
            }
        }
        
    }
    // index=findIndexOfNonterminal(nonterminals,nonterminal],m);
    // printf("%d - hello\n",index);
    // temp=production[i]+3;
    //     // printf("%s\n",temp);
    //     if(isTerminal(terminals,temp[0],n)){
    //         addToFirst(temp[0],first,index,num);
    //     }else{
    //         tempindex=findIndexOfNonterminal(nonterminals,temp[0],m);
    //         if(first[tempindex][0] != '\0'){
    //             copyFirst(index,tempindex,first);
    //         }else{
    //             findFirst(nonterminals,terminals,production,)
    //         }
    //     }
}
void findFirsts(char *nonterminals,char *terminals,char **production,char **first,int m,int n,int num){
    // for (int i = 0; i < num; i++)
    // {
    //     firstOfNonTerminal()
    // }
    for (int i = 0; i < m; i++)
    {
        firstOfNonTerminal(nonterminals,i,production,terminals,first,m,n,num);
    }
    
}
void main(){
    int m=3,n=2,num=4;
    char *terminals=malloc(sizeof(char) * n),*nonterminals=malloc(sizeof(char)*m),**production=malloc(sizeof(char *) * num),**first=malloc(sizeof(char *) * m);
    for (int i = 0; i < num; i++)
    {
        production[i]=malloc(sizeof(char) * CHARLENGTH);
    }
    for (int i = 0; i < m; i++)
    {
        first[i]=malloc(sizeof(char) *CHARLENGTH);
        first[i][0]='\0';
    }
    
    terminals[0]='a';terminals[1]='b';
    nonterminals[0]='S';nonterminals[1]='A';nonterminals[2]='B';
    strcpy(production[0],"S->aA");strcpy(production[1],"S->Ab");strcpy(production[2],"A->Ba");strcpy(production[3],"B->b");

    findFirsts(nonterminals,terminals,production,first,m,n,num);

    for (int i = 0; i < m; i++)
    {
        printf("%s\n",first[i]);
    }
    
}