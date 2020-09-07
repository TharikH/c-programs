#include <stdio.h>
#include <stdlib.h>
const int r = 3;
int great(int *large, int *small, int len)
{
    int flag = 0;
    for (int i = 0; i < len; i++)
    {
        if (large[i] < small[i])
        {
            flag = 1;
            break;
        }
    }
    return flag == 1 ? 0 : 1;
}
void sumAvail(int *avail, int *alloc, int len)
{
    for (int i = 0; i < len; i++)
    {
        avail[i] += alloc[i];
    }
}
void diffAvail(int *avail, int *alloc, int len){
    for (int i = 0; i < len; i++)
    {
        avail[i] -= alloc[i];
    }
}
int bankers(int alloc[][r], int max[][r], int *avail, int p_len, int r_len)
{
    int *process_finish = calloc(p_len, sizeof(int)), need[p_len][r_len], k = 0, cycle = -1, flag = 0, ord = 1;
    for (int i = 0; i < p_len; i++)
    {
        for (int j = 0; j < r_len; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    while (1)
    {
        if (k == cycle)
        {
            for (int i = 0; i < p_len; i++)
            {
                if (process_finish[i] == 0)
                {
                    // printf("%d ", k);
                    flag = -1;
                    break;
                }
            }
            break;
        }
        if (great(avail, need[k], r_len) && process_finish[k] == 0)
        {
            process_finish[k] = ord;
            ord++;

            sumAvail(avail, alloc[k], r_len);
            cycle = k;
        }
        // printf("\n%d %d\n", cycle, k);
        k = (k + 1) % p_len;
        if (k == p_len - 1 && cycle == -1)
        {
            flag = -1;
            break;
        }
    }
    if (flag == -1)
    {
        return 0;
    }
    else
    {
        // printf("poss");
        return 1;
    }
}
void resource(int alloc[][r], int max[][r], int *avail, int p_len, int r_len, int *req, int index)
{   int need[r_len];
    for(int i=0;i<r_len;i++){
        need[i]=max[index][i]-alloc[index][i];
    }
    if (great(avail,req,r_len) && great(need,req,r_len) )
    {   
        sumAvail(alloc[index],req,r_len);
        diffAvail(avail,req,r_len);
        if(bankers(alloc, max, avail, p_len, r_len))
            printf("\nPossible\n");
        else{
            printf("\neadlock\n");
        }
    }
    else{
        printf("\nnot poss\n");
    }
    
}
void main()
{
    int p_len = 5, r_len = 3;
    int alloc[5][3] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    int max[5][3] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    int avail[3] = {3, 3, 2}, ch,req[3],index;
    // int **a=alloc,**m=max;
    printf("\nEnter \n1.safety \n2.resource\n");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        if (bankers(alloc, max, avail, p_len, r_len))
        {
            printf("\nNo deadlock\n");
        }
        else
        {
            printf("deadlock");
        }

        break;
    case 2:
        printf("enter which process requests resource\n");
        scanf("%d", &index);
        printf("request the resource\n");
        for (int i = 0; i < r_len; i++)
        {
            printf(" enter request\n");
            scanf("%d", &req[i]);
        }
        resource(alloc, max, avail, p_len, r_len,req,index);
    default:

        break;
    }
}