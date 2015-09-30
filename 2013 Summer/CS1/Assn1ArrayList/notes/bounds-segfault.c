// bounds-segfault.c
// Adapted from class on May 14, 2013.

// Notice that even going too far beyond the bounds of an array can put us
// into uncharted territory and cause a segmentation fault.


#include <stdio.h>
#include <limits.h>

int main(void)
{
	int i, a[5];
	int *p = NULL;

	// INT_MAX is defined in limits.h. It's the biggest integer C can handle.
	printf("The loop will go from i = 0 to %d...\n", INT_MAX - 1);

	for (i = 0; i < INT_MAX; i++)
		a[i] = 10087;

	return 0;
}
