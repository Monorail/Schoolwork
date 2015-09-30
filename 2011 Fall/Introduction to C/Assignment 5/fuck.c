#include <stdio.h>

void SwapIntegers ( int & a, int & b );
void main (int argc, char ** argv)
{
int a, b;
a = atoi(argv[1]);
b = atoi(argv[2]);
SwapIntegers(a, b); // Our swapping fucntion
printf("%d %d", a, b);
}

void SwapIntegers ( int & a, int & b )
{
int temp = a;
a = b;
b = temp;
}
