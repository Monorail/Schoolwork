//Alex Berliner
//a2737438
//gcc Trie.c && ./a.out corpus01.txt input01.txt
#include "Trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NCHILD 26
#define NUMWORDS 21
#define NUMCHARS 1023
#define debug 0
#define SENTENCEDBG 0
#define MAINDEBUG 0
#define GETNODEDBG 0
#define INSSTRDBG 0
#define UPSUBDBG 0
#define INSCHDBG 0
#define BUILDDGB 0
#define USSDBG 0
void printTrie(TrieNode *root, int useSubtrieFormatting);
void printTrieHelper(TrieNode *root, char *buffer, int k);
int NChecker(TrieNode *root);
void lowerString(char *str);
TrieNode *createTrieNode(void);
TrieNode *insertChar(TrieNode *root,char ch, int last);
TrieNode *insertString(TrieNode *root, char *str);
TrieNode *insertSentence(TrieNode *root,char **sentence);
TrieNode *getNode(TrieNode *root, char *str);
TrieNode *updateSubSent(TrieNode *root, char **sentence, int numWords);
void panic(char *s)
{
	fprintf(stdout, "%s", s);
	exit(1);
}
int main(int argc, char **argv){
	int i = 0;
	int numWords=0;
	TrieNode *root  = createTrieNode();
	TrieNode *temp;
	FILE* ifp;
	char *str = malloc(sizeof(char)*1023);
	char **sentence=malloc(sizeof(char *)*(NUMWORDS+1));
	for(i =0;i<NUMWORDS;i++)sentence[i] = malloc(sizeof(char) * (NUMCHARS+1));
	if(argc<2){
		printf("Not enough args!\n");
		if (debug != 1 ) return 0;
	}
	if(MAINDEBUG)printf("main(): Starting first while loop\n");
	//Starting trie creation
	root = buildTrie(argv[1]);
	
	if(MAINDEBUG)printf("\n\n\n");
	ifp = fopen(argv[2], "r");
	while(fscanf(ifp,"%s",str)!=EOF){
		if(strcmp(str,"!")==0){
			if(MAINDEBUG)printf("main(): Print root\n");
			printTrie(root,0);
			if(MAINDEBUG)printf("main(): Print root done\n");
		}
		else{
			printf("%s\n",str);
			lowerString(str);
			//printf("main(): lowered string: %s\n",str);
			if(MAINDEBUG)printf("main(): Print co-oc for %s\n",str);
			TrieNode *h = getNode(root, str);
			if(h!=NULL){
				if(MAINDEBUG)printf("main(): h is not NULL\n");
				if(h->subtrie!=NULL){
					printTrie(h->subtrie,1);
				}else
					printf("(EMPTY)\n");
				if(MAINDEBUG)printf("main(): Done h print\n");
			}else{
				printf("(INVALID STRING)\n");
			}
			if(MAINDEBUG)printf("main(): Done with loop\nStarting cmd parse\n");
		}
		
	}
	return 0;
}
int timesInSent(char **sentence,char *key, int numWords){
	int i =0;
	int count = 0;
	for(i = 0;i<numWords;i++)
		if(strcmp(sentence[i],key)==0)count++;
	return count;
}
TrieNode *updateSubSent(TrieNode *root, char **sentence, int numWords){
	TrieNode *wordTemp;
	int i,j,k,occurPlace=0,scopecont = 0;
	if(USSDBG)printf("updateSubSent(): Start\n");
	//get corresponding arrays of the words and number of times they occur
	char **occurrences=malloc(sizeof(char *)*(NUMWORDS+1));
	for(i =0;i<NUMWORDS;i++)occurrences[i] = malloc(sizeof(char) * (NUMCHARS+1));
	int *numOccur=malloc(sizeof(int)*(NUMWORDS+1));
	//for each word, check if it's in occurrences already. continue if so
	//copy the word to occurrences. count how many times it occurs and set that for numOccur
	//increment for numOccur + occurences
	if(USSDBG)printf("updateSubSent(): Start loop\n");
	//after this, occurrences and numOccur should correspond with the names and number of occurrences of words
	for(i=0;i<numWords;i++){
		scopecont=0;
		if(USSDBG)printf("updateSubSent(): Start loop inc %d\nupdateSubSent(): OccurPlace is %d\n",i,occurPlace);
		
		for(j=0;j<occurPlace;j++){
			if(USSDBG)printf("updateSubSent(): continue?\n");
			if(strcmp(occurrences[j],sentence[i])==0){
				if(USSDBG)printf("updateSubSent(): Continuing, %s found\n",sentence[i]);
				scopecont=1;
				break;
			}
		}
		if(scopecont)continue;
		//this should only be run if there's a new word encountered
		if(USSDBG)printf("updateSubSent(): copying %s to occurrences[%d]\n",sentence[i],occurPlace);
		strcpy(occurrences[occurPlace],sentence[i]);
		if(USSDBG)printf("updateSubSent(): %s copied\n",occurrences[occurPlace]);
		numOccur[occurPlace++] = timesInSent(sentence,sentence[i],numWords);
	}
	//begin subtrie creation
	//	prints number of times each word occurs
	/*
	if(USSDBG)
		for(i = 0;i<occurPlace;i++){
			printf("updateSubSent(): %s occurs %d times\n",occurrences[i],numOccur[i]);
			wordTemp = getNode(root, occurrences[i]);
			if(USSDBG)printf("updateSubtrie(): Start\n");
		}
	*/
	//Add all words but the subtrie's word to the subtrie numOccur[i] times
	if(USSDBG)printf("\n\n\n\n");
	if(USSDBG)printf("updateSubSent(): Inserting %d words\n",occurPlace);
	
	
	
	for(i=0;i<occurPlace;i++){
		wordTemp = getNode(root,occurrences[i]);
		if(USSDBG)printf("updateSubSent(): Loop start i = %d\n",i);
		//i points at the current word creating a subtrie for
		for(j=0;j<occurPlace;j++){
			if(USSDBG)printf("updateSubSent(): Loop start j = %d\n",j);
			//j is the word that we're inserting
			if(i==j){//if the word we're looking at is the word we should be inserting
				if(USSDBG)printf("updateSubSent(): same word found continuing\n");
				continue;
			}
			//insert the word into the subtrie numOccur[j] times
			if(USSDBG)printf("updateSubtrie(): inserting subs for string %s\n",occurrences[i]);
			if(wordTemp->subtrie == NULL){
				wordTemp->subtrie = createTrieNode();
			}
			if(USSDBG)printf("updateSubtrie(): inserting %s %d times\n",occurrences[i],numOccur[j]);
			for(k=0;k<numOccur[j];k++){
				insertString(wordTemp->subtrie, occurrences[j]);
			}
		}
	}
	
	if(USSDBG)printf("updateSubtrie(): End\n\n\n\n");
	return root;
}

