//Alex Berliner and Shayne Linhart
//System Software
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define SYMDBG 0

typedef struct var{
	char* ident;
	int symbol; //1 for int, 2 for const, 3 for proc (-1 for empty)
	int stkAddr; //modifier (relative addr to bp)
	int value; //only used for const
	int lexLvl;
	int codeAddr;
} var;

void printSymTable();
void initSymbolTable();
void addSymbol(char* id, int lexLvl, int sym);
int lookUp(char* id);
void updateValue(char* id, int val);
void addProcSymbol(char* id, int lexL, int codeAddr);
void delFromST(int procIndex);

var* symbolTable; //size 500
int nextAvailableIndex;
int stkPos;

//Needs to be called before input is read in
void initSymbolTable(){
	nextAvailableIndex = 0;
	stkPos = 5; //pointing directly above AR //TODO: maybe make this 4, and get rid of the -1's for sto and lod
	int i = 0;
	
	symbolTable = malloc(sizeof(var) * 500);
	
	for (i = 0; i < 500; i++){
		if(SYMDBG) printf("Loop iter #%d\n",i);
		//symbolTable[i].ident = NULL;
		symbolTable[i].ident = malloc(sizeof(char)*12);
		strcpy(symbolTable[i].ident, "1");
		symbolTable[i].symbol = -1; //empty
		symbolTable[i].stkAddr = -1;
		symbolTable[i].value = 0;
	}
}

void addProcSymbol(char* id, int lexL, int codeAddr){
	int i;
	for(i = nextAvailableIndex-1; i>=0; i--){
		if(strcmp(symbolTable[i].ident, id) == 0) //procedure names can only be used once, regardless of which lex level
			error(21);
	}
	
	strcpy(symbolTable[nextAvailableIndex].ident, id);
	symbolTable[nextAvailableIndex].symbol = 3;
	symbolTable[nextAvailableIndex].lexLvl = lexL;
	symbolTable[nextAvailableIndex].codeAddr = codeAddr;
	nextAvailableIndex++;
	stkPos = 5; //reset stkPos for a different activation record (this is for modifier... lod(*,*,*, bp + M) )
	//printSymTable();
}

void addSymbol(char* id, int lexL, int sym){
	if(SYMDBG) printf("got to addsymbol\n");
	if(SYMDBG) printf("\n");
	//check if symbol is already in table
	int i;
	for(i = nextAvailableIndex-1; i>=0; i--){
		if(sym == 1 || sym == 2) { //if its an int or const
			if(strcmp(symbolTable[i].ident, id) == 0 && (symbolTable[i].lexLvl == lexL ||
			symbolTable[i].symbol == 3))	//see if its on same lex
				error(21);		//level (if it is, cant use same var name)		
		}
	}
	
	strcpy(symbolTable[nextAvailableIndex].ident, id);
	symbolTable[nextAvailableIndex].symbol = sym;
	symbolTable[nextAvailableIndex].lexLvl = lexL;
	
	if(sym == 1){
		symbolTable[nextAvailableIndex].stkAddr = stkPos;
		stkPos++;
	}

	nextAvailableIndex++;
}

int lookUp(char* id){
	int i;
	if(SYMDBG) printf("NAI in lookup(): %d\n", nextAvailableIndex);
	for(i = nextAvailableIndex-1; i>=0; i--){
		if(strcmp(symbolTable[i].ident, id) == 0)
			return i;
	}
	if(SYMDBG) printf("id name: %s\n",id);
	error(18); //undeclared identifer
}

//Takes in the name of a const searches the symbol table for that const,
//then updates its value with the parameter val
void updateValue(char* id, int val){
	int i;
	for(i = 0; i < nextAvailableIndex; i++){
		if(strcmp(symbolTable[i].ident, id) == 0){
			symbolTable[i].value = val;
			return;
		}
	}
}

void delFromST(int procIndex){
	//printf("Before deleting from ST\n");
	//printSymTable();
	//printf("%d\n",procIndex);// this is -1 and it shouldnt be

	nextAvailableIndex = procIndex + 1;
	//printf("After:\n");
	//printSymTable();
}

void printSymTable(){
	int i;
	printf("*******************************\n");
	for(i = 0; i < nextAvailableIndex; i++){
		printf("%s %d | ", symbolTable[i].ident, symbolTable[i].stkAddr);
	}
	printf("\n*******************************\n");


}

//gcc -o driver.o driver.c && ./driver.o -l -a -v HW4biginput.cegin