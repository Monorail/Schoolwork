// dynamic-memory.c
// Adapted from class on May 16, 2013.

#include <stdio.h>
#include <stdlib.h>

void panic(char *s)
{
	fprintf(stderr, "%s", s);
	exit(1);
}

int main(void)
{
	int i, n, *ptr, sum;

	// Sometimes we don't know how big of an array we need until runtime.
	// Let's ask the user.
	printf("How many exams have been taken? ");
	scanf("%d", &n);

	// Now let's create an array of n integers at runtime. malloc() will do that
	// for us. It needs to know how big each element in the array is, as well as
	// how many elements we want to store. Then it finds a contiguous block of
	// memory that's that size, gives you the block's address, and lets you play
	// with it. Be sure to include stdlib.h if you want to use malloc().
	ptr = malloc(sizeof(int) * n);

	// Some compilers want you to typecast malloc()'s return value, like so:
	// ptr = (int *)malloc(sizeof(int) * n);

	// NOTE: A common pitfall is to do malloc(sizeof(n)) or some such thing.
	//       Please master malloc() ASAP. You'll have to use it on your exams!

	// NOTE: calloc() does what malloc() does, except it initializes all values
	//       to zero, and you call it a bit differently: calloc(n, sizeof(int))

	// If malloc() fails to find a block as big as you need, it returns NULL.
	// This is very uncommon, but we check just to be on the safe side.
	if (ptr == NULL)
		panic("ERROR: out of memory in main()\n");

	// Now, we can proceed as before.
	for (i = 0; i < n; i++)
	{
		printf("What did the student earn on Exam #%d? ", i + 1);
		scanf("%d", &ptr[i]);
	}

	// Let's make sure everything got in there.
	for (i = 0; i < n; i++)
	{
		printf("Student earned %d on Exam #%d.\n", ptr[i], i + 1);
		sum += ptr[i];
	}

	if (n != 0)
		printf("Student's exam average: %.2f\n", (float)sum/(float)n);


	// CHECK YOUR UNDERSTANDING:
	// What if you wanted a string (i.e., an array of chars)? How does the
	// malloc() statement look different from the one above? Assume we want to
	// store a string of 5 characters, like "hello".


	return 0;
}
