#include <stdio.h>
#include <stdlib.h>

//make a reorganizing binary tree that
//holds the number and count of the numbers added

typedef struct node{
	int count;
	int data;
	struct node* left;
	struct node* right;
} node;

node* add(node* head, int num);
node* addNumber(node* head, int num);
node* createNode(int data);
void printNode(node* head);
int main(){
	node* head = NULL;
	head = add(head, 2);
	head = add(head, 2);
	head = add(head, 2);
	add(head, 1);
	add(head, 3);
	printNode(head);
	printNode(head->left);
	printNode(head->right);
	return 0;
}

node* add(node* head, int data){
	head = addNumber(head, data);
	return head;
}

node* addNumber(node* head, int num){
	if(head == NULL) {
		head = createNode(num);
		return head;
	}

	if(head->data == num) {
		head->count++;
	} else if(head->data > num) {
		printf("go left for %d\n", num);
		head = addNumber(head->left, num);
	}
	else {
		printf("go right for %d\n", num);
		head = addNumber(head->right, num);
	}
	return head;
}

node* createNode(int data){
	node* temp	= malloc(sizeof(node));
	temp->data	= data;
	temp->count = 1;
	temp->left	= NULL;
	temp->right	= NULL;
	return temp;
}

void printNode(node* head){
	printf("(%d, %d)\n", head->data, head->count);
}