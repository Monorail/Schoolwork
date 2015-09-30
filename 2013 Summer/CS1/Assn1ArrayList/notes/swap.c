// swaps.c
// Adapted from class on May 14, 2013.

// Today we saw that if we want a function to change variables that were
// declared in main(), we need to pass the address of those variables to the
// function, not just their values. This is called pass-by-reference, as opposed
// to pass-by-value.


#include <stdio.h>

// pass-by-value function that does not swap main()'s i and j variables
void swap_a(int i, int j)
{
	int temp = i;
	i = j;
	j = temp;
	
	printf("(in swap_a) i: %d, j: %d\n", i, j);
}

// pass-by-reference function that swaps main()'s i and j variables
void swap_b(int *i, int *j)
{
	int temp = *i;
	*i = *j;
	*j = temp;

	// Notice we have to dereference i and j to print the integer values they
	// point to, because they are pointers.
	printf("(in swap_b) i: %d, j: %d\n", *i, *j);
}

int main(void)
{
	int i = 42, j = 1087;

	// Check your understanding: What do you expect the output to be below?
	// And why do we pass i and j to swap_a(), but &i and &j to swap_b()?

	swap_a(i, j);
	printf("(in main, after swap_a) i: %d, j: %d\n", i, j);

	swap_b(&i, &j);
	printf("(in main, after swap_b) i: %d, j: %d\n", i, j);

	return 0;
}
