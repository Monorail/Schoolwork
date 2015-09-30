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

int main(void){
	int i;
	ArrayList *testarr = createArrayList(10);
	for(i = 0;i<testarr->capacity;i++)
        put(testarr,"hi");
    printArrayList(testarr);
    expandArrayList(testarr,30);
    trimArrayList(testarr);
    printArrayList(testarr);
    printf("MAIN: size is %d\nMAIN: cap is %d\n",testarr->size, testarr->capacity);
	return 0;
}
ArrayList *trimArrayList(ArrayList *list){
    int i;
    if (list->capacity<=list->size)
        return list;
    for(i = list->size;i<list->capacity;i++)
        free(list->array[i]);
    return list;
}
char *put(ArrayList *list, char *str){
    printf("put(): putting %s at pos %d\n",str,list->size);
	if (list == NULL || str == NULL)
		return NULL;
    if (list->capacity <= list->size){
        expandArrayList(list, ((list->capacity)*2)+1);
        list->capacity = (list->capacity)*2+1;
    }
    set(list, list->size,str);
    list->size++;
    return NULL;//list->array[list->size-1];
}
char *set(ArrayList *list, int index, char *str){
	if (list->capacity<index){//out of bounds check
		printf("OOB, returning NULL\n");
		return NULL;
	}
	if (list->size<index){
        list->size = index;
	}
	char *strtemp = strdup(str);//set a char pointer equal to the contents of str
	//printf("%s   %s\n",str,strtemp);
	strcpy(get(list,index),strtemp);//copies contents of strtemp into the arraylist
	free(strtemp);//frees strtemp
	return get(list,index);
}
//////////////////////////////////////////////    21
ArrayList *expandArrayList(ArrayList *list, int length){
	//printf("entering expandArrayList\n");
	int i;
	if (list->capacity>length){
        //printf("returning list->capacity>length\n");
		return list;
    }
	realloc(list->array,sizeof(char *) * length);

	//printf("ArrayList *temparr = createArrayList(length) done\n");
	for (i = list->size;i<length;i++){
        //list->array[i] = malloc(list->array[0]);
        realloc(list->array[i],sizeof(list->array[0]));
	}
//	for(i = 0;i<list->size;i++){
//		set(list,i, list->array[i]);
//
//	}
	return list;
}
int removeElement(ArrayList *list, int index){
    int i;
    ArrayList *temparr = createArrayList(list->capacity-1);//create a
    for (i = 0;i<index;i++){
        put(temparr,list->array[i]);
    }
    //printf("\n\n\n\print array after first loop\n");
	//printArrayList(temparr);
    for (i = index+1;i<list->size;i++){
        put(temparr,list->array[i]);
    }
    free(list);
    return temparr;
}
char *insertElement(ArrayList *list, int index, char *str){
    int i;
    ArrayList *temparr = createArrayList(list->capacity+1);//create a
    for (i = 0;i<index;i++){
        put(temparr,list->array[i]);
    }
	put(temparr,str);
    for (i = index;i<list->size-1;i++){
        put(temparr,list->array[i]);
    }
    free(list);
    return temparr;
}
void printArrayList(ArrayList *list){
    int i;
    printf("Printing list where size = %d and capacity = %d\n",list->size,list->capacity);
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
	ArrayList *temparr = malloc(sizeof(ArrayList));
	if (temparr == NULL)
		panic("malloc() returned NULL!");
	if (length<DEFAULT_INIT_LEN)//	sets length to DEFAULT_INIT_LEN if
		length = DEFAULT_INIT_LEN;//	DEFAULT_INIT_LEN is bigger

	temparr->size = 0;//initializing struct variables
	temparr->capacity = length;
	temparr->array = NULL;
	temparr->array = malloc(sizeof(char *) * LEN);
	for (i = 0; i<temparr->capacity; i++){
        temparr->array[i] = malloc(sizeof(char) * length);
	}
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



















































































































































