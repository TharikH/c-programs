#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dir
{
    int isdir;
    char name[20];
    int count;
    struct dir *next;
    struct dir *sub_dir;
} dir;

int isexist(dir *root, char *name)
{
    dir *ptr = root;
    while (ptr != NULL)
    {
        if (strcmp(ptr->name, name) == 0)
        {
            return 1;
        }
        ptr = ptr->next;
    }
    return 0;
}
void add(dir *root, int isdir)
{
    char name[20];
    printf("enter name : ");
    scanf(" %s", name);
    if (!isexist(root->sub_dir, name))
    {
        dir *new = (dir *)malloc(sizeof(dir));
        new->isdir = isdir;
        new->next = root->sub_dir;
        root->sub_dir = new;
        root->count++;
        strcpy(new->name, name);
    }
    else
    {
        printf("\nalready exist");
    }
}
dir *findParent(dir *root, char *name)
{
    dir *ptr = root->sub_dir;
    while (ptr != NULL)
    {
        if (strcmp(ptr->name, name))
        {
            return ptr;
        }
        ptr=ptr->next;
    }
    return ptr;
}
void delete (dir *root)
{
    char name[20];
    int flag = 0;
    printf("enter name : ");
    scanf(" %s", name);
    dir *ptr = root->sub_dir, *ptr1 = root->sub_dir;
    if (strcmp(ptr->name, name) == 0)
    {
        root->sub_dir = ptr->next;
        flag = 1;
        free(ptr);
    }
    while (ptr != NULL)
    {
        if (strcmp(ptr->name, name) == 0)
        {
            flag = 1;
            ptr1->next = ptr->next;
            free(ptr);
            break;
        }
        ptr1 = ptr;
        ptr = ptr->next;
    }
    if (flag == 0)
    {
        printf("\ndoesnt exist\n");
    }
}

void print(dir *root)
{
    dir *ptr = root;
    while (ptr != NULL)
    {
        printf(" %s ", ptr->name);
        ptr = ptr->next;
    }
}

void twolevel()
{
    int ch;
    char name[20];
    dir *root = (dir *)malloc(sizeof(dir)), *ptr;
    while (1)
    {
        printf("\nenter option \n1.create file\n2.delete file\n3.create user\n4.delete user\n5.print\n6.print users\n7.back\nchoose  : ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("enter which user : ");
            scanf(" %s", name);
            ptr = findParent(root, name);
            if (ptr != NULL)
            {
                add(ptr, 0);
            }
            else
            {
                printf("\nno user\n");
            }
            break;
        case 2:
            printf("enter which user : ");
            scanf(" %s", name);
            ptr = findParent(root, name);
            if (ptr != NULL)
            {
                delete (ptr);
            }
            else
            {
                printf("\nno user\n");
            }
            break;
        case 3:
            add(root, 1);
            break;
        case 4:
            delete (root);
            break;
        case 5:
            printf("enter which user : ");
            scanf(" %s", name);
            ptr = findParent(root, name);
            print(ptr->sub_dir);
            break;
        case 6:
            print(root->sub_dir);
            break;
        case 7:
            return;
        default:
            printf("invalid choice\n");
            break;
        }
    }
}
void single()
{
    int ch;
    dir *root = (dir *)malloc(sizeof(dir));
    root->isdir = 1;
    strcpy(root->name, "root");
    while (1)
    {
        printf("\nenter option \n1.create file\n2.delete file\n3.print\n4.back\nchoose  : ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            add(root, 0);
            break;
        case 2:
            delete (root);
            break;
        case 3:
            print(root->sub_dir);
            break;
        case 4:
            return;
        default:
            printf("invalid choice\n");
            break;
        }
    }
}
void heirarchy()
{
}
void main()
{
    int op;
    printf("enter options:\n1.single-level\n2.two-level\n3.heirarchical\n4.exit\nchoose  : ");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
        single();
        break;
    case 2:
        twolevel();
        break;
    case 3:
        heirarchy();
        break;
    case 4:
        exit(0);
    default:
        printf("Wrong option");
        break;
    }
}
