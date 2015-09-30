// file-read.c
// Adapted from class on May 14, 2013.

// We saw that one of the most sneaky (because we never expect this to happen!)
// causes of segmentation faults is a NULL file pointer. In this program, we
// check our file pointer before reading from the file, and we print the current
// working directory so we can check the path where the file we're trying to
// read should be stored.

// We also see that quoted strings are treated like memory addresses in C. For
// example, the panic() function requires a (char *) as its argument, which is
// a memory address. In main(), I call panic() with a quoted string as its
// argument. And it works. This implies that a quoted string evaluates to a
// memory address in C.


// Check your understanding: Why have I included each of these header files?
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// This function is a bit tongue-in-cheek.
void panic(char *s)
{
	// Print to stderr, just in case normal output is being redirected to a file.
	fprintf(stderr, "%s", s);

	// Exit with a non-normal return value. exit() is defined in stdlib.h.
	exit(1);
}

// This function should print the current working directory to the screen.
// You need to include unistd.h in order to call the getcwd() function.
void pwd(void)
{
	char cwd[1024];

	// getcwd() returns NULL if it can't stat the current working directory
	if (getcwd(cwd, 1024) == NULL)
		fprintf(stderr, "Working directory: (unknown)\n");
	else
		fprintf(stderr, "Working directory: %s\n", cwd);
}

int main(void)
{
	char buffer[100];
	FILE *ifp = fopen("input.txt", "r");

	// Print the current working directory. Try this out at home.
	pwd();

	// Check whether your file opened successfully. It's so easy to assume a
	// file opened successfully and then spend an hour trying to figure out why
	// your code is segfaulting.
	if (ifp == NULL)
		panic("ERROR: could not open file in main()\n");

	// Read strings into the buffer until we hit the end of the file.
	while (fscanf(ifp, "%s", buffer) != EOF)
	{
		// Check your understanding: Even if the input file has the word
		// "Szumlanski" in it, we'll never print out "Found the name I wanted!"
		// Why is that, and how can you fix the problem?
		if (buffer == "Szumlanski")
			printf("Found the name I wanted!\n");
	}

	// It's good practice close files when you're finished with them.
	fclose(ifp);

	return 0;
}
