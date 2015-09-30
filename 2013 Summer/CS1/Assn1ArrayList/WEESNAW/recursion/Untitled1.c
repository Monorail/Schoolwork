#include <stdio.h>
#include <stdlib.h>

int foo(int *arr,int n){
    //base
    if (n==1)
        return arr[0];
    return arr[n-1] + (n-1)/n*foo(arr[n-1],n-1);
}

int main(void){
    int i;
    int *arr;
    for (i = 0;i<7;i++){
        arr[i] = malloc(sizeof(int));
        arr[i]=i;
    }
    printf("wtf\n");
    return 0;
}
