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
    if (!isexist(root->sub_dir, name) && strcmp(name,"")!=0)
    {
        dir *new = (dir *)malloc(sizeof(dir));
        new->isdir = isdir;
        new->next = root->sub_dir;
        new->sub_dir=NULL;
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
    dir *ptr = root;
    while (ptr != NULL)
    {
        if (strcmp(ptr->name, name)==0 && ptr->isdir==1)
        {
            return ptr;
        }
        ptr=ptr->next;
    }
    return ptr;
}
dir *findParentPath(dir *root,char **path){
    dir *ptr=root;
    for(int i=0;i<10;i++){
        ptr=findParent(ptr,path[i]);
        if(ptr == NULL){
            break;
        }
        if(strcmp(path[i+1],"")==0){
            break;
        }else{
            ptr=ptr->sub_dir;
        }
    }
    return ptr;
}
void deleteAll(dir* root){
    if(root == NULL){
        return ;
    }
    else{
        if(root->isdir == 1){
            deleteAll(root->sub_dir);
        }
        deleteAll(root->next);
        free(root);
        root=NULL;
    }
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
        if(ptr->isdir)
            deleteAll(ptr->sub_dir);
        free(ptr);
        ptr=NULL;
        ptr1=NULL;
    }
    while (ptr != NULL)
    {
        if (strcmp(ptr->name, name) == 0)
        {
            flag = 1;
            ptr1->next = ptr->next;
            if(ptr->isdir)
                deleteAll(ptr->sub_dir);
            free(ptr);
            ptr1=NULL;
            ptr=NULL;
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
        printf(" %s(%d) ", ptr->name,ptr->isdir);
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
            ptr = findParent(root->sub_dir, name);
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
            ptr = findParent(root->sub_dir, name);
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
            ptr = findParent(root->sub_dir, name);
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
char **splitPath(char *s){
    int size=10,k=0,i=0,j=0;
    char **arr=(char **)malloc(sizeof(char *)*size);

    for(k=0;k<size;k++){
        *(arr+k)=(char *)malloc(sizeof(char) * size);
    }
    for(k=0;s[k]!='\0';k++){
        if(s[k] !='/'){
            arr[i][j++]=s[k];
        }else{
            arr[i][j]='\0';
            i++;
            j=0;
        }
    }
    return arr;
}
void heirarchy()
{
    int ch;
    char name[20];
    char path[100];
    char **path_array;
    dir *root = (dir *)malloc(sizeof(dir)), *ptr;
    strcpy(root->name,"root");
    root->isdir=1;
    while (1)
    {
        printf("\nenter option \n1.create file\n2.delete file/dir\n3.create dir\n4.print\n5.back\nchoose  : ");
        scanf("%d", &ch);
        printf("Specify path :");
        scanf(" %s",path);
        path_array=splitPath(path);
        ptr=findParentPath(root,path_array);
        if(ptr !=NULL){
        switch (ch)
        {
        case 1:
            add(ptr,0);
            break;
        case 2:
            delete(ptr);
            break;
        case 3:
            add(ptr,1);
            break;
        case 4:
            print(ptr->sub_dir);
            break;
        case 5:
            return;
        default:
            break;
        }
        }else{
            printf("\npath not correct\n");
        }

    }
}
void main()
{
    while(1){
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
}
