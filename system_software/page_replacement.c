#include <stdio.h>
#include <stdlib.h>

void print(int *frame, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (frame[i] == -1)
        {
            printf("- ");
        }
        else
        {
            printf("%d ", frame[i]);
        }
    }
    printf("\n");
}
void createFrame(int *frame, int count, int val)
{
    for (int i = 0; i < count; i++)
    {
        frame[i] = val;
    }
}
void fifo(int *req, int req_count, int frame_count)
{
    int frame[frame_count], fault = 0, i, j = 0, free, now = 0;
    createFrame(frame, frame_count, -1);
    for (i = 0; i < req_count; i++)
    {
        free = 0;
        for (j = 0; j < frame_count; j++)
        {
            if (frame[j] == -1 || frame[j] == req[i])
            {
                if (frame[j] == req[i])
                {
                    free = 1;
                }
                else
                {
                    free = 2;
                }
                break;
            }
        }
        if (free == 2)
        {
            frame[j] = req[i];
            fault++;
            now = (now + 1) % frame_count;
        }
        else if (free == 0)
        {
            frame[now] = req[i];
            fault++;
            now = (now + 1) % frame_count;
        }
        print(frame, frame_count);
    }
    printf("page fault : %d", fault);
}
void lru(int *req, int req_count, int frame_count)
{
    int frame[frame_count], fault = 0, recent[frame_count], i, j, free, flag[frame_count], small;
    createFrame(frame, frame_count, -1);
    for (i = 0; i < req_count; i++)
    {
        free = 0;
        for (j = 0; j < frame_count; j++)
        {
            if (frame[j] == -1 || frame[j] == req[i])
            {
                if (frame[j] == req[i])
                {
                    free = 1;
                }
                else
                {
                    free = 2;
                }
                break;
            }
        }
        if (free == 2)
        {
            frame[j] = req[i];
            fault++;
        }
        else if (free == 0)
        {
            createFrame(flag, frame_count, -1);
            for (j = i - 1; j >= 0; j--)
            {
                for (int k = 0; k < frame_count; k++)
                {
                    if ((req[j] == frame[k]) && (flag[k] == -1))
                    {

                        flag[k] = j;
                    }
                }
            }
            small = 0;
            for (j = 0; j < frame_count; j++)
            {
                if (flag[small] > flag[j])
                {
                    small = j;
                }
            }
            frame[small] = req[i];
            fault++;
        }
        print(frame, frame_count);
    }
    printf("page fault : %d\n", fault);
}
void optimal(int *req, int req_count, int frame_count)
{
    int frame[frame_count], fault = 0, recent[frame_count], i, j, free, flag[frame_count], large;
    createFrame(frame, frame_count, -1);
    for (i = 0; i < req_count; i++)
    {
        free = 0;
        for (j = 0; j < frame_count; j++)
        {
            if (frame[j] == -1 || frame[j] == req[i])
            {
                if (frame[j] == req[i])
                {
                    free = 1;
                }
                else
                {
                    free = 2;
                }
                break;
            }
        }
        if (free == 2)
        {
            frame[j] = req[i];
            fault++;
        }
        else if (free == 0)
        {
            createFrame(flag, frame_count, req_count);
            for (j = i + 1; j < req_count; j++)
            {
                for (int k = 0; k < frame_count; k++)
                {
                    if ((req[j] == frame[k]) && (flag[k] == req_count))
                    {

                        flag[k] = j;
                    }
                }
            }
            large = 0;
            for (j = 0; j < frame_count; j++)
            {
                if (flag[large] < flag[j])
                {
                    large = j;
                }
            }
            frame[large] = req[i];
            fault++;
        }
        print(frame, frame_count);
    }
    printf("page fault : %d\n", fault);
}

void main()
{
    int frame_count, req_count, ch;

    printf("enter number of frames");
    scanf("%d", &frame_count);
    printf("enter number of requests");
    scanf("%d", &req_count);

    int req[req_count];
    for(int i=0;i<req_count;i++){
        printf("Enter req :- ");
        scanf("%d",&req[i]);
    }
    printf("\n");
    // int req[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 3};
    while(1){
        printf("enter option \n1.fifo\n2.lru\n3.optimal\n4.exit\n");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        fifo(req, req_count, frame_count);
        break;
    case 2:
        lru(req, req_count, frame_count);
        break;
    case 3:
        optimal(req, req_count, frame_count);
        break;
    case 4:
        exit(0);
    default:
        printf("\nwrong op\n");
        break;
    }
    }
}