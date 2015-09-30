//Alex Berliner and Shayne Linhart
//System Software
typedef struct lexNode{
	char lex[12];
	int tokType;
	struct lexNode* next;
}lexNode;

typedef enum {
nulsym = 1, identsym, numbersym, plussym, minussym,
multsym,	slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
periodsym, becomessym, beginsym, endsym, ifsym, thensym,
whilesym, dosym, callsym, constsym, intsym, procsym, writesym,
readsym , elsesym } token_type;


void readFilePrintSource(char* filename);
int isValidSymbol(char c);
int isValidIdent(char* w);
int isReservedWord(char* w);
lexNode* tokenize();
int isWhiteSpace(char w);
lexNode* addlexNode(char* lex, int tokType, lexNode* list);
void charToString(char c, char* s);
void printLexTable(lexNode* list);
void printLexList(lexNode* list);
char* getSymbolicRep(int token);
void printSymbolicRep(lexNode* list);
int PL0CodeSize;
char* PL0Code;

#define LEXANDBG 0

int global_lArg;

lexNode* lexAnInit(char* filename, int lArg){
	global_lArg = lArg;
	lexNode* list = NULL; 	//head of list that contains all tokens

	readFilePrintSource(filename);
	list = tokenize(list);
	if(global_lArg == 1){
		//printLexTable(list);
		printLexList(list);
		if(global_lArg) printSymbolicRep(list);
	}
	addlexNode("$$$", -1, list);
	return list;
}

void printSymbolicRep(lexNode* list){
	lexNode* help = list;
	printf("\n\nLexeme List:\n");
	while(help!=NULL){
		if(help->tokType == 2 || help->tokType == 3){
			printf("%s %s ", getSymbolicRep(help->tokType), help->lex);
		}
		else{
			printf("%s ", getSymbolicRep(help->tokType));
		}
		help = help->next;
	}
	printf("\n");
}

char* getSymbolicRep(int token){
	switch(token){
		case nulsym:
		return "nulsym";
		case identsym:
		return "identsym";
		case numbersym:
		return "numbersym";
		case plussym:
		return "plussym";
		case minussym:
		return "minussym";
		case multsym:
		return "multsym";
		case slashsym:
		return "slashsym";
		case oddsym:
		return "oddsym";
		case eqsym:
		return "eqsym";
		case neqsym:
		return "neqsym";
		case lessym:
		return "lessym";
		case leqsym:
		return "leqsym";
		case gtrsym:
		return "gtrsym";
		case geqsym:
		return "geqsym";
		case lparentsym:
		return "lparentsym";
		case rparentsym:
		return "rparentsym";
		case commasym:
		return "commasym";
		case semicolonsym:
		return "semicolonsym";
		case periodsym:
		return "periodsym";
		case becomessym:
		return "becomessym";
		case beginsym:
		return "beginsym";
		case endsym:
		return "endsym";
		case ifsym:
		return "ifsym";
		case thensym:
		return "thensym";
		case whilesym:
		return "whilesym";
		case dosym:
		return "dosym";
		case callsym:
		return "callsym";
		case constsym:
		return "constsym";
		case intsym:
		return "intsym";
		case procsym:
		return "procsym";
		case writesym:
		return "writesym";
		case readsym:
		return "readsym";
		case elsesym:
		return "elsesym";
	}
	
	
}

void readFilePrintSource(char* filename){
	FILE *ifp = NULL;
	char c;
	int i = 0;
	ifp = fopen(filename, "r");
	if(ifp == NULL){
		printf("FILE %s NOT FOUND\n", filename);
		exit(1);
	}
	
	fseek(ifp, 0, SEEK_END); // move file pointer to end of file
	PL0CodeSize = ftell(ifp) / sizeof(char); //gets size of the file in bytes
	fseek(ifp, 0, SEEK_SET); //set file pointer back to beg of file

	PL0Code = calloc(PL0CodeSize+1, sizeof(char));//plus 1 just for an extra lookahead buffer just in case

	//printf("\nSource Program:\n");

	while(!feof(ifp)){
		c = fgetc(ifp);
		if(feof(ifp)) //this is needed because feof by nature runs one too many times. this will be the actual breaking condidion of the loop
			break;
		printf("%c", c);
		PL0Code[i] = c;
		i++;
	}
	PL0Code[i] = '\0'; //shows end of PL0Code array
	fclose(ifp);
}

