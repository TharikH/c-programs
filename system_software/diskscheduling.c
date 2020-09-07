#include <stdio.h>
#include <stdlib.h>
int diff(int a, int b)
{
    if (a > b)
        return a - b;
    else
        return b - a;
}
void sort(int *a, int len)
{
    int flag = 0, temp;
    for (int i = 0; i < len; i++)
    {
        flag = 0;
        for (int j = 0; j < len - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                flag = 1;
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
        if (flag == 0)
        {
            break;
        }
    }
}
void fcfs(int *a, int head, int len)
{
    int dist = 0;
    for (int i = 0; i < len; i++)
    {
        // printf("%d ",head);
        dist += (diff(head, a[i]));
        head = a[i];
        // printf("%d ",head);
    }
    printf("total seek for fcfs is: %d\n", dist);
}

int scanGeneral(int *a, int head, int len, int val,int last,int c)
{
    int pos, dist = 0, i, d=2,left=0,right=len;
    sort(a, len);
    for (i = 0; i < len; i++)
    {
        if (a[i] > head)
        {
            pos = i;
            break;
        }
    }
    while (d--)
    {
        if (val == 0)
        {
            for (i = pos - 1; i >= left; i--)
            {
                dist += (diff(head, a[i]));
                head = a[i];
            }
            if(d){
                head=a[i+1];
                dist += head;
                head = 0;
                val=1;
                if(c){
                    val=0;
                    dist+=last;
                    head=last;
                    left=pos;
                    pos=len;
                }
            }
        }
        else{
            for (i = pos; i < right; i++)
            {
                dist += (diff(head, a[i]));
                head = a[i];
            }
            if(d){
                head=a[i-1];
                dist += last-head;
                head = last;
                val=0;
                if(c){
                    val=1;
                    dist+=last;
                    head=0;
                    right=pos;
                    pos=0;
                }
            }
        }
    }
    return dist;
}
void scan(int *a, int head, int len,int dir,int last)
{
    int dist, val = 0;
    dist = scanGeneral(a, head, len, dir,last,val);
    printf("\nSeek time for scan is :%d\n", dist);
}
void cScan(int *a, int head, int len,int dir,int last)
{
    int dist, val = 1;
    dist = scanGeneral(a, head, len, dir,last,val);
    printf("\nSeek time for C-scan is :%d\n", dist);
}

void main()
{
    int ch, len, head,last,dir;
    while (1)
    {
        int a[] = {98, 137, 122, 183, 14, 133, 65, 78};
        len = sizeof(a) / sizeof(a[0]);
        head = 54;last=199;dir=0;
        printf("\n\nhead pos: %d\n ", head);
        printf("Values are :\n");
        for (int i = 0; i < len; i++)
        {
            printf("%d ", a[i]);
        }
        printf("choose operation: \n1.FCFS\n2.SCAN\n3.C-SCAN\n4.EXIT\n option: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            fcfs(a, head, len);
            break;
        case 2:
            scan(a, head, len,dir,last);

            break;
        case 3:
            cScan(a, head, len,dir,last);
            break;
        case 4:
            exit(0);
            break;
        default:
            printf("\ninvalid choice\n");
            break;
        }
    }
}