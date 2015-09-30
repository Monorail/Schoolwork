#include <stdio.h>

int main(void)
{
int i, a[5];

	for (i = 0; i < 5; i++)
		a[i] = i + 1;
		
	for (i = 0; i < 5; i++)
		printf("a[%d] = %d\n", i, a[i]);
	for (i = 0; i < 5; i++)
		printf("&a[%d] is %p\n", i, &a[i]);//& gets addresses of normal variables
	printf("%d\n", *a);
}
