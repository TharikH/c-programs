#include<stdio.h>

int fact(int num){
    int s=1;
    while(num){
        s*=num--;
    }
    return s;
}
void main(){
    int n,k=0,count=1;
    printf("Enter number : ");
    scanf("%d",&n);
    while(k<(n/2)){
        count+=(fact(n-k) / (fact(n-(2*k))*fact(k)));
        k++;
    }
    printf("%d\n",count);
}