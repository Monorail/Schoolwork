#include <stdio.h>

int foo(int x);
int bar(int x);
int main(){
    int x;
    scanf("%d",&x);
    if ((x = bar(x)) && (x = foo(x)));
        printf("x = %d",x);


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
1.what is the output when x is initially 2?
A.0
B.2
C.8
D.No output

2.what is the output when x is initially 4?
A.0
B.2
C.8
D.No output
*/
