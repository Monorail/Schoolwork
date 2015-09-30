#include <stdio.h>
#include <string.h>
#include "ArrayList.h"

int main(void)
{
	int i; char buffer[32];

	ArrayList *L1 = createArrayList(-1);
	ArrayList *L2 = createArrayList(-1);

	FILE *ifp = fopen("names.txt", "rb");

	// Read all names from the file and add them to L1.
	while (fscanf(ifp, "%s", buffer) != EOF)
		put(L1, buffer);

	// Add the names to L2 in reverse order.
	for (i = getSize(L1) - 1; i >= 0; i--)
		put(L2, get(L1, i));

	// Print the contents of L1.
	printf("\n-- LIST 1: --\n");
	printArrayList(L1);

	// Print the contents of L2.
	printf("\n-- LIST 2 (First Names): --\n");
	printArrayList(L2);

	// Swap last names with first names in L2.
	for (i = 0; i < getSize(L2); i++)
	{
		if (strcmp(get(L2, i), "Sean") == 0)
			set(L2, i, "Szumlanski");
		else if (strcmp(get(L2, i), "Adam") == 0)
			set(L2, i, "Bouters");
		else if (strcmp(get(L2, i), "Antoniya") == 0)
			set(L2, i, "Petkova");
		else if (strcmp(get(L2, i), "Ashkan") == 0)
			set(L2, i, "Paya");
		else if (strcmp(get(L2, i), "Grant") == 0)
			set(L2, i, "Van Horn");
	}

	// Print the contents of L2.
	printf("\n-- LIST 2 (Last Names): --\n");
	printArrayList(L2);

	// Print L1 (in reverse order) and L2, to match up first and last names.
	printf("\n-- COMBINED LISTS (First and Last Names): --\n");
	for (i = 0; i < getSize(L2); i++)
		printf("%s %s\n", get(L1, getSize(L1) - 1 - i), get(L2, i));

	// Add elements from L1 to the end of L1 (in reverse order).
	printf("\n");
	for (i = getSize(L1) - 1; i >= 0; i--)
		printf("Adding %s to L1 ...\n", put(L1, get(L1, i)));

	// Print the contents of L1.
	printf("\n-- LIST 1: --\n");
	printArrayList(L1);

	// Insert a string at the beginning of list L1.
	insertElement(L1, 0, "List of Names:");

	// Print the contents of L1.
	printf("\n-- LIST 1: --\n");
	printArrayList(L1);

	// Remove all elements from L1.
	while (getSize(L1))
		removeElement(L1, 0);

	// Print L1, which is now an empty list.
	printf("\n-- LIST 1: --\n");
	printArrayList(L1);

	// Destroy our lists.
	L1 = destroyArrayList(L1);
	L2 = destroyArrayList(L2);

	// Make sure L1 is good and destroyed (and that destroyArrayList doesn't
	// segfault when passed a NULL pointer).
	L1 = destroyArrayList(L1);

	// Print the empty lists one last time.
	printf("\n-- LIST 1: --\n");
	printArrayList(L1);

	printf("\n-- LIST 2: --\n");
	printArrayList(L2);

	return 0;
}
