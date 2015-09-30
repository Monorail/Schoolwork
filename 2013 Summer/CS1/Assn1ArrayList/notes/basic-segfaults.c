// basic-segfaults.c
// Adapted from class on May 14, 2013.

// Today we saw three basic pointer errors that can cause segmentation faults:
// (1) dereferencing an uninitialized pointer
// (2) initializing a pointer to an incompatible data type (e.g., an integer)
// (3) dereferencing a NULL pointer


#include <stdio.h>

int main(void)
{
	int i = 10087;

	// Notice that the compiler complains about what's going on with the ptr_b
	// assignment. Always heed compiler warnings and work to eliminate them!
	int *ptr_a;
	int *ptr_b = 18098;
	int *ptr_c = NULL;

	// dereferencing an uninitialized pointer
	printf("%d\n", *ptr_a);

	// initializing a pointer to an incompatible data type
	printf("%d\n", *ptr_b);

	// dereferencing a NULL pointer
	printf("%d\n", *ptr_c);

	// As far as dereferencing goes, this is a much better idea:
	ptr_a = &i;
	printf("%d\n", *ptr_a);

	// And finally, we saw that we use "%p" to print memory addresses, like so:
	printf("Address of i: %p\n", &i);
	printf("Address stored in ptr_a: %p\n", ptr_a);

	return 0;
}
