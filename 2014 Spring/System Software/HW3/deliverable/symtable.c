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
	int stkAddr;
	int value; //only used for const
} var;

void initSymbolTable();
void addSymbol(char* id, int sym);
int lookUp(char* id);
void updateValue(char* id, int val);

var* symbolTable; //size 500
int nextAvailableIndex;
int stkPos;

//Needs to be called before input is read in
void initSymbolTable(){
	nextAvailableIndex = 0;
	stkPos = 5; //pointing directly above AR
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

void addSymbol(char* id, int sym){
	if(SYMDBG) printf("got to addsymbol\n");
	if(SYMDBG) printf("\n");
	//check if symbol is already in table
	int i;
	for(i = 0; i < nextAvailableIndex; i++){
		if(strcmp(symbolTable[i].ident, id) == 0)
			error(21);//TODO: change error num		
	}
	
	
	strcpy(symbolTable[nextAvailableIndex].ident, id);
	symbolTable[nextAvailableIndex].symbol = sym;
	symbolTable[nextAvailableIndex].stkAddr = stkPos;
	
	nextAvailableIndex++;
	if(sym == 1)
		stkPos++;
}

int lookUp(char* id){
	int i = 0;
	
	for(i = 0; i < nextAvailableIndex; i++){
		if(strcmp(symbolTable[i].ident, id) == 0)
			return i;
	}
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

