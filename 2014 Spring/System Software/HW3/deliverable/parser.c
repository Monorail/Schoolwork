//Alex Berliner and Shayne Linhart
//System Software
lexNode* program(lexNode* list);
lexNode* block(lexNode* list);
lexNode* statement(lexNode* list);
lexNode* condition(lexNode* list);
lexNode* expression(lexNode* list);
lexNode* term(lexNode* list);
lexNode* factor(lexNode* list);
int isRelation(int t);
lexNode* nextToken(lexNode* list);
void emit(int op, int r, int l, int m);
void initIdent();
void printCode();

typedef enum {
LIT = 1, RTN, LOD, STO, CALL, INC, JMP , JPC, SIOWRITE, SIOREAD, NEG, ADD, SUB,
MUL, DIV, ODD, MOD, EQL, NEQ, LSS, LEQ, GTR, GEQ
} OP;


FILE *ifp;
node* list;
int errorNum = 0;
int cx = 0, cx1, cx2;//assembly code index
instr* assemblyCode;
int topStk; //helps place new variables on stack
var getsTarget; //saves the variable on the left hand side of a gets expression
int fact1, fact2;
char tmpConst[12];
int rp; //register pointer
int rpCounter; //used to tell how much to decrement the rp on Stores
int ctemp;
int negFlag = 0; //Used to help with negative first terms in an expression
int varCtr=0;
int internalLineNum = 0;

#define CODE_SIZE 500
#define PARSERDBG 0

int aArg = 1;
int parseLexemeList(lexNode* list, int aArgInput){
	aArg = aArgInput;
	assemblyCode = malloc(sizeof(instr) * MAX_CODE_LENGTH);
	program(list);
	return 0;
}
/*

1 nulsym = 1, 	2 identsym, 
3 numbersym, 	4 plussym, 
5 minussym, 	6 multsym,	
7 slashsym, 	8 oddsym, 
9 eqsym, 	10 neqsym, 
11 lessym, 	12 leqsym,
13 gtrsym, 	14 geqsym, 
15 lparentsym, 	16 rparentsym, 
17 commasym, 	18 semicolonsym,
19 periodsym, 	20 becomessym, 
21 beginsym, 	22 endsym, 
23 ifsym, 	24 thensym,
25 whilesym, 	26 dosym, 
27 callsym, 	28 constsym, 
29 intsym, 	30 procsym, 
31 writesym,	32 readsym , 
33 elsesym
*/
lexNode* program(lexNode* list){
	rp = -1; //set to negative 1 first because register file is "empty"
	rpCounter = 0;
	topStk = 5; //since AR has 4 elements
	
	emit(INC, 0, 0, 4); //incrememt sp to top of AR
	
	if(PARSERDBG) if(aArg) printf("Parser: program(): start\n");
	lexNode* front = list; //reserve the whole list
	list = block(list);

	if(list->tokType != periodsym)
		error(4);//Error: Period expected. - changed
	if(PARSERDBG) if(aArg) printf("Parser: program(): finish\n");
	if(aArg) printCode();
	if(aArg) printf("Program is syntactially sound!\n");
	emit(RTN,0,0,0);
	return list;
}

