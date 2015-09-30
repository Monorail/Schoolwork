// memory-leak.c
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
	int i, j, num_students, num_exams, *exam_scores = NULL, sum;

	printf("How many students are in the class? ");
	scanf("%d", &num_students);

	printf("How many exams have they taken? ");
	scanf("%d", &num_exams);

	for (i = 0; i < num_students; i++)
	{
		// Re-initialize sum of exam scores for each student.
		sum = 0;

		// Create a new array in memory to input data for one student. We could
		// just use the same array instead of allocating a new one each time
		// through the for-loop, but then you wouldn't get to see what a
		// memory leak looks like and how to fix it. :)
		exam_scores = malloc(sizeof(int) * num_exams);

		if (exam_scores == NULL)
			panic("ERROR: out of memory in main()\n");

		printf("\n");

		// Input exam scores
		for (j = 0; j < num_exams; j++)
		{
			printf("What did Student #%d earn on Exam #%d: ", i + 1, j + 1);
			scanf("%d", &exam_scores[j]);
		}

		// Let's make sure everything got in there.
		for (j = 0; j < num_exams; j++)
		{
			printf("Student #%d earned %d on Exam #%d.\n", i + 1,
			       exam_scores[j], j + 1);

			sum += exam_scores[j];
		}

		if (num_exams != 0)
			printf("Student #%d's exam average: %.2f\n", i + 1,
			       (float)sum/(float)num_exams);

		// Without this free() statement, you will have a major memory leak in
		// your code. Can you see why?
		//free(exam_scores);
	}

	return 0;
}