TrieNode *buildTrie(char *filename){
	int i = 0;
	int numWords=0;
	TrieNode *root  = createTrieNode();
	TrieNode *temp;
	FILE* ifp;
	char *str = malloc(sizeof(char)*1023);
	char **sentence=malloc(sizeof(char *)*(NUMWORDS+1));
	for(i =0;i<NUMWORDS;i++)sentence[i] = malloc(sizeof(char) * (NUMCHARS+1));
	ifp = fopen(filename, "r");
	if (ifp == NULL) fprintf(stderr, "Can't open str file in.list!\n");
	while(fscanf(ifp,"%s",str)!=EOF){
		lowerString(str);
		numWords=0;
		while(strcmp(str,".") !=0){
			lowerString(str);
			if(BUILDDGB)printf("main(): str is %s\n", str);
			strcpy(sentence[numWords],str);
			numWords++;
			fscanf(ifp,"%s",str);
		}
		lowerString(str);
		strcpy(sentence[numWords],str);
		if(BUILDDGB)printf("main(): Done with scans\n");
		root = insertSentence(root, sentence);
		root = updateSubSent(root, sentence, numWords);
	}
	return root;
	
}

TrieNode *insertSentence(TrieNode *root,char **sentence){
	int ctr = 0,i=0;
	if(SENTENCEDBG)printf("insertSentence(): Creating main tree\n");
	while(strcmp(sentence[ctr],".") !=0){
		if(SENTENCEDBG)printf("insertSentence(): Inserting %s\n",sentence[ctr]);
		insertString(root, sentence[ctr]);
		//if(SENTENCEDBG)printf("%s\n",sentence[ctr]);
		ctr++;
	}
	return root;
}

TrieNode *insertString(TrieNode *root, char *str){
	//if(INSSTRDBG)printf("insertString(): \n");
	if(INSSTRDBG)printf("insertString(): Start\n");
	if(str==NULL)
		panic("insertString(): Null string entered\n");
	if(root==NULL){
		if(INSSTRDBG)printf("insertString(): root node is NULL! Creating.\n");
		root = createTrieNode();
	}else if(INSSTRDBG)printf("insertString(): root node is not NULL!\n");
	if(INSSTRDBG)printf("insertString(): Lowering string\n");
	lowerString(str);
	int runNum = strlen(str),i;
	if(runNum<1)
		return root;
	if(INSSTRDBG)printf("insertString(): strlen is %d\n",runNum);
	if(INSSTRDBG)printf("insertString(): Starting loop\n");
	TrieNode *tempIter = root;
	for(i=0;i<runNum-1;i++){
		tempIter = insertChar(tempIter, str[i],0);
		if(INSSTRDBG)printTrie(tempIter,1);
		tempIter = tempIter->children[str[i]-'a'];
	}
	
	if(INSSTRDBG)printf("insertString(): Done inserting %c\n",str[i]);
	tempIter = insertChar(tempIter, str[i],1);
	if(INSSTRDBG)printf("insertString(): Updated tempIter\n");
	return root;
}

