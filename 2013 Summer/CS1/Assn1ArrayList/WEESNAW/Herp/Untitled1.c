#include <stdlib.h>
#include <stdio.h>
int recur(int);
int main(void){
    printf("%d\n",recur (0));
    return 0;
}


int recur(int n){
    //Base
    if(n==1 || n==0)
        return 1;
    if (n%2 == 1)
        n--;
    return n * recur(n-2);
}
