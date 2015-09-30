//Alex Berliner and Shayne Linhart
//System Software
void error(int e);
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "VM.c"
#include "symtable.c"
#include "LexAn.c"
#include "parser.c"


#define inputDBG 0


instr* genTempCode();

int main(int argc, char **argv){
	int lArg=0, aArg=0, vArg=0;
	if ((argc-1) == 0)
		return 0;
	//check for 
	//-l : print the list of lexemes/tokens (scanner output) to the screen
	//-a : print the generated assembly code (parser/codegen output) to the screen
	//-v : print virtual machine execution trace (virtual machine output) to the screen
	//filename (no code)
	int i=0;
	for(i=0; i<argc-1; i++){
		if(inputDBG) printf("%s\n",argv[i]);
		if(strcmp(argv[i], "-l") == 0){
			lArg = 1;
			continue;
		}
		if(strcmp(argv[i], "-a") == 0){
			aArg = 1;
			continue;
		}
		if(strcmp(argv[i], "-v") == 0){
			vArg = 1;
			continue;
		}
	}
	//lArg = 0; aArg = 1; vArg = 1; // ****param override remove later****
	if(inputDBG) printf("%d %d %d\n",lArg, aArg, vArg);
	
	initSymbolTable();
	
	char* filename = malloc(sizeof(char)*20);
	strcpy(filename,argv[argc-1]);
	if(inputDBG) printf("%s\n",filename);
	lexNode* list = lexAnInit(filename, lArg);
	parseLexemeList(list, aArg);
	VMinit(assemblyCode,vArg);
	return 0;
}
