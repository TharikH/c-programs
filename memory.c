#include <stdio.h>
#include <stdlib.h>

#define VAL 1000

typedef struct Mem                 //create structure
{
    int data1;
    int data2;
    int tag;
    int ptag;
    struct Mem *next;
    struct Mem *prev;
} mem;

void create(mem *parent, int d, int t)                              //create partion --first node on last
{
    mem *ptr = (mem *)malloc(sizeof(mem));
    ptr->data1 = parent->data1;
    ptr->data2 = ptr->data1 + d;
    ptr->tag = t;
    ptr->prev = parent->prev;
    ptr->next = parent;
    if (parent->prev != NULL)
    {
        parent->prev->next = ptr;
    }
    parent->prev = ptr;
    parent->data1 = ptr->data2;
}
void print(mem *parent)                                                //print linked lists-----both available and alloc
{
    mem *ptr = parent;
    while (ptr != NULL)
    {
        printf("%d ==> %d -- %d\n", ptr->tag, ptr->data1, ptr->data2);
        ptr = ptr->next;
    }
}
mem *changeParent(mem *parent)                                      //as on creation added elements on first----so taking the header to front
{
    mem *ptr = parent;
    while (ptr->prev != NULL)
    {
        ptr = ptr->prev;
    }
    return ptr;
}
void addMem(mem *avail, mem *alloc, int data)                           //add memory onto the partion by using FCFS rule
{
    mem *temp;
    int flag = 0;
    while (avail != NULL)
    {
        if (avail->data2 - avail->data1 > data)
        {
            if (alloc->data2 == 0 && alloc->data1 == 0)
            {
                temp = alloc;
            }
            else
            {
                temp = (mem *)malloc(sizeof(mem));
                temp->next = alloc->next;
                temp->prev = alloc;
                alloc->next = temp;
            }
            temp->data1 = avail->data1;
            temp->data2 = temp->data1 + data;
            avail->data1 += data;
            temp->ptag = avail->tag;
            printf("Enter tag");
            scanf("%d", &temp->tag);
            flag = 1;
            break;
        }
        avail = avail->next;
    }
    if (flag == 0)
    {
        printf("\nnot able to allocate\n");
    }
}
void deleteMem(mem *avail, mem **temp, int tag)                                         //delete memory and it goes back to its parent----compared with parent tag
{
    int flag = 0;
    mem *alloc = *temp;
    while (alloc != NULL)
    {
        if (alloc->tag == tag)
        {
            while (avail->tag != alloc->ptag)
                avail = avail->next;
            avail->data1 -= alloc->data2 - alloc->data1;

            if (alloc->prev != NULL)
            {
                alloc->prev->next = alloc->next;
                if (alloc->next != NULL)
                    alloc->next->prev = alloc->prev;
                free(alloc);
            }
            else if (alloc->next == NULL)
            {
                alloc->data1 = 0;
                alloc->data2 = 0;
            }
            else
            {
                alloc->next->prev = NULL;
                *temp = alloc->next;
                free(alloc);
            }

            flag = 1;
            break;
        }
        alloc = alloc->next;
    }
    if (flag == 0)
    {
        printf("no tags found");
    }
}
//main function     <<<<<<<<<<<<<<<<<<<<<<<<<<<-------------------------------------------------------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.
void main()
{
    int d, t, ch, i = 1;
    mem *parent = (mem *)malloc(sizeof(mem));
    mem *alloc = (mem *)malloc(sizeof(mem));
    alloc->tag = 0;
    alloc->data1 = 0;
    alloc->data2 = 0;
    parent->data2 = VAL;
    parent->data1 = 0;
    parent->tag = 0;
    parent->next = NULL;
    parent->prev = NULL;
    printf("Total Partion: %d\n---------------\n", VAL);
    while (i)
    {
        printf("\nchoose option:\n1.create partion\n2.print memory partion\n3.goto partion\n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("\navailable partition %d\nhow much partion should be allocated and tag given?\n", parent->data2 - parent->data1);
            scanf("%d %d", &d, &t);
            if ((parent->data2 - parent->data1) > d)
            {
                create(parent, d, t);
                printf("available memory is %d ", parent->data2 - parent->data1);
            }
            else
            {
                printf("\nnot enough memory\n");
            }
            break;
        case 2:
            print(parent);
            break;
        case 3:
            i = 0;
            break;
        default:
            printf("\ninvalid choice");
            break;
        }
    }
    parent = changeParent(parent);
    while (1)
    {
        printf("\n1.add memory\n2.print avail\n3.print alloc\n4.delete partition\n5.exit\n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("how much memory allocate?");
            scanf("%d", &d);
            addMem(parent, alloc, d);
            break;
        case 2:
            print(parent);
            break;
        case 3:
            print(alloc);
            break;
        case 4:
            printf("enter tag of memory to delete\n");
            scanf("%d", &d);
            deleteMem(parent, &alloc, d);
            break;
        case 5:
            exit(0);
            break;

        default:
            printf("\ninvalid choice");
            break;
        }
    }
}