#include <stdio.h>
#include <stdlib.h>
float average(int *w, int num)
{
    int avg = 0;
    for (int i = 0; i < num; i++)
    {
        avg += w[i];
    }
    return ((float)avg) / num;
}
void fcfs(int *a, int *b, int len)
{                                                                                                                 //fcfs
    int *t = (int *)calloc(len, sizeof(int)), finish[len], time = 0, small, *w = (int *)calloc(len, sizeof(int)); //turnaround array and finish array
    for (int i = 0; i < len; i++)
    {
        small = i;
        for (int j = 0; j < len; j++)
        {
            if (t[j] == 0)
            {                                         //To check if that value is being used for processing
                if (a[j] < a[small] || t[small] != 0) //to check whether small elemnt is already used  or there is an elemnt in arrival time where it is smaller
                {
                    small = j; //to get the smallest arrival time first
                }
            }
        }
        // printf("%d\n",small);
        if (time < a[small])
        { //if arrival time greater than total time,so we need to add arrival
            time += (time-a[small]);
        }
        time += b[small];  //to add burst time to total time
        t[small] = time;   //to store finish time so later it can be made to turnaround by subtracting
        finish[i] = small; //to add the sequence
    }
    for (int i = 0; i < len; i++)
    { //create turn around and waiting time
        t[i] -= a[i];
        w[i] = t[i] - b[i];
    }
    printf("Waiting time =  %f \n", average(w, len));
    printf("Turnaround time =  %f\n", average(t, len));
}

void sjf(int *a, int *b, int len)
{                                                                                                                       //sjf
    int *t = (int *)calloc(len, sizeof(int)), finish[len], time = 0, small, *w = (int *)calloc(len, sizeof(int)), flag; //turnaround array and finish array
    for (int i = 0; i < len; i++)
    {
        small = i;
        flag = 0;
        for (int j = 0; j < len; j++)
        {
            if (t[j] == 0)
            {                                                           //To check if that value is being used for processing
                if ((b[j] < b[small] || t[small] != 0 || (a[small]>time)) && a[j] <= time) //to check whether small elemnt is already used  or there is an elemnt in burst time where it is smaller and arrival is less than total time
                {
                    
                    small = j; //to get the smallest arrival time first
                }
            }
        }
        // printf("%d\n",small);
        if (time < a[small])
        { //if arrival time greater than total time,so we need to add arrival
            time += a[small];
        }
        time += b[small];  //to add burst time to total time
        t[small] = time;   //to store finish time so later it can be made to turnaround by subtracting
        finish[i] = small; //to add the sequence
    }
    for (int i = 0; i < len; i++)
    { //create turn around and waiting time
        t[i] -= a[i];
        w[i] = t[i] - b[i];
    }
    printf("Waiting time =  %f \n", average(w, len));
    printf("Turnaround time =  %f\n", average(t, len));
    free(t);
    free(w);
}
void enq(int *a, int val, int *front, int *rear, int len)
{
    if (*front == -1)
    {
        a[++(*front)] = val;
        (*rear)++;
    }
    else
    {
        *rear = ((*rear) + 1) % len;
        a[*rear] = val;
    }
}
int deq(int *a, int *front, int *rear, int len)
{
    int temp;
    if (*front == *rear)
    {
        temp = a[(*rear)];
        *front = -1;
        *rear = -1;
    }
    else
    {
        temp = a[*front];
        *front = ((*front) + 1) % len;
    }
    return temp;
}
void rr(int *a, int *b, int len)
{
    int slice = 3, *t = (int *)calloc(len, sizeof(int)), finish[len], time = 0, small, w[len], front = -1, rear = -1, bt[len], val, flag, q[len], temp;
    for (int i = 0; i < len; i++)
        bt[i] = b[i];
    while (1)
    {
        val = 0;
        if (front != -1)
        {
            temp = deq(q, &front, &rear, len);
            if (bt[temp] - slice <= 0)
            {
                time += bt[temp];
                finish[temp] = time;
            }
            else if (bt[temp] - slice > 0)
            {
                bt[temp] -= slice;
                time += slice;
                val = 1;
            }
        }
        while (1)
        {
            small = 0;
            flag = 0;
            for (int j = 0; j < len; j++)
            {
                if (t[j] == 0)
                { //To check if that value is being used for processing
                    flag = 1;
                    if (a[j] < a[small] || t[small] != 0) //to check whether small elemnt is already used  or there is an elemnt in arrival time where it is smaller
                    {
                        small = j; //to get the smallest arrival time first
                    }
                }
            }

            if (flag == 0 || (a[small] > time && front != -1))
            {
                break;
            }
            else if (a[small] > time && front == -1)
            {   if(val==1)
                    break;
                time += a[small];
            }
            else
            {
                t[small] = 1;
                enq(q, small, &front, &rear, len);
            }
        }
        if (val == 1)
        {
            enq(q, temp, &front, &rear, len);
        }
        if (front == -1)
        {
            break;
        }
    }
    for (int i = 0; i < len; i++)
    {
        finish[i] -= a[i];
        w[i] = finish[i] - b[i];
    }
    printf("Waiting time =  %f \n", average(w, len));
    printf("Turnaround time =  %f\n", average(finish, len));
}
void priority(int *a, int *b, int *p, int len)
{
    int *t = (int *)calloc(len, sizeof(int)), finish[len], time = 0, small, *w = (int *)calloc(len, sizeof(int)), flag; //turnaround array and finish array
    for (int i = 0; i < len; i++)
    {
        small = i;
        flag = 0;
        for (int j = 0; j < len; j++)
        {
            if (t[j] == 0)
            {                                                           //To check if that value is being used for processing
                if ((p[j] < p[small] || t[small] != 0 || (a[small]>time)) && a[j] <= time) //to check whether small elemnt is already used  or there is an elemnt in priority time where it is smaller and arrival is less than total time
                {
                    flag = 1;
                    small = j; //to get the smallest arrival time first
                }
            }
        }
        // printf("%d\n",small);
        if (time < a[small])
        { //if arrival time greater than total time,so we need to add arrival
            time += a[small];
        }
        time += b[small];  //to add burst time to total time
        t[small] = time;   //to store finish time so later it can be made to turnaround by subtracting
        finish[i] = small; //to add the sequence
    }
    for (int i = 0; i < len; i++)
    { //create turn around and waiting time
        t[i] -= a[i];
        w[i] = t[i] - b[i];
    }
    printf("Waiting time =  %f \n", average(w, len));
    printf("Turnaround time =  %f\n", average(t, len));
}

