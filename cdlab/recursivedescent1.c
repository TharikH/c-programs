#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHARLENGTH 20
#define MAX 20

int ind;

int isPresent(char *terminals, char terminal, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (terminals[i] == terminal)
        {
            return 1;
        }
    }
    return 0;
}

int recursive(char *terminals, char *nonterminals, char **production, char *input, char nonterminal, int m, int n, int num)
{
    char *ptr;
    int j, flag = 1, temp = 0, temp1;
    for (int i = 0; i < num; i++)
    {
        int len = strlen(production[i] + 3), tempflag = 0, *arr = calloc(len, sizeof(int));
        temp = 1;
        temp1 = ind;
        if (production[i][0] == nonterminal)
        {
            ptr = production[i] + 3;
            // printf("%c %s  %d\n", nonterminal, ptr, ind);
            j = 0;
            while (ptr[j] != '\0')
            {
                if (isPresent(terminals, ptr[j], n))
                {
                    if (input[ind] == ptr[j])
                    {
                        // printf("%c  %d",ptr[j],ind);
                        arr[j] = 1;
                        ind++;
                        // printf("shifft %c %s  %d %d\n", nonterminal, ptr, ind, j);
                    }
                    else
                    {
                        // printf("wrong %c %s  %d %d\n", nonterminal, ptr, ind, j);
                        break;
                    }
                }
                else if (isPresent(nonterminals, ptr[j], m))
                {
                    temp = recursive(terminals, nonterminals, production, input, ptr[j], m, n, num);
                    if (temp < 0)
                        break;
                    else
                        arr[j] = 1;
                }
                else if (ptr[j] == 'e')
                {
                    arr[j] = 1;
                }
                j++;
            }
            if (temp < 0 || ptr[j] != '\0')
            {
                ind = temp1;
                continue;
            }
        }

        tempflag = 0;
        for (int i = 0; i < len; i++)
        {
            if (arr[i] != 1)
                tempflag = 1;
        }
        if (!tempflag)
        {
            // printf("reduce %c \n", nonterminal);
            return 1;
        }
    }
    // printf("error %c \n", nonterminal);
    return -1;
}

void main()
{
    int m = 4, n = 5, num = 7;
    // printf("enter number of terminals,nonterminals,production");
    // scanf("%d %d %d",&n,&m,&num);
    char *terminals = malloc(sizeof(char) * n), *nonterminals = malloc(sizeof(char) * m), **production = malloc(sizeof(char *) * num);
    char *input = malloc(sizeof(char) * CHARLENGTH);
    // printf("enter terminals:\n");
    // for (int i = 0; i < n; i++)
    // {
    //     scanf(" %c",&terminals[i]);
    // }
    // printf("enter nonterminals:\n");
    // for (int i = 0; i < m; i++)
    // {
    //     scanf(" %c",&nonterminals[i]);
    // }
    // printf("enter production:\n");
    for (int i = 0; i < num; i++)
    {
        production[i] = malloc(sizeof(char) * CHARLENGTH);
        // scanf("%s",production[i]);
    }
    // printf("enter input: ");
    // scanf("%s",input);
    terminals[0] = 'a';
    terminals[1] = 'b';
    terminals[2] = 'c';
    terminals[3] = 'd';
    terminals[4] = 'f';
    nonterminals[0] = 'S';
    nonterminals[1] = 'A';
    nonterminals[2] = 'B';
    nonterminals[3] = 'C';
    strcpy(production[0], "S->ABC");
    strcpy(production[1], "A->aAb");
    strcpy(production[2], "A->C");
    strcpy(production[3], "B->cB");
    strcpy(production[4], "B->d");
    strcpy(production[5], "C->fC");
    strcpy(production[6], "C->e");
    strcpy(input, "aabbdff");
    ind = 0;
    int temp = recursive(terminals, nonterminals, production, input, production[0][0], m, n, num);
    if (input[ind] != '\0' || temp < 0)
    {
        printf("rejected!");
    }
    else
    {
        printf("accepted");
    }
}