#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node *next;
}*head;
void reverse(struct node *cur,struct node *prev){
    if(cur){
        reverse(cur->next,cur);
        cur->next=prev;
    }else{
        head=prev;
    }
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
    struct node *temp,*ptr;
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
    reverse(head,NULL);
    display(head);

}