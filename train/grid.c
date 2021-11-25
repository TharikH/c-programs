#include<stdio.h>
#define ROW 10
#define COL 10

int arr[ROW+1][COL+1];
int grid(int m,int n){
    int temp;
    if(arr[m][n] != -1){
        return arr[m][n];
    }else if(m == 0 || n==0){
        arr[m][n]=0;
        return 0;
    }else if(m==1 && n==1){
        arr[m][n]=1;
        return 1;
    }else{
        temp=grid(m-1,n)+grid(m,n-1);
        arr[m][n]=temp;
        return temp;
    }
}
void main(){
    for (int i = 0; i <= ROW; i++)
    {
        for (int j = 0; j <= COL; j++)
        {
            arr[i][j]=-1;
        }
        
    }
    
    printf("%d\n",grid(ROW,COL));
}