//returns number associated with enum if is valid symbol, 0 if not a valid symbol
int isValidSymbol(char c){
	if(c == '+'){
		return 4;
	}
	else if(c == '-'){
		return 5;
	}
	else if(c == '*'){
		return 6;
	}
	else if(c == '/'){
		return 7;
	}
	else if(c == '='){
		return 9;
	}
	else if(c == '<'){
		return 11;
	}
	else if(c == '>'){
		return 13;
	}
	else if(c == '('){
		return 15;
	}
	else if(c == ')'){
		return 16;
	}
	else if(c == ','){
		return 17;
	}
	else if(c == ';'){
		return 18;
	}
	else if(c == '.'){
		return 19;
	}
	else if(c == ':'){ //this one isnt defined as its own symbol, but im adding it for use of the 'becomes' symbol and for consistency
		return 30;
	}
	else if(c == '%'){
		error(12);//12. The preceding factor cannot begin with this symbol.
	} else {
		return 0;
	}
}

//the workhorse function that does most of the logic for seperating tokens.
//returns a pointer to the head of the list that contains all the tokens
lexNode* tokenize(lexNode* list){
	int i = 0; //pointer
	char* temp = calloc(20, sizeof(char));
	int j = 0; //counter for temp
	char* s; //helper string used to help convert chars to strings.

	while(PL0Code[i] != '\0'){

		if(isWhiteSpace(PL0Code[i])!= 0){
			i++;
		}
		else if(isalpha(PL0Code[i]) != 0){ //if it is a letter
			while(isalpha(PL0Code[i])!= 0 || isdigit(PL0Code[i])!= 0){ //while the char is a letter or a digit
				temp[j] = PL0Code[i];
				if(j>17){
					error(13);
				}
				i++; j++;
			}
			temp[j] = '\0'; //make the string null terminating
			j = 0;

			if(isReservedWord(temp)!= 0){
				list = addlexNode(temp, isReservedWord(temp), list);
			}
			else if(isValidIdent(temp)!= 0){
				list = addlexNode(temp, identsym, list);
			}
			else{
				error(16);
			}
		}
		else if(isValidSymbol(PL0Code[i])!= 0) {
			if(isValidSymbol(PL0Code[i]) == 4 ||isValidSymbol(PL0Code[i]) == 5 ||isValidSymbol(PL0Code[i]) == 6 ||isValidSymbol(PL0Code[i]) == 9 ||
				 isValidSymbol(PL0Code[i]) == 15 ||isValidSymbol(PL0Code[i]) == 16 ||
				 isValidSymbol(PL0Code[i]) == 17 || isValidSymbol(PL0Code[i]) == 18 ||isValidSymbol(PL0Code[i]) == 19){ //if the symbol isnt a possible beginning of another sym.
				s = calloc(2,sizeof(char)); //used to help convert characters to strings
				charToString(PL0Code[i],s);
				list = addlexNode(s ,isValidSymbol(PL0Code[i]) , list);
				i++;
			}
			else if(isValidSymbol(PL0Code[i]) == 7){ //if it is a slash symbol, check to see if its a comment or a divides
				if(PL0Code[i+1] == '*'){//if the next char is a '*' then it is a comment
					i = i+2;
					while(PL0Code[i] != '\0'){
						if(PL0Code[i+1] == '\0'){ // would cause an error because the comment is never closed
							error(10);
						}
						if(PL0Code[i] == '*' && PL0Code[i+1] == '/'){
							i = i+2; //effictivly ignore comments
							break;
						}
						i++;
					}
				}
				else{
					list = addlexNode("/" , slashsym , list);
					i++;
				}
			}
			else if(isValidSymbol(PL0Code[i]) == 11){//check if its a less than or a not equal or (less than or equal to)
				if(PL0Code[i+1] == '\0'){
					i++;
					list = addlexNode("<" , lessym , list);
				}
				else if(PL0Code[i+1] == '>'){ //neq
					list = addlexNode("<>" ,neqsym , list);
					i = i+2;
				}
				else if(PL0Code[i+1] == '='){//leq
					list = addlexNode("<=" ,leqsym , list);
					i = i+2;
				}
				else{
					i++;
					list = addlexNode("<" , lessym , list);
				}
			}
			else if(isValidSymbol(PL0Code[i]) == 13){ //check if it is greater than or greater than or equal to
				if(PL0Code[i+1] == '\0'){
					list = addlexNode(">" , gtrsym , list);
					i++;
				}
				else if(PL0Code[i+1] == '='){
					list = addlexNode(">=" , geqsym , list);
					i = i+2;
				}
				else{
					list = addlexNode(">" , gtrsym , list);
					i++;
				}
			}
			else if(isValidSymbol(PL0Code[i]) == 30){ //see if is becomes symbol
				if(PL0Code[i+1] == '='){
					list = addlexNode(":=" , becomessym , list);
					i = i+2;
				}
				else{
					error(16);
				}
			}
		}
		else if(isdigit(PL0Code[i])!= 0){ //check to see if valid number
			while(isdigit(PL0Code[i])!= 0){ //while the char is a digit
				temp[j] = PL0Code[i];

				if(j>17){
					error(20);
				}
				i++; j++;
			}
			if(isalpha(PL0Code[i])!= 0){ //see if the char immediatly following digit(s) is a letter. if it is it should be regarded as an invalid ident
				error(19);
			}
			temp[j] = '\0'; //make the string null terminating
			j = 0;
			if(strlen(temp) > 5){
				error(20);
			}
			else{
				list = addlexNode(temp , numbersym , list);
			}
		}
		else{
			error(16);
		}
	}
	return list;
}

