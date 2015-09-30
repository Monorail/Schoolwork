// pointer-corruption.c
// Adapted from class on May 14, 2013.

// When you access an array, C doesn't check whether you're going out of bounds.
// It will lead you read and write beyond the end of an array, which could
// potentially cause you to corrupt a pointer that is stored near the array in
// memory.


#include <stdio.h>

int main(void)
{
	int i, a[5];
	int *p = NULL;

	// This is just to show that p is properly initialized. There's no trick here.
	if (p == NULL)
		printf("Initially, p is NULL.\n");

	// Notice that we're going waaaaaay out of bounds here! We're writing stuff
	// in all kinds of crazy places in memory, and overwriting who-knows-what.
	for (i = 0; i < 1000; i++)
		a[i] = 10087;

	// Line 28 most likely will not print out. Why? Shouldn't p still be NULL?
	if (p == NULL)
		printf("Subsequently, p is NULL.\n");

	return 0;
}
