#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void panic(char *s)
{
	fprintf(stderr, "%s", s);
	exit(1);
}

typedef struct node{
	int data;
	struct node *next = NULL;
} node;

node *createNode(int data){
	node *ptr = malloc(sizeof(node));
	
	if (ptr == NULL)
		panic("ERROR: out of memory in createNode()\n");
	ptr->data = data;
	ptr->next = NULL;
	
	return ptr;
}


int main(void){
    
    return 0;
}
