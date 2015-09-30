//Alex Berliner
//PID: a2737438

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"
#define LEN 10
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


ArrayList *trimArrayList(ArrayList *list){
	int i;
	//returns the list if nothing needs to be trimmed
	for(i=list->size;i<list->capacity;i++)
	free(list->array[i]);
	//frees the memory from the unused slots in memory
	list->capacity = list->size;
	//synchronizes the size and sets capacity of the arraylist	
	printf("-> Trimmed ArrayList to size %d.\n",
			list->capacity);
		return list; 					
	
}
char *put(ArrayList *list, char *str){
	//returns NULL if list or str don't exist
	if (list == NULL || str == NULL)
		return NULL;
	if (list->capacity == list->size){
		//expands the arraylist if the array can't hold the new value
		list = expandArrayList(list, (list->capacity)*2+1);
	}
	set(list, list->size,str);
	list->size++;
	return list->array[list->size-1];
}
char *set(ArrayList *list, int index, char *str){
	//out of bounds check
	if (list->capacity<index){
		return NULL;
	}
	//set a char pointer equal to the contents of str
	char *strtemp = strdup(str);
	//printf("%s   %s\n",str,strtemp);
	//copies contents of strtemp into the arraylist
	strcpy(get(list,index),strtemp);
	free(strtemp);//frees strtemp
	return get(list,index);
}
ArrayList *expandArrayList(ArrayList *list, int length){
	int i;
	//returns the list untouched if it doesn't need to be expanded
	if(list->capacity>=length)
		return list;
		//create a bigger array
	ArrayList *ret = createArrayList(length);
	//copy the strings into the new array
	for(i = 0;i<list->size;i++)
		strcpy(ret->array[i],list->array[i]);
	//copy over the size to the new array	
	ret->size = list->size;
	//copy over the capacity
	ret->capacity = length;
	printf("-> Expanded ArrayList to size %d.\n",length);
	return ret;
}
int removeElement(ArrayList *list, int index){
	int i;
	//checks if the index is in bounds
	if (list->size<index)
		return 0;
	//moves each element back by one	
	for(i = index;i<list->size-1;i++)
		list->array[i]=list->array[i+1];
	list->size--;//decrements the size
	return 0;
}
char *insertElement(ArrayList *list, int index, char *str){
	int i;
	//moves each element forward by one
	for(i = list->size;i>index;i--){
		list->array[i] = list->array[i-1];
	}
	//sets the element at the desired position
	list->array[i]=str;
	//increments size
	list->size++;
	//checks if the string hasn't been set
	if (strcmp(list->array[index],str) == 0)
		return NULL;
	return list->array[index];
}
void printArrayList(ArrayList *list){
	int i;
	//checks if list is empty or inexistant
	if (list == NULL || list->size == 0){
		printf("(empty list)\n");
		return;
	}
	for (i = 0; i < list->size;i++)
		//print the elements in the string
		printf("%s\n",list->array[i]);

}
char *get(ArrayList *list, int index){
	if (list->size<index){//out of bounds check
		//printf("OOB, returning NULL\n");
		//returns NULL if the list is inexistant
		return NULL;
	}
	
	return list->array[index];
}
ArrayList *createArrayList(int length){
	int i;
	//create an ArrayList pointer
	ArrayList *temparr =(ArrayList *) malloc(sizeof(ArrayList));
	//checking to see if malloc was successful
	if (temparr == NULL){
		fprintf(stderr, "malloc failed\n");
		exit(1);
	}
	//sets length to DEFAULT_INIT_LEN if DEFAULT_INIT_LEN is bigger
	if (length<DEFAULT_INIT_LEN)
		length = DEFAULT_INIT_LEN;
	//initializing struct variables
	temparr->size = 0;
	temparr->capacity = length;
	temparr->array = NULL;
	//providing memory for the string pointers
	temparr->array = malloc(sizeof(char *) * length);
	for (i = 0; i<temparr->capacity; i++){
	//providing memory for the characters
		temparr->array[i] = malloc(sizeof(char) * LEN);
	}
	//setting the capacity to what it actually is
	temparr->capacity = length;
	printf("-> Created new ArrayList of size %d.\n",temparr->capacity);
	return temparr;
}
ArrayList *destroyArrayList(ArrayList *list){
	int i;
	//must free() in the reverse order of createArrayList
	for (i = 0; i<list->size; i++){
		free(list->array[i]);
	}
	//freeing the char array
	free(list->array);
	//freeing the struct
	free(list);
	return list;
}
int getSize(ArrayList *list){
	//return -1 if the list is inexistant
	if (list==NULL)
		return -1;
	return list->size;
}
