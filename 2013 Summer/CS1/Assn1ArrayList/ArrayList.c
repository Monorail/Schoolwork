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
	ArrayList *testarr = createArrayList(11);
	//if (destroyArrayList(testarr)==NULL)
     //	printf("List deleted successfully!");
	set(testarr,0,"bye");
	for(i=0;i<testarr->capacity-1;i++){
        set(testarr,i,"hi");
	}
	ArrayList *cpyarr = expandArrayList(testarr,20);
	cpyarr = destroyArrayList(cpyarr);
	if (cpyarr==NULL)
        printf("returned NULL!\n");
    else printf("did not return NULL");
	return 0;
}



ArrayList *expandArrayList(ArrayList *list, int length){
	int i;
	if (list->capacity>length){
		return list;
    }
	ArrayList *temparr = createArrayList(length);
	temparr->size = list->size;

	for(i = 0;i<list->size;i++){
		set(temparr, i, list->array[i]);
	}
	return temparr;
}

char *get(ArrayList *list, int index){
	if (list->size<index){//out of bounds check
		printf("OOB, returning NULL\n");
		return NULL;
	}
	return list->array[index];
}

char *set(ArrayList *list, int index, char *str){

	if (list->capacity<index){//out of bounds check
		printf("OOB, returning NULL\n");
		return NULL;
	}
	if (list->size<index)
        list->size = index;
	char *strtemp = strdup(str);//set a char pointer equal to the contents of str
	strcpy(get(list,index),strtemp);//copies contents of strtemp into the arraylist
	free(strtemp);//frees strtemp

	return get(list,index);
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
    printf("Freeing elements #0 through %d\n",(list->size-1));
	for (i = 0; i<list->size; i++){
        printf("Freeing element %d... \n",i);
        free(list->array[i]);
        printf("Complete.\n");
    }
    printf("Freeing list->array... \n");
    free(list->array);
    printf("Complete.\nFreeing list... \n");
    free(list);
    list = NULL;
    printf("Complete.\n");
    return list;
}




















































































































































