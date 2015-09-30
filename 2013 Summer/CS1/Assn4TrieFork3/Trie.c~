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
#define BUILDDGB 1
#define DUPEDBG 1
void printTrie(TrieNode *root, int useSubtrieFormatting);
void printTrieHelper(TrieNode *root, char *buffer, int k);
int NChecker(TrieNode *root);
void lowerString(char *str);
TrieNode *createTrieNode(void);
TrieNode *insertChar(TrieNode *root,char ch, int last);
TrieNode *insertString(TrieNode *root, char *str);
TrieNode *insertSentence(TrieNode *root,char **sentence);
TrieNode *updateSubtrie(TrieNode *root, char *key,char **sentence, int numWords);
TrieNode *getNode(TrieNode *root, char *str);
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

	if(argc<2)panic("Not enough args!\n");

	if(MAINDEBUG)printf("main(): Starting first while loop\n");
	//Starting trie creation here
	root = buildTrie(argv[1]);
	//Trie creation done
	
	/*vars used for reading:
	str
	root
	h
	*/
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

TrieNode *buildTrie(char *filename){
	int i = 0,j=0;
	int numOccur = 0;
	int numWords=0;
	int numFoundWords = 0;
	TrieNode *root  = createTrieNode();
	TrieNode *temp;
	FILE* ifp;
	char *str = malloc(sizeof(char)*1023);
	char **sentence=malloc(sizeof(char *)*(NUMWORDS+1));
	for(i =0;i<NUMWORDS;i++)sentence[i] = malloc(sizeof(char) * (NUMCHARS+1));
	char **foundWords=malloc(sizeof(char *)*(NUMWORDS+1));
	for(i =0;i<NUMWORDS;i++)foundWords[i] = malloc(sizeof(char) * (NUMCHARS+1));
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
		if(BUILDDGB)printf("main(): sentence made root\n");
		i=0;
		//printf("NUMWORDS is %d\n",numWords);
		//fancy fancy wow
		if(numWords>1)
			for(i=0;i<numWords;i++){
				for(j =0;j<numFoundWords;j++)
					if(strcmp(foundWords[j],sentence[i])==0){
						if(DUPEDBG)printf("buildTrie(): A duplicate of %s was found!\n",sentence[i]);
						continue;
					}
				numOccur = findNumOccurs(sentence, sentence[i],numWords);
				if(numOccur>1){
					if(DUPEDBG)printf("buildTrie(): %s was found %d times.\n",sentence[i],numOccur);
					updateSubtrie(getNode(root, sentence[i]), sentence[i],sentence,numWords);
					//reduce the number of each thing in the subtree by numOccur-1
					for(j = 0;j<numWords;j++){
						
					}
				}
				else updateSubtrie(getNode(root, sentence[i]), sentence[i],sentence,numWords);
				strcpy(foundWords[numFoundWords++],sentence[i]);
				if(BUILDDGB)printf("main(): **Subtrie for %s is:\n",sentence[i]);
				if(BUILDDGB)printTrie(getNode(root, sentence[i])->subtrie,1);
				if(BUILDDGB)printf("main(): ***End print***\n");
			}
		if(BUILDDGB)printf("main(): Loop iter done\n");
	}
	return root;
	
}

int findNumOccurs(char **sentence, char *key, int numWords){
	int num=0;
	int i;
	for(i = 0;i<numWords;i++){
		if(strcmp(sentence[i],key)==0)
			num++;
		
	}
	return num;
}

TrieNode *updateSubtrie(TrieNode *root, char *key,char **sentence, int numWords){
//if(UPSUBDBG)printf("updateSubtrie(): \n");
	if(UPSUBDBG)printf("updateSubtrie(): Start\n");
	if(root->subtrie == NULL){
		if(UPSUBDBG)printf("updateSubtrie(): Creating subtrie node for %s.\n",key);
		root->subtrie = createTrieNode();
		if(UPSUBDBG)printf("updateSubtrie(): Subtrie node for %s created.\n",key);
	}else{
		if(UPSUBDBG)printf("updateSubtrie(): Root is not NULL\n");
		if(UPSUBDBG)printf("updateSubtrie(): Starting with:\n");
		if(UPSUBDBG)printTrie(root->subtrie,1);
		if(UPSUBDBG)printf("updateSubtrie(): End start print\n");
	}
	int skipped=0,i=0;
	if(UPSUBDBG)printf("updateSubtrie(): Starting loop\n");
	for(i=0;i<numWords;i++){
	if(UPSUBDBG)printf("updateSubtrie(): Loop iter %d\n",i);
		if(strcmp(sentence[i],key)==0){
			continue;
		}
		
		if(UPSUBDBG)printf("updateSubtrie(): inserting string %s\n",sentence[i]);
		insertString(root->subtrie, sentence[i]);
	}
	if(UPSUBDBG)printf("updateSubtrie(): End result begin:\n");
	if(UPSUBDBG)printTrie(root->subtrie,1);
	if(UPSUBDBG)printf("updateSubtrie(): End result end\n");
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















