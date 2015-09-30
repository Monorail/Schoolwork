//real

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"
#define LEN 10
int main(void)
{
	int i; char buffer[32];

	ArrayList *L1 = createArrayList(-1);
	ArrayList *L2 = createArrayList(-1);

	FILE *ifp = fopen("names.txt", "rb");

	// Read all names from the file and add them to L1.
	while (fscanf(ifp, "%s", buffer) != EOF){
		printf("%s\n",buffer);
		put(L1, buffer);
	}

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

ArrayList *trimArrayList(ArrayList *list){
	int i;
	//returns the list if nothing needs to be trimmed
	if (list->size==list->capacity)
	return list;
	//frees the memory from the unused slots in memory
	for(i=list->size;i<list->capacity;i++)
        free(list->array[i]);
	//synchronizes the size and capacity of the arraylist
	list->capacity = list->size;
	printf("-> Trimmed ArrayList to size %d.",list->capacity);
	return list;
}



char *put(ArrayList *list, char *str){
	//returns NULL if list or str don't exist
	if (list == NULL || str == NULL)
		return NULL;
    if (list -> capacity == list->size){
        list = expandArrayList(list, (list->capacity)*2+1); //expands the arraylist if the array can't hold the new value
    }
    set(list, list->size,str);//puts the string into the array
    list->size++;//
    return list->array[list->size];
}
char *set(ArrayList *list, int index, char *str){
	if (list->capacity<index){//out of bounds check
	}
	char *strtemp = strdup(str);//set a char pointer equal to the contents of str
	//printf("%s   %s\n",str,strtemp);
	strncpy(get(list,index),strtemp,LEN);//copies contents of strtemp into the arraylist
	return get(list,index);
}
ArrayList *expandArrayList(ArrayList *list, int length){
    int i;
    if(list->capacity>=length)//returns the list untouched if it doesn't need to be expanded
        return list;
    ArrayList *ret = createArrayList(length);//create a bigger array
    for(i = 0;i<list->size;i++)//copy the strings into the new array
        strcpy(ret->array[i],list->array[i]);
    ret->size = list->size;//copy over the size to the new array
    ret->capacity = length;//copy over the capacity
    printf("-> Expanded ArrayList to size %d\n.",length);
    destroyArrayList(list);/
	return ret;
}
int removeElement(ArrayList *list, int index){
    int i;
    if (list->size<index)//checks if the index is in bounds
        return 0;
    for(i = index;i<list->size-1;i++)//moves each element back by one
        list->array[i]=list->array[i+1];
    list->size--;//decrements the size
    return 1;
}
char *insertElement(ArrayList *list, int index, char *str){
    int i;
    for(i = index;i<list->size;i++)//moves each element forward by one
        list->array[i+1] = list->array[i];
    list->array[index] = str;//sets the element at the desired position
    list->size++;//increments size
    if (strcmp(list->array[index],str) == 0)//checks if the string hasn't been set
        return NULL;
    return list->array[index];
}
void printArrayList(ArrayList *list){
    int i;
    if (list == NULL || list->size == 0){//checks if list is empty or inexistant
        printf("(empty list)\n");
        return;
    }
    //printf("Printing list where size = %d and capacity = %d\n",list->size,list->capacity);
    for (i = 0; i < list->size;i++)
        //printf("%s\n",list->array[i]);
        printf("%s\n",i,list->array[i]);//print the elements in the string

}
char *get(ArrayList *list, int index){
	if (list->size<index){//out of bounds check
		//printf("OOB, returning NULL\n");
		return NULL;
	}
	if (list == NULL)//returns NULL if the list is inexistant
        return NULL;
	return list->array[index];
}
ArrayList *createArrayList(int length){
	int i;
	ArrayList *temparr =(ArrayList *) malloc(sizeof(ArrayList));//create an ArrayList pointer checking to see if malloc was successful
	if (temparr == NULL)//checking to see if malloc was successful
		panic("malloc() returned NULL!");
	if (length<DEFAULT_INIT_LEN)//	sets length to DEFAULT_INIT_LEN if DEFAULT_INIT_LEN is bigger
		length = DEFAULT_INIT_LEN;//	
    //declaring / initializing the members
	temparr->size = 0;//initializing struct variables
	temparr->capacity = length;
	temparr->array = NULL;
	temparr->array = malloc(sizeof(char *) * length);//providing memory for the string pointers
    if (temparr->array == NULL)
		panic("malloc() returned NULL!");
	for (i = 0; i<temparr->capacity; i++){
        temparr->array[i] = malloc(sizeof(char) * LEN);//providing memory for the characters
        if (temparr->array == NULL)
            panic("malloc() returned NULL!");
	}
	temparr->capacity = length;//setting the capacity to what it actually is
	printf("-> Created new ArrayList of size %d\n.",temparr->capacity);
	return temparr;
}
ArrayList *destroyArrayList(ArrayList *list){
    int i;//must free() in the reverse order of createArrayList
	for (i = 0; i<list->size; i++){//freeing characters
        free(list->array[i]);
    }
    free(list->array);//freeing the char array
    free(list);//freeing the struct
    return NULL;
}
int getSize(ArrayList *list){
    if (list==NULL)//return -1 if the list is inexistant
        return -1;
    return list->size;
}































