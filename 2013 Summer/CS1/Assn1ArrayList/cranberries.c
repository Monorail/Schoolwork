#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"
#define LEN 10
void panic(char *s)
{
	fprintf(stderr, "%s", s);
	exit(1);
}
int main(void){
	ArrayList *testarr = createArrayList(-1);
	if (destroyArrayList(testarr)==NULL)
		printf("Array was deleted successfully!\n");
	//else printf("The array lives!\n");
	testarr->array[0]="hi";
	printf("%s\n",testarr->array[0]);
	//testarr = destroyArrayList(testarr);
	//printf("%s\n",testarr->array[0]);
	return 0;
}

ArrayList *createArrayList(int length){
	ArrayList *arrptr=(ArrayList *) malloc(sizeof(ArrayList));
	if (arrptr == NULL)
		panic("malloc() returned NULL!");
	if (length<DEFAULT_INIT_LEN)//	sets length to DEFAULT_INIT_LEN if
		length = DEFAULT_INIT_LEN;//	DEFAULT_INIT_LEN is bigger

	arrptr->size = 0;//initializing struct variables
	arrptr->capacity = length;
	int i;

	for (i = 0; i < length; i++){
		arrptr->array =  malloc(sizeof(char *) * LEN);
		arrptr->array[i] = "hi";
		printf("%s\n",arrptr->array[i]);

		if (arrptr->array[i] == NULL)
			panic("ERROR: out of memory in main()\n");
	}
	printf("-> Created new ArrayList of size %d\n",arrptr->size);
	arrptr->array[0]="hif";
	return arrptr;
}

ArrayList *destroyArrayList(ArrayList *list){
	
	return list;
}
/*
ArrayList *expandArrayList(ArrayList *list, int length)
{

	return
}


typedef struct ArrayList
{
	// We will store an array of strings (i.e., an array of char arrays)
	char **array;

	// Size of list (i.e., number of elements that have been added to the array)
	int size;

	// Length of the array (i.e., the array's current maximum capacity)
	int capacity;

} ArrayList;

*/














