//Alex Berliner
//a2737438
//System Software
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_TABLE_SIZE 100
#define INPUTSTRLEN 30

void parseString(char* str);
int isWhitespace(char in);
typedef struct lexeme_node{
		char* varData;
		int token_type;
		struct lexeme_node *next;		
	} lexeme_node;
	
	char specialSymbols[] = 	{'+', '-', '*', '/', '(', ')', '=', ',' , '.', '<', '>',  ';' , ':'};
	int specialSymbolsLength;
	
	int throwError = 0;
	
	lexeme_node* lexemeTableHead = NULL;
	lexeme_node* lexemeTableTail = NULL;
	char  *validTokens[] = {
	"placeholder", "NULL", "ident", "number", "+", "-", "*", "/", "odd", "=", "<>", "<", "<=", ">", ">=", "(", ")", 
	",", ";", ".", ":=", "begin", "end", "if", "then", "while", "do", "call", "const", "int", "procedure", "write", "read", "else"};
	int validTokensLen = 34;
	
void parseString(char* inputStr){
	//determine if word is a var, digit or identifier
	int varTypeLen = strlen(inputStr);
	int i, varType=-1;
	for(i = 3;i<validTokensLen;i++){
		if(strcmp(validTokens[i],inputStr) == 0){
			varType = i;
			break;
		}
	}
	
	if(varType == -1){//we did not find a predefined word or symbol, so determine the token type and check for errors
		//check if we have an identifier or a digit
		if(isalpha(inputStr[0])){//probably an identifier
			if(varTypeLen > 11){//make sure identifier isnt too long
				printf("The identifier %s is too long!\n", inputStr);
				throwError = 1;
				return;
			}
			for(i = 0;i<varTypeLen;i++){//make sure all the chars are letters or digits
				if(!isalpha(inputStr[i]) && !isdigit(inputStr[i])){
					printf("%s is not a valid identifier or number!\n", inputStr);
					throwError = 1;
					return;
				}
			}
			varType = 2;
		}else if(isdigit(inputStr[0])){//most likely a digit unless there are non-digits after
			if(varTypeLen > 5){//make sure digits arent too long
				printf("The number %s is too long!\n", inputStr);
				throwError = 1;
				return;
			}
			for(i = 0;i<varTypeLen;i++){//make sure all the chars are digits
				if(!isdigit(inputStr[i])){
					printf("%s is not a valid identifier or number!\n", inputStr);
					throwError = 1;
					return;
				}
			}
			varType = 3;
		}else{ 
			throwError = 1;
			return;
		}
		
	}
	//begin addition to lexeme table
//	/*
	if(lexemeTableHead == NULL){//first run, create head of linked list
		lexemeTableHead = malloc(sizeof(lexeme_node));
		if(varType == 2 || varType == 3){
			lexemeTableHead->varData = malloc(sizeof(inputStr));
			strcpy(lexemeTableHead->varData, inputStr);
		}
		lexemeTableHead->token_type = varType;
		lexemeTableHead->next = NULL;
		
		lexemeTableTail = lexemeTableHead;
		
	}
	else {//other runs, move tail down
		
		lexeme_node* temp = malloc(sizeof(lexeme_node));
		
		if(varType == 2 || varType == 3){
			temp->varData = malloc(sizeof(inputStr));
			strcpy(temp->varData, inputStr);
		}
		temp->token_type = varType;
		temp->next = NULL;
		//move down tail
		lexemeTableTail->next = temp;
		lexemeTableTail = temp;
	}
//	*/
}

int main(int argc, char **argv){
	if (!(argc-1))
		return 0;
	
	//startup///////////////////////////
	specialSymbolsLength = strlen(specialSymbols);
	//startup end///////////////////////
	int i;
	
	FILE *ifp;//input file pointer
	ifp = fopen(argv[1], "r");//open file
	char c;
	while(!feof(ifp)){//print out whole file
		fscanf(ifp, "%c", &c);
		printf("%c",c);
	}
	
	ifp = fopen(argv[1], "r");//reopen file
		
	
	char curChar, lookaheadChar;
	if(feof(ifp)){
		printf("Empty file!\n");
		return 0;
	}
	
	fscanf(ifp, "%c", &lookaheadChar);//set up lookahead
	
	char* curStr = malloc(sizeof(char) * INPUTSTRLEN);//looking at current word
	int curStrLen = 0;

	while(!feof(ifp)){//str parsing
		curChar = lookaheadChar;//move up looked at char
		fscanf(ifp, "%c", &lookaheadChar);//read in lookahead
		if(isWhitespace(curChar))
			continue;
		int symCt = 0;
		if(!isdigit(curChar) && !isalpha(curChar)){//check for invalid characters
			for(i = 0; i < specialSymbolsLength; i++){
				if(curChar ==specialSymbols[i])
					symCt=1;
			}
			if(symCt != 1){
				printf("Invalid character found: %c\n", curChar);
			}
		}
		
		if(curChar == '/' && lookaheadChar == '*'){//check for comments
			curChar = lookaheadChar;
			fscanf(ifp, "%c", &lookaheadChar);
			curChar = lookaheadChar;
			fscanf(ifp, "%c", &lookaheadChar);
			while(curChar!='*' && lookaheadChar != '/'){
				curChar = lookaheadChar;
				fscanf(ifp, "%c", &lookaheadChar);
			}
			curChar = lookaheadChar;
			fscanf(ifp, "%c", &lookaheadChar);
			continue;
		}
		curStr[curStrLen] = curChar;
		curStrLen++;
		if(symCt || (!isdigit(lookaheadChar) && !isalpha(lookaheadChar))){//found a special symbol
			
			if(!isWhitespace(lookaheadChar) && (curChar == '<' || curChar == '>' || curChar == ':')){//check for :=, <>, etc
				//printf("Appending lookahead for operators\n");
				curChar = lookaheadChar;//move up looked at char
				fscanf(ifp, "%c", &lookaheadChar);//read in lookahead
				curStr[curStrLen] = curChar;
				curStrLen++;	
			}
			
			parseString(curStr);
			if(throwError)
				return 0;
			curStrLen = 0;
			for(i = 0;i<INPUTSTRLEN;i++)
				curStr[i]='\0';
		}
		
	}
	lexeme_node* temp = lexemeTableHead;//storing lexeme table in a linked list
	printf("Lexeme Table:\nlexeme\t\ttoken type\n");
	while(temp != NULL){
		if(temp->token_type == 2 || temp->token_type == 3)
			printf("%-12s\t%d\n", temp->varData, temp->token_type);
		else printf("%-12s\t%d\n", validTokens[temp->token_type], temp->token_type);
		temp = temp->next;
	}
	temp = lexemeTableHead;
	printf("\nLexeme List:\n");
	while(temp != NULL){//print out lexeme table
//		/*
		if(temp->token_type == 2 || temp->token_type == 3)
			printf("%d %s ", temp->token_type, temp->varData);
		else printf("%d ", temp->token_type);
//		*/
		temp = temp->next;
	}
	printf("\n");
	fclose(ifp);
	return 0;
	
}

int isWhitespace(char in){
	return 	in == '\r' || 
		in == '\n' || 
		in == '\t' || 
		in == 10   ||
		in == ' ';	 
}











//token_type derp = dosym;



































