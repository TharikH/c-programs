#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node *next;
}*head;
struct node * reverse(struct node *cur){
    struct node *prev,*next;
    while(cur){
        next=cur->next;
        cur->next=prev;
        prev=cur;
        cur=next;
    }
    return prev;
}
void display(struct node *ptr){
    while (ptr)
    {
        printf("%d ",ptr->data);
        ptr=ptr->next;
    }
    printf("\n");
}
void main(){
    head=(struct node *)malloc(sizeof(struct node));
    struct node *temp,*ptr,*rev;
    int n;
    scanf("%d",&n);
    ptr=head;
    scanf("%d",&ptr->data);
    n--;
    for (int i = 0; i < n; i++)
    {
        temp=malloc(sizeof(struct node));
        scanf("%d",&temp->data);
        ptr->next=temp;
        ptr=ptr->next;
    }
    display(head);
    rev=reverse(head,NULL);
    display(rev);

}