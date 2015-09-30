// string-segfault.c
// Adapted from class on May 14, 2013.

// Today we saw that strings in C need space for the null terminator, '\0'.
// (This is also refered to as the "null sentinel.") Recall that C allows you to
// write beyond the end of an array, so if you write a string that is too long,
// you could venture into other parts of memory and corrupt pointers or create
// a direct segmentation fault.

// THIS IS ONE OF THE LEADING CAUSES OF SEGFAULTS AND MISCELLANEOUS MEMORY-
// RELATED HORRIBLENESS IN C.


#include <stdio.h>
#include <string.h>

int main(void)
{
	char str1[5];
	char str2[5];

	// This is so dangerous! You just wrote past the end of the array because
	// there wasn't enough space in str1 for the null terminator, '\0'.
	strcpy(str1, "hello");

	// This causes some nasty problems on Mac and Linux. What about Windows?
	// This is problematic even if you comment out strcpy(str1, "hello") above.
	strcpy(str2, "This is quite the long string, don't you think?");

	return 0;
}
