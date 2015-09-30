// pointer-arithmetic.c
// Adapted from class on May 16, 2013.

#include <stdio.h>

// SUGGESTED EXERCISES:
//
// 1.) Write a function, printA(char *s), that prints the string str
//     WITHOUT using the strlen() function. HINT: Remember strings are
//     terminated with the null sentinel ('\0') in C.
//
// 2.) Write a function, printB(char *s), that prints the string str WITHOUT
//     using the strlen() function, and with the following restriction: the ONLY
//     variable you can declare inside the function is: char *ptr. (You may not
//     use any global variables to help you out with this, either!)

int main(void)
{
	int i, a[5], *ptr;

	// This makes sense, right? We saw that 'a' is a memory address (int *), and
	// we know that 'ptr' is designed to hold memory addresses.
	ptr = a;

	// We can now treat 'ptr' as a synonym for 'a'.
	for (i = 0; i < 5; i++)
		ptr[i] = i + 1;

	// Let's test out that theory by printing each a[i] now.
	for (i = 0; i < 5; i++)
		printf("a[%d] = %d\n", i, a[i]);

	// Now, if an address is always 32 or 64 bits (depending on your system
	// architecture), why don't we just have a generic "memory address" type?
	// Why do we need to declare (int *) or (char *) instead of just (pointer)?

	// What happens if we do this?
	printf("\n");
	printf("  ptr: %p\n",   ptr);
	printf("++ptr: %p\n", ++ptr);

	// Let's reset ptr and see another example.
	ptr = a;
	
	// The same is true even if we print this as an integer using typecasting:
	printf("\n");
	printf("  ptr: %d\n", (int)  ptr);
	printf("++ptr: %d\n", (int)++ptr);

	// This also holds if we try to jam an integer into our integer pointer.
	// (This will generate a compiler warning.)
	printf("\n");
	ptr = 42;
	++ptr;
	printf("42 + 1 = %d?!\n", (int)ptr);

	return 0;
}
