//Alex Berliner
//a2737438
#include "Trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NCHILD 26
#define NUMWORDS 21
#define NUMCHARS 1023
void printTrie(TrieNode *root, int useSubtrieFormatting);
void printTrieHelper(TrieNode *root, char *buffer, int k);
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
	char **sentence=malloc(sizeof(char *)*(NUMWORDS+1));
	char *str = malloc(sizeof(char)*1023);
	for(i =0;i<NUMWORDS;i++)sentence[i] = malloc(sizeof(char) * (NUMCHARS+1));
	if(argc<2){
		printf("Not enough args!\n");
	}
	//Starting trie creation
	root = buildTrie(argv[1]);
	
	ifp = fopen(argv[2], "r");
	//command parsing loop
	while(fscanf(ifp,"%s",str)!=EOF){
		//print when the command is "!"
		if(strcmp(str,"!")==0){
			printTrie(root,0);
		}
		else{
			//if not "!", then looking for a string to print subtrie of
			printf("%s\n",str);
			lowerString(str);
			TrieNode *h = getNode(root, str);
			if(h!=NULL){
				if(h->subtrie!=NULL){
					printTrie(h->subtrie,1);
				}else
					printf("(EMPTY)\n");
			}else{
				printf("(INVALID STRING)\n");
			}
		}
		
	}
	free(str);
	for(i =0;i<NUMWORDS;i++)free(sentence[i]);
	free(sentence);
	return 0;
}
int timesInSent(char **sentence,char *key, int numWords){
	//calculates the number of times a word appears in a sentence
	int i =0;
	int count = 0;
	for(i = 0;i<numWords;i++)
		if(strcmp(sentence[i],key)==0)count++;
	return count;
}
TrieNode *updateSubSent(TrieNode *root, char **sentence, int numWords){
	//updates the subtrie of the words in a sentence
	TrieNode *wordTemp;
	int i,j,k,occurPlace=0,scopecont = 0;
	//get corresponding arrays of the words and number of times they occur
	char **occurrences=malloc(sizeof(char *)*(NUMWORDS+1));
	for(i =0;i<NUMWORDS;i++)occurrences[i] = malloc(sizeof(char) * (NUMCHARS+1));
	int *numOccur=malloc(sizeof(int)*(NUMWORDS+1));
	//for each word, check if it's in occurrences already. continue if so
	//copy the word to occurrences. count how many times it occurs and set that for numOccur
	//increment for numOccur + occurences
	//after this, occurrences and numOccur should correspond with the names and number of occurrences of words
	for(i=0;i<numWords;i++){
		scopecont=0;
		
		for(j=0;j<occurPlace;j++){
			if(strcmp(occurrences[j],sentence[i])==0){
				scopecont=1;
				break;
			}
		}
		if(scopecont)continue;
		//this should only be run if there's a new word encountered
		strcpy(occurrences[occurPlace],sentence[i]);
		numOccur[occurPlace++] = timesInSent(sentence,sentence[i],numWords);
	}
	//begin subtrie creation
	//	prints number of times each word occurs
	//Add all words but the subtrie's word to the subtrie numOccur[i] times
	for(i=0;i<occurPlace;i++){
		wordTemp = getNode(root,occurrences[i]);
		//i points at the current word creating a subtrie for
		for(j=0;j<occurPlace;j++){
			//j is the word that we're inserting
			if(i==j){//if the word we're looking at is the word we should be inserting
				continue;
			}
			//insert the word into the subtrie numOccur[j] times
			if(wordTemp->subtrie == NULL){
				wordTemp->subtrie = createTrieNode();
			}
			for(k=0;k<numOccur[j];k++){
				insertString(wordTemp->subtrie, occurrences[j]);
			}
		}
	}
	//cleanup
	free(numOccur);
	for(i =0;i<NUMWORDS;i++)free(occurrences[i]);
	free(occurrences);
	return root;
}

