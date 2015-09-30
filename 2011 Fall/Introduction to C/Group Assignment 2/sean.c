#include <stdio.h>

int foo(int x);
int bar(int x);
int main(){

        printf("hi sean!\n");


    return 0;
}

int foo(int x){
    return x*x*x;
}


int bar(int x){
    x-=2;
    return x;
}

/*
1.what is the output when x == 0?
2.what is the output when x == 2?
*/
