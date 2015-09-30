#include <stdio.h>
#include "ArrayList.h"

int main(void)
{
	ArrayList *L1 = createArrayList(-1);

	// Trim array list. This should reduce its capacity to 0.
	trimArrayList(L1);

	// Trim again. This should produce no output since capacity is already 0.
	trimArrayList(L1);

	// Print the empty list.
	printArrayList(L1);
	printf("Size of list: %d\n", getSize(L1));

	// Destroy array list. Hopefully this won't segfault.
	L1 = destroyArrayList(L1);

	// Print the empty list.
	printArrayList(L1);
	printf("Size of list: %d\n", getSize(L1));

	// Since L1 has been destroyed and is now NULL, the put() function should
	// return NULL
	if (put(L1, "Hello, world!\n") == NULL)
		printf("Awesome!\n");
	else
		printf("Not so awesome!\n");

	// Create new list and add strings to the end. Print out the strings we're
	// adding (to ensure put() is returning pointers to those strings).
	printf("%s\n", put(L1 = createArrayList(-1), "Hello,"));
	printf("%s\n", put(L1, "world!"));

	// Print L1 again.
	printf("Array list contents:\n");
	printArrayList(L1);

	L1 = destroyArrayList(L1);

	return 0;
}
