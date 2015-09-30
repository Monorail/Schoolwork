#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void foo(int *arr, int n){
    n=0;
    while(1){
        printf("%d\n",arr[++n]);
    }
}
int main(void){
    int *arr = malloc(sizeof(int)*5);
    int i;
    for (i = 0;i <5;i++)
        arr[i] = i;
    foo(arr,5);
    return 0;

}

