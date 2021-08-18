#include<stdio.h>
#include<stdlib.h>

void main(){
    int a[]={1,2,3,4,6},lsum=0,rsum=0,i=0,j=4;
    while(i < j)
    {
        if(lsum > rsum){
            rsum+=a[j--];
        }else{
            lsum+=a[i++];
        }
    }
    if (rsum == lsum)
        printf("%d ",a[i]);

}