#include <stdio.h>
#include <stdlib.h>
divFact(int, int);

int main(void){
    printf("%d\n",divFact(23,20));

    return 0;
}

int divFact(int n,int divisor){
    //Base case
    if (divisor>n)
        return 1;
    return n*divFact(n-divisor,divisor);


}
