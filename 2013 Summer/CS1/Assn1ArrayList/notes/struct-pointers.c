// struct-pointers.c
// Adapted from class on May 16, 2013.

#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LEN 30
#define PID_LEN      8

typedef struct Student
{
	// Notice that we're leaving room for all characters PLUS a null sentinel.
	char f_name[MAX_NAME_LEN + 1];
	char l_name[MAX_NAME_LEN + 1];
	char ucf_id[PID_LEN + 1];
} Student;

// Pass a Student struct to this function. Access individual members of the
// struct using the dot (.) operator. We use the dot operator if we have an
// actual struct. If we just have a POINTER to a struct, we use the arrow (->)
// operator (see print_student_alternative() for an example).
void print_student(Student s)
{
	printf("\nYou entered: %s %s (ID: %s)\n", s.f_name, s.l_name, s.ucf_id);
}

// Don't pass the whole struct to this function (which could potentially be
// a LOT of data). Just pass a struct POINTER instead (which is a small amount
// of data -- just a single memory address). Then use the arrow (->) operator.
// to access struct members instead of the dot (.) operator.
void print_student_alternative(Student *s)
{
	printf("\nYou entered: %s %s (ID: %s)\n", s->f_name, s->l_name, s->ucf_id);
}

// Alternatively, you could first dereference the variable s. Since (*s) takes
// you to the actual struct (and is not just a POINTER to a struct), we can use
// the dot (.) operator instead of the arrow (->) operator.
void print_student_alternative2(Student *s)
{
	printf("\nYou entered: %s %s (ID: %s)\n", (*s).f_name, (*s).l_name, (*s).ucf_id);
}

int main(void)
{
	Student s;
	int width;

	// Check your understanding: Why am I not using the & operator in the scanf()
	// statements below?

	printf("Enter student's first name: ");
	scanf("%s", s.f_name);

	printf("Enter student's last name: ");
	scanf("%s", s.l_name);

	printf("Enter student's ID: ");
	scanf("%s", s.ucf_id);

	// Print student information (output should be identical for all functions).
	print_student(s);
	print_student_alternative(&s);
	print_student_alternative2(&s);

	// CHECK YOUR UNDERSTANDING:
	// Suppose we declare Student *s instead of Student s. How would you use
	// malloc() to create a new Student struct for s to point to? And then how
	// would you call print_student() and print_student_alternative()?


	return 0;
}