lexNode* block(lexNode* list){//1 for int, 2 for const, 3 for proc (-1 for empty)
	if(PARSERDBG) if(aArg) printf("Parser: block(): start\n");
	if(list->tokType == constsym){
		do{
			list = nextToken(list);
			if(list->tokType != identsym)
				error(2);//2. Identifier must be followed by =.
				
			addSymbol(list->lex, 2);
			sprintf(tmpConst, "%s", list->lex);
			list = nextToken(list);
			if(list->tokType != eqsym)
				error(6);//6. Assignment operator expected.-changed
			list = nextToken(list);
			if(list->tokType != numbersym)
				error(1);//1. = must be followed by a number. - changed
			updateValue(tmpConst, atoi(list->lex));
			list = nextToken(list);
		} while(list->tokType == commasym);
		if(list->tokType != semicolonsym)
			error(5);//5. Semicolon between statements missing.-changed
		list = nextToken(list);
	}
	if(list->tokType == intsym){
		do{
			varCtr++;
			list = nextToken(list);
			if(list->tokType != identsym)
				error(3);// 3. const, int, procedure must be followed by identifier. - changed
			addSymbol(list->lex, 1);
			
			list = nextToken(list);
		} while(list->tokType == commasym);
		initIdent();
		if(list->tokType != semicolonsym)
			error(5);//5. Semicolon between statements missing. - changed
		list = nextToken(list);
	}
	while(list->tokType == procsym){
		list = nextToken(list);
		if(list->tokType != identsym)
			error(2);//2. Identifier must be followed by =.- changed
			
		addSymbol(list->lex, 3);
		
		list = nextToken(list);
		if(list->tokType != semicolonsym)
			error(5);//5. Semicolon between statements missing. - changed
		list = nextToken(list);
		list = block(list);
		if(list->tokType != semicolonsym)
			error(5);//5. Semicolon between statements missing. - changed
		list = nextToken(list);
	}
	list = statement(list);
	if(PARSERDBG) if(aArg) printf("Parser: block(): finish\n");
	return list;
}

lexNode* statement(lexNode* list){
	int i;
	char* lexSave = list->lex;
	if(PARSERDBG) if(aArg) printf("Parser: statement(): start %s\n", lexSave);
	if(list->tokType == identsym){
		if(PARSERDBG) if(aArg) printf("Parser: statement(): identsym\n");
		i = lookUp(list->lex);
		if(symbolTable[i].symbol != 1)
			error(17); //should be an indent, not a const or procedure
		list = nextToken(list);
		if(list->tokType != becomessym)
			error(6);//6. Assignment operator expected. - changed
		list = nextToken(list);
		list = expression(list);	      //v (That minus one is because the bp equals one)
		emit(STO, rp, 0, symbolTable[i].stkAddr-1); //store whats at the top of the RF to the appriopriate variable in the stack
		rp--;
		if(PARSERDBG) printf("rp is now %d\n", rp);
	}
	else if(list->tokType == callsym){
		if(PARSERDBG) if(aArg) printf("Parser: statement(): callsym\n");
		list = nextToken(list);
		//if(list->tokType != identsym)
			error(15);//15.  Call not implemented yet -> 2. Identifier must be followed by =.
		list = nextToken(list);
	}
	else if(list->tokType == beginsym){
		if(PARSERDBG) if(aArg) printf("Parser: statement(): beginsym\n");
		list = nextToken(list);
		list = statement(list);
		while(list->tokType == semicolonsym){
			list = nextToken(list);
			list = statement(list);
		}
		if(list->tokType != endsym)
			error(14);//14. "end" expected
		list = nextToken(list);
	}
	else if(list->tokType == ifsym){
		if(PARSERDBG) if(aArg) printf("Parser: statement(): ifsym\n");
		list = nextToken(list);
		list = condition(list);
		if(list->tokType != thensym)
			error(7);//7. then expected.
		list = nextToken(list);
		ctemp = cx;
		emit(JPC, rp, 0, 0);
		list = statement(list);
		assemblyCode[ctemp].m = cx;
	}
	else if(list->tokType == writesym){
		if(PARSERDBG) if(aArg) printf("Parser: statement(): write\n");
		list = nextToken(list);		
		i = lookUp(list->lex);
		
		if(symbolTable[i].symbol == 1){//integer
			rp++;
			emit(LOD, rp, 0, symbolTable[i].stkAddr-1);	//integers get their values from the stack
			emit(SIOWRITE, rp, 0, 1);
		}
		else if(symbolTable[i].symbol == 2){			//consts get their values from the symbol table
			rp++;
			emit(LIT, rp, 0, symbolTable[i].value);
			emit(SIOWRITE, rp, 0, 1);
		}
		else {
			error(4);//10. Expression must not contain a procedure identifier.
		}
		int writeVal = symbolTable[i].value;
		list = nextToken(list);
		list = statement(list);
	}
	else if(list->tokType == readsym){
		if(PARSERDBG) if(aArg) printf("Parser: statement(): read\n");
		list = nextToken(list);		
		i = lookUp(list->lex);
		if(symbolTable[i].symbol == 1){//found valid int read x; <keyboard input> -> x. <input> -> regStack; regStack -> x;
			rp++;
			emit(SIOREAD, rp, 0, 2);
			emit(STO, rp, 0, symbolTable[i].stkAddr-1);
		}else{
			error(17);//12. Assignment to constant or procedure is not allowed.
		}
		list = nextToken(list);
		list = statement(list);
	}
	else if(list->tokType == whilesym){
		if(PARSERDBG) if(aArg) printf("Parser: statement(): whilesym\n");
		cx1 = cx;
		list = nextToken(list);
		list = condition(list);
		cx2 = cx;
		emit(JPC, rp, 0, 0);
		if(list->tokType != dosym)
			error(8);//8. do expected. - changed
		list = nextToken(list);
		list = statement(list);
		emit(JMP, 0, 0, cx1);
		assemblyCode[cx2].m = cx;
	}
	if(PARSERDBG) if(aArg) printf("Parser: statement(): finish %s\n", lexSave);
	return list;
}

