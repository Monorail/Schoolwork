// arrays-and-pointers.c
// Adapted from class on May 16, 2013.

#include <stdio.h>

int main(void)
{
	int i, a[5];

	for (i = 0; i < 5; i++)
		a[i] = i + 1;

	// An integer takes up 32 bits (4 bytes) in C, so the address of each
	// integer in an array is greater than the previous index's address by 4.
	//
	// Note that, in C, arrays are always contiguous blocks in memory.
	//
	//   0x10   0x14   0x18   0x1c   0x20
	//   +------+------+------+------+------+
	//   |  1   |  2   |  3   |  4   |  5   |
	//   +------+------+------+------+------+
	//     a[0]   a[1]   a[2]   a[3]   a[4]

	// No surprises here...
	for (i = 0; i < 5; i++)
		printf("a[%d] = %d\n", i, a[i]);

	// Let's take a look at those memory addresses!
	for (i = 0; i < 5; i++)
		printf("&a[%d] is %p\n", i, &a[i]);

	// But, what is a itself (without an index)? This line yields a compiler
	// warning and the output isn't "1", so we can infer that a is not
	// synonymous with a[0].
	printf("%d\n", a);

	// This is the answer. a is treated as an address (a pointer!) in C.
	// This is the base address for the array, which is also &a[0].
	printf("%p\n", a);

	if (&a[0] == a)
		printf("Yes, they're equal!\n");

	return 0;
}
