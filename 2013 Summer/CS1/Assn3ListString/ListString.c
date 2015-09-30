//Alex Berliner
//a2737438
#include "ListString.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

node *destroyList(node *head){//TA's code
	node *temp = NULL;
	while (head != NULL){
		temp = head;
		head = head->next;
		free(temp);
	}
	return NULL;
}
node *createNode(char data){//prof's code
	node *ptr = malloc(sizeof(node));
	ptr->data = data;
	ptr->next = NULL;
	return ptr;
}

node *insert(node *head, char data){//TA code
	node *ptr = NULL;
	if (head == NULL)
		return createNode(data);
	for (ptr = head; ptr->next != NULL; ptr = ptr->next);
	ptr->next = createNode(data);
	return head;
}
void printList(node *head){//TA's code
	node *ptr = NULL;
	if (head == NULL){
		printf("(empty string)\n");
		return;
	}
	for (ptr = head; ptr != NULL; ptr = ptr->next)
		printf("%c", ptr->data);
	printf("\n");
}
node *frontInsert(node *head, char data){//prof's code
	node *ptr = createNode(data);
	ptr->next = head;
	return ptr;
}


node *deleteNext(node *head){
	//deletes the element after the head
	if(head == NULL)
		return NULL;
	if(head->next == NULL)
		return head;
	//sets the next element to the one after the one to be deleted
	node *del = head->next;
	head->next=head->next->next;
	free(del);
	return head;
}


int main(int argc, char **argv){
	int debug = 0;
	int mainCtr=0;
	char input[1023];
	char *str = "qwertyuiop";
	strcpy(input,argv[1]);
	FILE* ifp;
	ifp = fopen(input, "r");
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file in.list!\n");
	}
	int ctr= 0;
	node *head;
	fscanf(ifp,"%s", input);
	head = stringToList(input);
	//scanning through the file
	while(fscanf(ifp, "%s", input)!=EOF){
		if (debug) printf("\n\ninput: \"%s\"\n",input);
		if (debug)printf("before: ");
		if (debug)printList(head);
		if(!strcmp(input, "@")){
			int intCtr = 0;
			if (debug) printf("@(%d): replace\n",ctr++);
			char key;
			char repStr[1023];
			//read in key and string
			fscanf(ifp," %c",&key);
			fscanf(ifp,"%s", repStr);
			if (debug) printf("char: |%c| str: |%s|\n",key,repStr);
			//replace the key with string
			head = replaceChar(head,key,repStr);
		}
		else if(!strcmp(input, "-")){
			//deletes all instances of the key
			char key;
			fscanf(ifp," %c",&key);
			if (debug) printf("-(%d): delete instances of %c\n",ctr++,key);
			head = replaceChar(head,key,NULL);
		}
		else if(!strcmp(input, "~")){
			//reverses the list
			if (debug) printf("~(%d): reverse\n",ctr++);
			head = reverseList(head);
		}
		else if(!strcmp(input, "!")){
			//prints the linked list
			if (debug) printf("!(%d): print\n",ctr++);
			printList(head);
		}
		if (debug)printf("after: ");
		if (debug) printList(head);
	}
	destroyList(head);
	return 0;
}
node *replaceChar(node *head, char key, char *str){
	int debug = 0;
	if (head == NULL)
		return NULL;
	if (str == NULL){
		if (debug)printf("deleting key\n");
	}
	node *mainHead, *mainEnd, *repHead, *repEnd, *iterPtr;
	//create a temp head so all elements can be referenced with node->next
	head = frontInsert(head, 's');
	//iterPtr is used to keep track of where in the list we are, the iterator pointer
	iterPtr = head;
	if (debug)printf("Entering while\n");
	//breaks when the next element of the list is NULL
	while(iterPtr->next != NULL){
		if (debug)printf("looking at %c\n",iterPtr->next->data);
		if(iterPtr->next->data == key){
			if (debug)printf("Key found\n");
			//str is the thing to insert, if it's null it deletes the key instead
			if(str!=NULL){
				if (debug)printf("str isnt null\n");
				//replace key char with string
				//keep track of start loc in LL
				mainHead = iterPtr;
				//record position after the replaced char
				mainEnd = iterPtr->next->next;
				if (debug)printf("setting mainEnd\n");
				//create LL from string
				repHead = stringToList(str);
				if (debug)printf("Making rephead\n");
				repEnd = repHead;
				//find end of the replacement list
				if (debug)printf("Finding repEnd\n");
				while(repEnd->next!=NULL)
					repEnd=repEnd->next;
				//set the key element to the string head
				iterPtr->next = repHead;
				//link the end of the new string to the main list
				repEnd->next = mainEnd;
				//update the iterator
				iterPtr=repEnd;
			}else{
				if (debug)printf("deleting iterptr next\n");
				iterPtr = deleteNext(iterPtr);
			}
			if (debug)printf("next\n");
				
		}
		else{
			if (debug)printf("I am the walrus\n");
			iterPtr = iterPtr->next;
			if (debug)printf("moving on\n");
		}
		if (debug)printf("end result:\n");
		if (debug)printList(head);
		if (debug)printf("\n");
		if (debug)printf("wazzooooo\n");
	}
	if (debug)printf("out of loop\n");
	//clean up the temp head
	node *freeptr = head;
	head = head->next;
	free(freeptr);
    fclose(ifp);
	return head;
}

node *reverseList(node *head){
	node *ptr1 = NULL;
	node *newHead=NULL;
	for (ptr1 = head; ptr1 != NULL; ptr1 = ptr1->next){
		//iterates through the list and sets each element of the old list at the beginning of the new list
		newHead=frontInsert(newHead,ptr1->data);
	}
	
	return newHead;
}


node *stringToList(char *str){
	//converts the string into a list
	if (str == NULL){
		printf("string is null");
		return NULL;
	}
	//adds chars to the head until the null terminator is hit
	int ctr = 0;
	node *head = createNode(str[ctr++]);
	while(str[ctr] != '\0'){
		head = insert(head, str[ctr++]);
	}
	return head;
}