lexNode* condition(lexNode* list){
	if(PARSERDBG) if(aArg) printf("Parser: condition(): start\n");

	if(list->tokType == oddsym){
		list = nextToken(list);
		list = expression(list);		
	} else {
		list = expression(list);
		int relation = list->tokType;
		if(isRelation(list->tokType) == 0)
			error(9);//9. Relational operator expected. - changed
		list = nextToken(list);
		list = expression(list);
		switch(relation){
			case eqsym:
				emit(EQL, rp-1, rp-1, rp);
				break;
			case neqsym:
				emit(NEQ, rp-1, rp-1, rp);
				break;
			case lessym:
				emit(LSS, rp-1, rp-1, rp);
				break;
			case leqsym:
				emit(LEQ, rp-1, rp-1, rp);
				break;
			case gtrsym:
				emit(GTR, rp-1, rp-1, rp);
				break;
			case geqsym:
				emit(GEQ, rp-1, rp-1, rp);
				break;
			
		}
		rp--;
		if(PARSERDBG) if(aArg) printf("Parser: condition(): finish\n");
	}
	return list;
}

lexNode* expression(lexNode* list){
	int plusOrMin;
	negFlag = 0;
	if(PARSERDBG) if(aArg) printf("Parser: expression(): start\n");
	if(list->tokType == plussym || list->tokType == minussym){
		plusOrMin = list->tokType;
		list = nextToken(list);
		if(plusOrMin == minussym) //this is activated if a number or variable is negated
			negFlag = 1;      //i.e x:= -x * 4;
	}
	list = term(list);
	if(negFlag == 1){
		emit(NEG, rp, rp, 0);
		negFlag = 0;
	}
	while(list->tokType == plussym || list->tokType == minussym){
		plusOrMin = list->tokType;
		list = nextToken(list);
		list = term(list);
		if(plusOrMin == plussym){
			emit(ADD, rp-1, rp-1, rp); //Add the last two factors loaded on stack
			rp--;
			
		}
		else if(plusOrMin == minussym){
			emit(SUB, rp-1, rp-1, rp); //Sub the last two factors loaded on stack
			rp--;
		}
	}
	if(PARSERDBG) if(aArg) printf("Parser: expression(): finish\n");
	return list;
}

lexNode* term(lexNode* list){
	int mulOrDiv = 0;
	if(PARSERDBG) if(aArg) printf("Parser: term(): start\n");
	list = factor(list);
	if(negFlag == 1){
		emit(NEG, rp, rp, 0);
		negFlag = 0;
	}
	while(list->tokType == multsym || list->tokType == slashsym){
		mulOrDiv = list->tokType;
		list = nextToken(list);
		list = factor(list);
		if(mulOrDiv == multsym){
			emit(MUL, rp-1, rp-1, rp); //Multiply the last two factors loaded on the stack
			rp--;
		}
		if(mulOrDiv == slashsym){
			emit(DIV, rp-1, rp-1, rp); //Divide the last two factors loaded on the stack
			rp--;
		}
	}
	if(PARSERDBG) if(aArg) printf("Parser: term(): finish\n");
	return list;
}

