#include<stdio.h>
int fval(int num){
    int temp1=-1,temp2=-1,temp3=-1,count=0;
    while(num != 0){
        temp1=num%10;
        if(temp2 !=-1 && temp1 == temp2)
            return count;
        if(temp3 == temp1 && temp3!=-1)
            return count-1;
        temp3=temp2;
        temp2=temp1;
        num/=10;
        count++;
    }
    return 0;
}
void main(){
    int a=100,b=1000,count=0,temp;
    for(int i=1;i<b;i++){
        temp=1;
        count=fval(i);
        if(count >0){
            while(count-1 > 0){
                temp*=10;
                count--;
            }
            i+=temp-1;
        }else{
            printf("%d\n",i);
        }
    }
}