#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct expression
{
    char op[2], op1[5], op2[5], res[5];
    int flag;
} arr[10];
struct table {
    char var[10];
    char value[10];
}symb[10];
int n,count;

void processString(struct expression* inp,char *str){
    char temp[10];
    int i=0,k=0;
    while (isalpha(str[i]))
    {
        inp->res[k++]=str[i];
        i++;
    }
    inp->res[k]='\0';
    i++;
    k=0;
    while (isalpha(str[i]) || isdigit(str[i]))
    {
        temp[k++]=str[i];
        i++;
    }
    temp[k]='\0';
    strcpy(inp->op1,temp);
    if(str[i] == '\0'){
        strcpy(inp->op2,"-");
        strcpy(inp->op,"=");
    }else{
        
        inp->op[0]=str[i++];
        inp->op[1]='\0';
        k=0;
        while (isalpha(str[i]) || isdigit(str[i]))
        {
            inp->op2[k++]=str[i];
            i++;
        }
        inp->op2[k]='\0';
    }
}
void getInput()
{
    int i;
    char str[100];
    count=0;
    printf("Enter the number of  expressions : ");
    scanf("%d", &n);
    printf("Enter the input in 3AC : \n");
    for (i = 0; i < n; i++)
    {
        scanf("%s", str);
        processString(&arr[i],str);
        // printf("%s=%s%s%s\n",arr[i].res,arr[i].op1,arr[i].op,arr[i].op2);
        arr[i].flag = 0;
    }
}
int isPresent(char *arr){
    for (int i = 0; i < count; i++)
    {
        if(strcmp(arr,symb[i].var) == 0){
            return i;
        }
    }
    return -1;
}
void constantProp()
{
    int i;
    int op1, op2, res,index;
    char op, res1[5];
    for (i = 0; i < n; i++)
    {
        if((index = isPresent(arr[i].op1)) > -1){
            strcpy(arr[i].op1,symb[index].value);
        }
        if((index = isPresent(arr[i].op2)) > -1){
            strcpy(arr[i].op2,symb[index].value);
        }
        if (isdigit(arr[i].op1[0]) && isdigit(arr[i].op2[0]) || isdigit(arr[i].op1[0]) && strcmp(arr[i].op, "=") == 0)
        {
            op1 = atoi(arr[i].op1);
            op2 = atoi(arr[i].op2);
            op = arr[i].op[0];
            switch (op)
            {
            case '+':
                res = op1 + op2;
                break;
            case '-':
                res = op1 - op2;
                break;
            case '*':
                res = op1 * op2;
                break;
            case '/':
                res = op1 / op2;
                break;
            case '=':
                res = op1;
                break;
            }
            if((index = isPresent(arr[i].res)) > -1){
                sprintf(symb[index].value, "%d", res);
            }else{
                strcpy(symb[count].var,arr[i].res);
                sprintf(symb[count++].value, "%d", res);
            }
            // printf("%s %d",symb[0].value,res);
            arr[i].flag = 1;
            // change(i, res1);
        }else{
        if((index = isPresent(arr[i].res)) > -1){
                strcpy(symb[count].var,"-");
            }
    }
    }
}
void printOutput()
{
    int i = 0;
    printf("\nOptimized code is : ");
    for (i = 0; i < n; i++)
    {
        if (!arr[i].flag)
        {
            if(arr[i].op2[0] == '-'){
                printf("\n%s%s%s",arr[i].res,arr[i].op,arr[i].op1);
            }
            else{
            printf("\n%s=%s%s%s",arr[i].res,arr[i].op1, arr[i].op, arr[i].op2);
            }
        }
    }
    printf("\n");
}

void main()
{
    getInput();
    constantProp();
    printOutput();
}