TrieNode *insertChar(TrieNode *root,char ch, int last){
	if(root==NULL){
		if(INSCHDBG)printf("insertChar(): Node is NULL, creating\n");
		root = createTrieNode();
	}
	if(INSCHDBG)printf("insertChar(): Inserting node %c\n",ch);
	if(root->children[(int)ch-97]==NULL){
		if(INSCHDBG)printf("insertChar(): Creating new node %c\n",ch);
		root->children[(int)ch-97] = createTrieNode();
	}
	if(last){
		if(INSCHDBG)printf("insertChar(): inserting last char %c,count is %d\n",ch,root->children[(int)ch-97]->count+1);
		root->children[(int)ch-97]->count++;
	}
	return root;
}
TrieNode *getNode(TrieNode *root, char *str){
	int strLen = strlen(str),i;
	TrieNode *temp = root;
	for(i=0;i<strLen;i++){
		if(temp->children[(int)str[i]-97]!=NULL){
			if(GETNODEDBG)printf("getNode(): Moving to %c\n",str[i]);
			temp=temp->children[(int)str[i]-97];
			if(GETNODEDBG)printf("getNode(): Moved\n");
		}
		else{
			if(GETNODEDBG)printf("getNode(): NULL child!\n");
				return NULL;
			}
	}
	if(temp->count<1){
		if(GETNODEDBG)printf("getNode(): NULL child!\n");
		return NULL;
	}
	return temp;
}
void lowerString(char *str){
	//converts a string to lowercase
	//get the length of the string
	if(debug)printf("lowerString(): Lowering %s\n",str);
	int i = 0,end = strlen(str);
	if(debug)printf("lowerString(): String is %d long\n",end);
	//iterates backwards and sets each character to its lower equivalent
	for(i=0;i<end;i++){
		if(debug)printf("lowerString(): Loop iteration %d lowering %c\n",i,str[i]);
		str[i]=tolower(str[i]);
		if(debug)printf("lowerString(): Past Lowering of %c\n",str[i]);
	}
	if(debug)printf("lowerString(): String lowered to %s\n",str);
}
int NCheck(TrieNode *root){
	if(root==NULL){
		if(debug)printf("NChecker(): Passed root is NULL\n");
	}
	if(debug)printf("NChecker(): Passed root is *NOT* NULL\n");
	if(root->children==NULL){
		if(debug)printf("NChecker(): Passed root->children is NULL\n");
	}
	if(debug)printf("NChecker(): Passed root->children is *NOT* NULL\n");
	int i;
	char *activeChildren=malloc(sizeof(char)*NCHILD*2);
	for(i = 0;i<NCHILD;i++){
		if(root->children[i]!=NULL){
			if(debug)printf("NChecker(): Adding %c\n",(char)(i+97));
			activeChildren[strlen(activeChildren)]=(char)(i+97);
			strcat(activeChildren,",");
		}
	}
	printf("NChecker(): Active children: %s\n", activeChildren);
	free(activeChildren);
	return 0;
}
TrieNode *createTrieNode(void){//initializes data for a new trie node
	//create the root
	TrieNode *temp = malloc(sizeof(TrieNode));
	//create the children
	//temp->children[0] = malloc(sizeof(TrieNode)*NCHILD);
	temp->children[0] = (TrieNode *)malloc(sizeof(TrieNode *)*NCHILD);
	//create the subtrie
	temp->subtrie = NULL;
	//set the count to 0
	temp->count = 0;
	int i;
	for(i=0;i<NCHILD;i++){
		temp->children[i]=NULL;
	}
	return temp;
}


void printTrieHelper(TrieNode *root, char *buffer, int k)
{
	int i;

	if (root == NULL)
		return;

	if (root->count > 0)
		printf("%s (%d)\n", buffer, root->count);

	buffer[k + 1] = '\0';

	for (i = 0; i < 26; i++)
	{
		buffer[k] = 'a' + i;

		printTrieHelper(root->children[i], buffer, k + 1);
	}

	buffer[k] = '\0';
}

// If printing a subtrie, the second parameter should be 1; otherwise, 0.
void printTrie(TrieNode *root, int useSubtrieFormatting)
{
	char buffer[1026];

	if (useSubtrieFormatting)
	{
		strcpy(buffer, "- ");
		printTrieHelper(root, buffer, 2);
	}
	else
	{
		strcpy(buffer, "");
		printTrieHelper(root, buffer, 0);
	}
}
