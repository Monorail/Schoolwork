//Alex Berliner
//a2737438
#include "Trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NCHILD 26
TrieNode *createTrieNode(void);
TrieNode *getNode(TrieNode *root, char *str);
void insertString(TrieNode *root, char *str);
void lowerString(char str[]);
void insertChar(TrieNode *root,char ch, int last);
void printTrie(TrieNode *root);
void panic(char *s)
{
	fprintf(stdout, "%s", s);
	exit(1);
}
#define debug 1
int main(int argc, char **argv){
	FILE* ifp;
	char str[1023];
	if(argc<2){
		printf("Not enough args!\n");
		if (debug != 1 ) return 0;
	}
		
	ifp = fopen(argv[1], "r");
	if (ifp == NULL) {
		fprintf(stderr, "Can't open str file in.list!\n");
	}
	TrieNode *root = createTrieNode();
	fscanf(ifp,"%s",str);
	/*
	while(strcmp(str,".")!=0){
		insertString(root, str);
		fscanf(ifp,"%s",str);
	}
	printf("%d\n",root->children[(int)'l'-97]->children[(int)'i'-97]->count);
	printTrie(root);
	*/
	TrieNode *temp = root;
	insertChar(temp, 'b',0);
	printf("\n");
	temp=temp->children[(int)'b'-97];
	insertChar(temp, 'a',0);
	printf("\n");
	temp=temp->children[(int)'a'-97];
	insertChar(temp, 'n',0);
	printf("\n");
	temp=temp->children[(int)'n'-97];
	insertChar(temp, 'd',1);
	temp = root;
	do{
		int i;
		for(i=0;i<26;i++){
			printf("for %d\n",i);
			if(temp->children[i] != NULL){
				printf("%c\n",(char)(i+97));
				break;
			}
		}
		temp=temp->children[i];
	}while(temp->count!=1);
	
	return 0;
}
void insertChar(TrieNode *root,char ch, int last){
	//this will search through a node's children to see if a character can be created
	//if it needs to be created it will create a new Trie at children[x]
	//if it does not need to be created it will simply return root
	//it will increment count if last is 1
	//if(debug)printf("insertChar(): Start\n");
	int charNum = (int)ch-97;
	if(debug)printf("insertChar(): Inserting %c\n",ch);
	if(root==NULL){
		if(debug)printf("insertChar(): Root is NULL, creating\n");
		root=createTrieNode();
	}
	else if(debug)printf("insertChar(): Root is not NULL\n");
	root->children[charNum]=createTrieNode();
	if(last){
		if(debug)printf("insertChar(): Last char, incrementing count to %d\n\n",root->children[charNum]->count+1);
		root->children[charNum]->count++;
	}
}
void insertString(TrieNode *root, char *str){
	if(debug)printf("insertString(): Start\n");
	if(str==NULL || strlen(str)==0){
		panic("insertString(): string is NULL!\n");
	}
	lowerString(str);
	int charNum;
	int stringLen = strlen(str);
	TrieNode *tempTrie=root;
	if(debug)printf("insertString(): Inserting ***%s***, len = %d\n",str,stringLen);
	int i=0;
	if(debug)printf("insertString(): Starting loop\n");
	while(i<stringLen-1){
		if(debug)printf("insertString(): Inserting non-last char %c\n",str[i]);
		insertChar(tempTrie,str[i],0);
		
		i++;
		tempTrie = tempTrie->children[(int)str[i]-97];
	}
	if(debug)printf("insertString(): Inserting last char\n");
	insertChar(tempTrie,str[i],1);
	/*
	if(debug)printf("insertString(): Inserting last character %c and ending string\n",str[i]);
	insertChar(tempTrie,str[i],1);
	if(debug)printf("insertString(): Changing count of letter %c at location %d to %d\n",str[i-1],charNum,root->children[charNum]->count+1);
	root->children[charNum]->count++;
	if(debug)printf("insertString(): Iterated child %c to %d\n\n",str[i-1],root->children[charNum]->count);
	*/
}
TrieNode *buildTrie(char *filename){
	
}
void printTrie(TrieNode *root){
	if(root==NULL){
		if(debug)printf("printTrie(): root is null, returning\n");
		return;
	}
	int i;
	for(i = 0;i<26;i++){	
		if(root->children[i]!=NULL){
			printf("%c\n",(char)(i+97));
		}
	}
}
TrieNode *createTrieNode(void){//initializes data for a new trie node
	//create the root
	TrieNode *temp = malloc(sizeof(TrieNode));
	//create the children
	temp->children[0] = malloc(sizeof(TrieNode)*NCHILD);
	//create the subtrie
	temp->subtrie = NULL;
	//set the count to 0
	temp->count = 0;
	return temp;
}
TrieNode *getNode(TrieNode *root, char *str){
}

void lowerString(char str[]){//converts a string to lowercase
	//get the length of the string
	int i= strlen(str);
	//iterates backwards and sets each character to its lower equivalent
	for(;i>=0;i--)
		str[i]=tolower(str[i]);
}
