void main()
{

    while (1)
    {
        int ch, i = 1;
        char c;
        int *bt = (int *)malloc(sizeof(int)), *at = (int *)malloc(sizeof(int)), *pt = (int *)malloc(sizeof(int));
        printf("Choose which Scheduling\n1.FCFS\n2.SJF\n3.RR\n4.Priority\n5.Exit\n");
        scanf("%d", &ch);
        if (ch == 5)
        {
            exit(0);
        }
        while (1)
        {
            printf("enter burst: ");
            scanf("%d", &bt[i-1]);
            printf("enter arrival: ");
            scanf("%d", &at[i-1]);
            if (ch == 4)
            {
                printf("enter priority: ");
                scanf("%d", &pt[i-1]);
            }
            printf("\ndo you wanna continue? y/n :");
            scanf(" %c", &c);
            if (c == 'n')
                break;
            i++;
            bt = realloc(bt, sizeof(int) * i);
            at = realloc(at, sizeof(int) * i);
            if(ch==4){
                pt = realloc(pt, sizeof(int) * i);
            }
        }
        // int bt[] = {3,6,1,2,4}, at[] = {0,1,3,2,4}, pt[] = {3,4,9,7,8};
        // for(int j=0;j<i;j++)
        //     printf("%d-%d\n",bt[j],at[i]);
        switch (ch)
        {
        case 1:
            fcfs(at, bt, i);
            break;
        case 2:
            sjf(at, bt, i);
            break;
        case 3:
            rr(at, bt, i);
            break;
        case 4:
            priority(at, bt, pt, i);
            break;
        default:
            printf("invalid choice");
            break;
        }
    }
}