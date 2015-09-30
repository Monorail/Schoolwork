Alex Berliner and Shayne Linhart
System Software
This program will compile from gcc.
The program itself will be printed at the beginning and the SIO output will be printed at the bottom of the program always.
If you wish to save this to a text file please use Bash's ">" operator.

All variables are initialized to 0.
The identifiers of procedures are unique throughout the entire program.

This program compiles all source files depended on into one binary file. 
It is not possible to execute the binary for one part (ie VM) individually.

The compile driver supports the following directives:
	-l : print the list of lexemes/tokens (scanner output) to the screen

	-a : print the generated assembly code (parser/codegen output) to the screen

	-v : print virtual machine execution trace (virtual machine output) to the screen

When running the program, the final argument must always be the input PL/0 code.

To compile:
gcc -o driver.o driver.c

To execute:
./driver.o <DIRECTIVES> <YOUR CODE FILE>
