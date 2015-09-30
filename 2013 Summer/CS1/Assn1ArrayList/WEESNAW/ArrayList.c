//linux seal of approval :D

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"
#define LEN 10
void panic(char *s)
{
	fprintf(stderr, "%s", s);
	exit(1);
}
void psc(ArrayList *list){
    printf("size is %d and capacity is %d\n",list->size,list->capacity);
}
ArrayList *retarr(ArrayList *list){

    return list;
}
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

    for(i=list->size;i<list->capacity;i++)
        free(list->array[i]);
    list->capacity = list->size;
    printf("-> Trimmed ArrayList to size %d.\n",list->capacity);
    return list;
}
char *put(ArrayList *list, char *str){
	if (list == NULL || str == NULL)
		return NULL;
    if (list->capacity == list->size){

        list = expandArrayList(list, (list->capacity)*2+1);
    }
    set(list, list->size,str);
    list->size++;
    return list->array[list->size-1];
}
char *set(ArrayList *list, int index, char *str){
	if (list->capacity<index){//out of bounds check
		return NULL;
	}
	char *strtemp = strdup(str);//set a char pointer equal to the contents of str
	//printf("%s   %s\n",str,strtemp);
	strcpy(get(list,index),strtemp);//copies contents of strtemp into the arraylist
	free(strtemp);//frees strtemp
	return get(list,index);
}
ArrayList *expandArrayList(ArrayList *list, int length){
    int i;
    if(list->capacity>=length)
        return list;
    ArrayList *ret = createArrayList(length);
    for(i = 0;i<list->size;i++)
        strcpy(ret->array[i],list->array[i]);
    ret->size = list->size;
    ret->capacity = length;
    printf("-> Expanded ArrayList to size %d.\n",length);
    //destroyArrayList(list);//Not working..
	return ret;
}
int removeElement(ArrayList *list, int index){
    int i;
    for(i = index;i<list->size-1;i++)
        list->array[i]=list->array[i+1];
    list->size--;
    return 0;
}
char *insertElement(ArrayList *list, int index, char *str){
    int i;
    for(i = list->size;i>index;i--){
        list->array[i] = list->array[i-1];
    }
    list->array[i]=str;
    list->size++;
    return list->array[index];
}
void printArrayList(ArrayList *list){
    int i;
    //printf("Printing list where size = %d and capacity = %d\n",list->size,list->capacity);
    for (i = 0; i < list->size;i++)
        //printf("%s\n",list->array[i]);
        printf("#%d: %s\n",i,list->array[i]);

}
char *get(ArrayList *list, int index){
	if (list->size<index){//out of bounds check
		printf("OOB, returning NULL\n");
		return NULL;
	}
	return list->array[index];
}
ArrayList *createArrayList(int length){
	int i;
	ArrayList *temparr =(ArrayList *) malloc(sizeof(ArrayList));
	if (temparr == NULL)
		panic("malloc() returned NULL!");
	if (length<DEFAULT_INIT_LEN)//	sets length to DEFAULT_INIT_LEN if
		length = DEFAULT_INIT_LEN;//	DEFAULT_INIT_LEN is bigger

	temparr->size = 0;//initializing struct variables
	temparr->capacity = length;
	temparr->array = NULL;
	temparr->array = malloc(sizeof(char *) * length);
	for (i = 0; i<temparr->capacity; i++){
        temparr->array[i] = malloc(sizeof(char) * LEN);
	}
	temparr->capacity = length;
	printf("-> Created new ArrayList of size %d.\n",temparr->capacity);
	return temparr;
}
ArrayList *destroyArrayList(ArrayList *list){
    int i;
	for (i = 0; i<list->size; i++){
        free(list->array[i]);
    }
    free(list->array);
    free(list);
    return list;
}
int getSize(ArrayList *list){
    if (list==NULL)
        return -1;
    return list->size;
}

















































































































