TrieNode *buildTrie(char *filename){
	//this will take in the input file and build a trie in its entirety
	int i = 0,numWords=0;
	TrieNode *root  = createTrieNode(),*temp;
	
	FILE* ifp;
	ifp = fopen(filename, "r");
	
	char *str = malloc(sizeof(char)*1023);
	char **sentence=malloc(sizeof(char *)*(NUMWORDS+1));
	for(i =0;i<NUMWORDS;i++)sentence[i] = malloc(sizeof(char) * (NUMCHARS+1));
	if (ifp == NULL) fprintf(stderr, "Can't open str file in.list!\n");
	//this while loop will take each sentence and enter it into the trie
	while(fscanf(ifp,"%s",str)!=EOF){
		//each word must be lowered before entering
		lowerString(str);
		numWords=0;
		//reads until the ending string "." is found
		while(strcmp(str,".") !=0){
			lowerString(str);
			strcpy(sentence[numWords],str);
			numWords++;
			fscanf(ifp,"%s",str);
		}
		lowerString(str);
		strcpy(sentence[numWords],str);
		//creates the framework in the root and then fills in the subtries
		root = insertSentence(root, sentence);
		root = updateSubSent(root, sentence, numWords);
	}
	
	//cleanup
	for(i =0;i<NUMWORDS;i++)free(sentence[i]);
	free(sentence);
	free(str);
	
	return root;
	
}

TrieNode *insertSentence(TrieNode *root,char **sentence){
	//Inserts an entire sentence of strings into a trie. does not create subtries
	int ctr = 0,i=0;
	while(strcmp(sentence[ctr],".") !=0){
		//inserts strings until the ending character is hit
		insertString(root, sentence[ctr]);
		ctr++;
	}
	return root;
}

TrieNode *insertString(TrieNode *root, char *str){
	//Inserts one string into a trie
	//NULL checks
	if(str==NULL)
		panic("insertString(): Null string entered\n");
	if(root==NULL){
		root = createTrieNode();
	}
	//gets the string length after we know str exists
	int runNum = strlen(str),i;
	TrieNode *tempIter = root;
	for(i=0;i<runNum-1;i++){
		//inserts one character at the temporary pointer and then increments it
		tempIter = insertChar(tempIter, str[i],0);
		tempIter = tempIter->children[str[i]-'a'];
	}
	//inserts the final character with updating count
	tempIter = insertChar(tempIter, str[i],1);
	return root;
}

TrieNode *insertChar(TrieNode *root,char ch, int last){
	//inserts a character at the child of root and increments count if last is 1
	//NULL checks
	if(root==NULL){
		root = createTrieNode();
	}
	if(root->children[ch-'a']==NULL){
		root->children[ch-'a'] = createTrieNode();
	}
	//checks to see if it is the last character in a word
	if(last){
		root->children[ch-'a']->count++;
	}
	return root;
}
TrieNode *getNode(TrieNode *root, char *str){
	//returns the first node of the passed word
	int strLen = strlen(str),i;
	TrieNode *temp = root;
	//check to see where the string ends
	for(i=0;i<strLen;i++){
		if(temp->children[(int)str[i]-97]!=NULL){
			temp=temp->children[(int)str[i]-97];
		}
		else{
				return NULL;
			}
	}
	//NULL return if the last element isn't the end of the word
	//used for empty and invalid string checks
	if(temp->count<1){
		return NULL;
	}
	return temp;
}
void lowerString(char *str){
	//converts a string to lowercase
	//get the length of the string
	int i = 0,end = strlen(str);
	//iterates backwards and sets each character to its lower equivalent
	for(i=0;i<end;i++){
		str[i]=tolower(str[i]);
	}
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


void printTrieHelper(TrieNode *root, char *buffer, int k)//prof code
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
void printTrie(TrieNode *root, int useSubtrieFormatting)//prof code
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
