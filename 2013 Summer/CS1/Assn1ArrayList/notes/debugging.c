// debugging.c
// Adapted from class on May 14, 2013.

// Judicious use of printf() is one way to track down a segmentation fault.
// In this program, we use printf() statements to track down a segfault in
// a modified version of pointer-corruption.c (also from May 14, 2013).

// Check your understanding: Most likely, nothing will print before we segfault
// on line 37 in this program. (At least, that's the case on my Linux and Mac
// systems.) Do you remember why?


#include <stdio.h>

int main(void)
{
	int i, a[5];
	int *p = NULL;
	
	if (p == NULL)
		printf("Initially, p is NULL.");
	
	printf("Got to this line.");
	
	// Going out of bounds like this is most likely going to corrupt our pointer.
	for (i = 0; i < 1000; i++)
		a[i] = 10087;
	
	printf("Got to this other line.");
	
	if (p != NULL)
	{
		printf("Got into the if-statement.");

		// Here's the segfault. But if get this far, why is there no output before
		// we crash?
		printf("p: %d\n", *p);
	}

	printf("Escaped the if-statement with my life.");
	
	return 0;
}