lexNode* factor(lexNode* list){
	int i;
	if(PARSERDBG) if(aArg) printf("Parser: factor(): start\n");
	if(list->tokType == identsym){
		i = lookUp(list->lex);
		rp++;
		if(symbolTable[i].symbol == 1) //if its an int
			emit(LOD, rp, 0, symbolTable[i].stkAddr - 1); //-1 because bp = 1
		else if(symbolTable[i].symbol == 2) //if its a const
			emit(LIT, rp, 0, symbolTable[i].value);
		else
			error(4);//10. Expression must not contain a procedure identifier.
		list = nextToken(list);
	}
	else if(list->tokType == numbersym){
		rp++;
		emit(LIT, rp, 0, atoi(list->lex));
		list = nextToken(list);
	}
	else if(list->tokType == lparentsym){
		list = nextToken(list);
		list = expression(list);
		if(list->tokType != rparentsym)
			error(11);//11. Right parenthesis missing.
		list = nextToken(list);
	}
	else{
		error(12);//12. The preceding factor cannot begin with this symbol.
	}
	if(PARSERDBG) if(aArg) printf("Parser: factor(): finish\n");
	return list;
}

int isRelation(int t){
	if(t == eqsym ||
		 t == neqsym ||
		 t == lessym ||
		 t == leqsym ||
		 t == gtrsym ||
		 t == geqsym)
		 return 1;
	return 0;
}

lexNode* nextToken(lexNode* list){
	list = list->next;
	if(strcmp("$$$", list->lex) == 0)
		error(4);
	if(PARSERDBG) if(aArg) printf("Current token: %s\n",list->lex);
	return list;
}



void emit(int op, int r, int l, int m){
	if(cx > MAX_CODE_LENGTH) {
		error(4);
	}
	else {
		assemblyCode[cx].op = op; 	// opcode
		assemblyCode[cx].r = r; 	// register
		assemblyCode[cx].l = l;		// lexicographical level
		assemblyCode[cx].m = m;		// modifier
		assemblyCode[cx].lineNum = internalLineNum;	// modifier
		internalLineNum++;
		cx++;
	}
}

void printCode(){
	printf("\n");
	int i=0;	
	for(i = 0;i<cx;i++){
		printf("%d %d %d %d\n", assemblyCode[i].op, assemblyCode[i].r, assemblyCode[i].l, assemblyCode[i].m);
	}
	printf("\n");
		
}

void initIdent(){
	emit(LIT, 0, 0, 0);
	emit(INC, 0, 0, varCtr);
	int i = 0;
	for(i = 0; i < varCtr; i++){
		emit(STO, 0, 0, topStk);
		topStk++;
	}
}

void error(int e){
	if(aArg){
		printf("Error %d: ", e);
		switch(e){
			case 1:
			printf("= must be followed by a number.\n");
			break;
			case 2:
			printf("Identifier must be followed by =.\n");
			break;
			case 3:
			printf("const, int, procedure must be followed by identifier.\n");
			break;
			case 4:
			printf("Program not closed with a period.\n");
			break;
			case 5:
			printf("Semicolon between statements missing.\n");
			break;
			case 6:
			printf("Assignment operator expected.\n");
			break;
			case 7:
			printf("then expected.\n");
			break;
			case 8:
			printf("do expected.\n");
			break;
			case 9:
			printf("Relational operator expected.\n");
			break;
			case 10:
			printf("Comment was not closed.\n");
			break;
			case 11:
			printf("Right parenthesis missing.\n");
			break;
			case 12:
			printf("The preceding factor cannot begin with this symbol.\n");
			break;
			case 13:
			printf("Identifier too long.\n");
			break;
			case 14:
			printf("end expected.\n");
			break;
			case 15:
			printf("Call not implemented yet\n");
			break;
			case 16:
			printf("Invalid symbol.\n");
			break;
			case 17:
			printf("Assignment to constant or procedure is not allowed.\n");
			break;
			case 18:
			printf("Undeclared identifier.\n");
			break;
			case 19:
			printf("Invalid identifier.\n");
			break;
			case 20:
			printf("Number too long.\n");
			break;
			case 21:
			printf("Previously declared identifier.\n");
			break;
		}
	}
	exit(1);
}