//returns the enum value of the reserved word symbol if it exist, 0 if its not a reserved word
int isReservedWord(char* w){
	if(strcmp(w,"const") == 0){
		return 28;
	}
	else if(strcmp(w,"int") == 0){
		return 29;
	}
	else if(strcmp(w,"procedure") == 0){
		return 30;
	}
	else if(strcmp(w,"call") == 0){
		return 27;
	}
	else if(strcmp(w,"begin") == 0){
		return 21;
	}
	else if(strcmp(w,"end") == 0){
		return 22;
	}
	else if(strcmp(w,"if") == 0){
		return 23;
	}
	else if(strcmp(w,"then") == 0){
		return 24;
	}
	else if(strcmp(w,"else") == 0){
		return 33;
	}
	else if(strcmp(w,"while") == 0){
		return 25;
	}
	else if(strcmp(w,"do") == 0){
		return 26;
	}
	else if(strcmp(w,"read") == 0){
		return 32;
	}
	else if(strcmp(w,"write") == 0){
		return 31;
	}
	else if(strcmp(w, "odd") == 0){
		return 8;
	}
	else{
		return 0; //not a reserved word
	}
}

//returns 1 if valid ident, 0 otherwise.
int isValidIdent(char* w){
	int i = 1;
	if(w == NULL || strlen(w) == 0 || strlen(w) > 11)
		return 0;
	if(isalpha(w[0])==0)
		return 0;
	while(w[i] != '\0'){
		if(isalpha(w[i])==0 && isdigit(w[i])==0)
			return 0;
		i++;
	}
	return 1;
}

int isWhiteSpace(char w){
	if(w == ' '||
		 w == '\t'||
		 w == '\n' ||
		 w == '\r')
		return 1;
	return 0;
}

//add a new lexNode to the end of the list
lexNode* addlexNode(char* lex, int tokType, lexNode* list){
	lexNode* newlexNode = (lexNode*)malloc(sizeof(lexNode));
	strcpy(newlexNode->lex, lex);
	newlexNode->tokType = tokType;
	newlexNode->next = NULL;
	lexNode* tmp = list;

	if(tmp == NULL)
		return newlexNode;

	while(tmp->next != NULL){
		tmp = tmp->next;
	}
	tmp->next = newlexNode;
	return list;
}

//s must be of size 2 or greater;
void charToString(char c, char* s){
	s[0] = c;
	s[1] = '\0';
}

void printLexTable(lexNode* list){
	lexNode* help = list;
	printf("Lexeme Table:\n");
	printf("%-12s\t%-12s", "lexeme", "token type");
	while(help!=NULL){
		printf("\n%-12s\t%-12d", help->lex, help->tokType);
		help = help->next;
	}
}

void printLexList(lexNode* list){
	lexNode* help = list;
	printf("\n\nLexeme List:\n");
	while(help!=NULL){
		if(help->tokType == 2 || help->tokType == 3){
			printf("%d %s ", help->tokType, help->lex);
		}
		else{
			printf("%d ", help->tokType);
		}
		help = help->next;
	}
	printf("\n");
}
