//Alex Berliner and Shayne Linhart
//System Software
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_STACK_HEIGHT 2000
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 3
#define execute_debug 0
typedef struct instr{
		int op; 	// opcode
		int r;		// reg
		int l; 		// L
		int m;		// M
		int lineNum;
} instr;

typedef struct node{
		int loc; // ar line location
		struct node *next;
} node;

int fetch();
int execute();
int base(int, int);
char* determineOP(int);
void printRegFile();
int* stack;
int* rf;	//register file
int pc;		//VMProgram counter
int bp;		//base pointer
int sp;		//stack pointer
instr ir;	//instruction register
instr* VMProgram;
int SIO_out_ctr;
int* SIO_out_holder;
instr* genCode();	
int VMinit(instr* prog, int vArg);
//The dynamic link points to the top of the ARI of the caller.
//The static link points to the bottom of the ARI of the callee's static parent.
int vArg = 0;

instr* genCode(){
	int i = 0;
	VMProgram = malloc(sizeof(instr) * MAX_CODE_LENGTH);
	VMProgram[i].op = 6; VMProgram[i].r = 0; VMProgram[i].l = 0; VMProgram[i].m = 6; VMProgram[i].lineNum = 0;
	i++;
	VMProgram[i].op = 1; VMProgram[i].r = 0; VMProgram[i].l = 0; VMProgram[i].m = 6; VMProgram[i].lineNum = 1;
	i++;
	VMProgram[i].op = 4; VMProgram[i].r = 0; VMProgram[i].l = 0; VMProgram[i].m = 4; VMProgram[i].lineNum = 2;
	i++;
	VMProgram[i].op = 3; VMProgram[i].r = 0; VMProgram[i].l = 0; VMProgram[i].m = 4; VMProgram[i].lineNum = 3;
	i++;
	VMProgram[i].op = 1; VMProgram[i].r = 1; VMProgram[i].l = 0; VMProgram[i].m = 0; VMProgram[i].lineNum = 4;
	i++;
	VMProgram[i].op = 22; VMProgram[i].r = 0; VMProgram[i].l = 0; VMProgram[i].m = 1; VMProgram[i].lineNum = 5;
	i++;
	VMProgram[i].op = 8; VMProgram[i].r = 0; VMProgram[i].l = 0; VMProgram[i].m = 17; VMProgram[i].lineNum = 6;
	i++;
	VMProgram[i].op = 3; VMProgram[i].r = 0; VMProgram[i].l = 0; VMProgram[i].m = 4; VMProgram[i].lineNum = 7;
	i++;
	VMProgram[i].op = 14; VMProgram[i].r = 0; VMProgram[i].l = 0; VMProgram[i].m = 0; VMProgram[i].lineNum = 8;
	i++;
	VMProgram[i].op = 4; VMProgram[i].r = 0; VMProgram[i].l = 0; VMProgram[i].m = 5; VMProgram[i].lineNum = 9;
	i++;
	VMProgram[i].op = 3; VMProgram[i].r = 0; VMProgram[i].l = 0; VMProgram[i].m = 4; VMProgram[i].lineNum = 10;
	i++;
	VMProgram[i].op = 1; VMProgram[i].r = 1; VMProgram[i].l = 0; VMProgram[i].m = 1; VMProgram[i].lineNum = 11;
	i++;
	VMProgram[i].op = 13; VMProgram[i].r = 0; VMProgram[i].l = 0; VMProgram[i].m = 1; VMProgram[i].lineNum = 12;
	i++;
	VMProgram[i].op = 4; VMProgram[i].r = 0; VMProgram[i].l = 0; VMProgram[i].m = 4; VMProgram[i].lineNum = 13;
	i++;
	VMProgram[i].op = 3; VMProgram[i].r = 0; VMProgram[i].l = 0; VMProgram[i].m = 5; VMProgram[i].lineNum = 14;
	i++;
	VMProgram[i].op = 9; VMProgram[i].r = 0; VMProgram[i].l = 0; VMProgram[i].m = 1; VMProgram[i].lineNum = 15;
	i++;
	VMProgram[i].op = 7; VMProgram[i].r = 0; VMProgram[i].l = 0; VMProgram[i].m = 3; VMProgram[i].lineNum = 16;
	i++;
	VMProgram[i].op = 3; VMProgram[i].r = 0; VMProgram[i].l = 0; VMProgram[i].m = 4; VMProgram[i].lineNum = 17;
	i++;
	VMProgram[i].op = 9; VMProgram[i].r = 0; VMProgram[i].l = 0; VMProgram[i].m = 1; VMProgram[i].lineNum = 18;
	i++;
	VMProgram[i].op = 3; VMProgram[i].r = 0; VMProgram[i].l = 0; VMProgram[i].m = 5; VMProgram[i].lineNum = 19;
	i++;
	VMProgram[i].op = 9; VMProgram[i].r = 0; VMProgram[i].l = 0; VMProgram[i].m = 1; VMProgram[i].lineNum = 20;
	i++;
	VMProgram[i].op = 2; VMProgram[i].r = 0; VMProgram[i].l = 0; VMProgram[i].m = 0; VMProgram[i].lineNum = 21;
	i++;
	return VMProgram;
}

int VMinit(instr* prog, int vArgInput){
	vArg = vArgInput;
	int i;
	//initialize SIO holder array
	SIO_out_ctr=0;
	SIO_out_holder = malloc(sizeof(int)*2000);
	
	//initialize all stack vars
	stack = calloc(MAX_STACK_HEIGHT, sizeof(int));
	//initialize registers
	sp = 0;
	bp = 1;
	pc = 0;
	rf = calloc(16, sizeof(int));
	VMProgram = prog;
	/*
	FILE *ifp;//input file pointer

	ifp = fopen(argv[1], "r");
	int lineCtr = 0;
	if(vArg)printf("Line\tOP\tR\tL\tM\n");
	while(!feof(ifp)){//read in code from the input file
		fscanf(ifp, "%d%d%d%d", &ir.op, &ir.r, &ir.l, &ir.m);
		VMProgram[lineCtr].op = ir.op;
		VMProgram[lineCtr].r = ir.r;
		VMProgram[lineCtr].l = ir.l;
		VMProgram[lineCtr].m = ir.m;
		VMProgram[lineCtr].lineNum = lineCtr;
		if(vArg)printf("%d\t%s\t%d\t%d\t%d\n", lineCtr, determineOP(VMProgram[lineCtr].op), VMProgram[lineCtr].r, VMProgram[lineCtr].l, VMProgram[lineCtr].m);//print out code to terminal
		lineCtr++;
	}
	if(vArg)printf("%d\t%s\t%d\t%d\t%d\n", lineCtr, determineOP(VMProgram[lineCtr].op), VMProgram[lineCtr].r, VMProgram[lineCtr].l, VMProgram[lineCtr].m);
	*/
	//VMProgram[lineCtr].op = -1;//set op after last line of VMProgram to -1 to denote VMProgram end
	//if(vArg)printf("%d\t%s\t%d\t%d\t%d\n", lineCtr, determineOP(VMProgram[lineCtr].op), VMProgram[lineCtr].r, VMProgram[lineCtr].l, VMProgram[lineCtr].m);
	
	if(vArg)printf("\n");
	if(vArg)printf("Inital Values\t\t\t\tpc	bp	sp\t\n");
	while(bp != 0){//enter fetch / execute cycle	
		fetch();
		execute();
	}
	printf("Program Output: ");
	for(i=0; i<SIO_out_ctr;i++){//print out stored SIO out values
		printf("%d ",SIO_out_holder[i]);
	}
	printf("\n");
	return 0;
}


int fetch(){
	/*
		In the Fetch Cycle, an instruction is fetched from the “code” store and placed in the IR register (IR <= code[PC]).
		Afterwards, the VMProgram counter is incremented by 1 to point to the next instruction to be executed (PC <= PC + 1).
	*/
	ir = VMProgram[pc];
	pc++;
	return 0;
}

int execute(){
	/*
		In the Execute Cycle, the instruction that was fetched is executed by the VM.
		The OP component that is stored in the IR register (IR.OP) indicates the operation to be executed.
		For example, if IR.OP is the ISA instruction ADD (IR.OP = 12), then the R, L, M component of the instruction in the IR register (IR.R, IR.L, IR.M)
		are used as a register and execute the appropriate arithmetic or logical instruction.
	*/
	switch(ir.op){
		case 1://LIT R,0,M
			rf[ir.r] = ir.m;
			break;

		case 2: //RTN  0, 0, 0
			sp = bp-1;
			pc = stack[sp+4];
			bp = stack[sp+3];
		    	break;

		case 3://LOD R, L, M		R[i] <= stack[ base(L, bp) + M];
			rf[ir.r] = stack[ base(ir.l, bp) + ir.m];
			break;

		case 4://STO R, L, M		stack[ base(L, bp) + M] <= R[i];
			stack[base(ir.l,bp) + ir.m] = rf[ir.r];
			break;

		case 5://CAL   0, L, M
			stack[sp + 1]  = 0;		// space to return value
			stack[sp + 2]  = base(ir.l, bp);// static link (SL)
		    	stack[sp + 3]  = bp;		// dynamic link (DL)
			stack[sp + 4]  = pc;	// return address (RA) 
			bp = sp + 1;
			pc = ir.m;
			break;

		case 6:// INC   0, 0, M
			sp = sp + ir.m;
			break;

		case 7://JMP   0, 0, M 
			pc = ir.m;
			break;

		case 8:// JPC   R, 0, M
			if (rf[ir.r] == 0) 
				pc = ir.m; 
			break;

		case 9://SIO   R, 0, 1
			SIO_out_holder[SIO_out_ctr] = rf[ir.r];
			SIO_out_ctr++;
			break;

		case 10://SIO   R, 0, 2
			scanf("%d",&rf[ir.r]);
			break;

		case 11://NEG
			rf[ir.r]  = -rf[ir.l];
			break;

		case 12://ADD
			rf[ir.r]  = rf[ir.l] + rf[ir.m];
			break;

		case 13://SUB
			rf[ir.r] = rf[ir.l] - rf[ir.m];
			break;

		case 14://MUL
			rf[ir.r] = rf[ir.l] * rf[ir.m];
			break;

		case 15://DIV
			rf[ir.r] = rf[ir.l] / rf[ir.m];
			break;

		case 16://ODD
			rf[ir.r] = rf[ir.r] % 2;
			break;

		case 17://MOD
			rf[ir.r] = rf[ir.l] % rf[ir.m];
			break;

		case 18://EQL
			rf[ir.r]  = (rf[ir.l] == rf[ir.m]);
			break;

		case 19://NEQ
			rf[ir.r] = (rf[ir.l] != rf[ir.m]);
			break;

		case 20://LSS
			rf[ir.r] = (rf[ir.l] < rf[ir.m]);
			break;

		case 21://LEQ
			rf[ir.r] = rf[ir.l] <= rf[ir.m];
			break;

		case 22://GTR
			rf[ir.r] = (rf[ir.l] > rf[ir.m]);
			break;

		case 23://GEQ
			rf[ir.r] = (rf[ir.l] >= rf[ir.m]);
			break;

		default://
			if(vArg)printf("Error: invalid op code %d\n", ir.op);
			error(1); //TODO: get rid of error
			break;

	}
	
	int curBP = bp;
	int curSP = sp;
	node* head=NULL;
	while(curBP > 1){//this loop stores the location of every new activation record in a linked list, for use when inserting the |'s
		if(curBP<sp){
			//if(vArg)printf("%d ",curBP);
			if(head == NULL){//first run, create head
				head = malloc(sizeof(node));
				head->loc = curBP;
				head->next = NULL;
			}
			else {//other runs, move head down
				node* temp = head;
				head = malloc(sizeof(node));
				head->loc = curBP;
				head->next = temp;
			}
		}
		curSP = curBP-1;
		curBP = stack[curSP+3];
	}
	//finally print out the formatted stack
	node* temp = head;
	if(vArg)printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d",ir.lineNum,determineOP(ir.op),ir.r,ir.l,ir.m,pc,bp,sp);
	int i;
	int end = (sp<3)?4:sp + 1;//always print out 3 stack elements minimum
	for(i = 1;i<end;i++){//print stack
		if(temp != NULL && i == temp->loc){//print | if we go to a new AR
			temp = temp->next;
			if(vArg)printf("\t|");
		}
		if(vArg)printf("\t%d",stack[i]);
	}
	//if(vArg)printf("\n");
	if(vArg)printf("\n");
	return 0;
}



int base(int l, int base){ 	// l stand for L in the instruction format
	int b1; 		//find base L levels down
	b1 = base;
	while (l > 0){
		b1 = stack[b1 + 1];
		l--;
	}
	return b1;
}

char* determineOP(int OP){//determines the string representation of every op code
	switch(OP){
		case 1://
			return (char *)"lit";
		case 2://
			return (char *)"rtn";
		case 3://
			return (char *)"lod";
		case 4://
			return (char *)"sto";
		case 5://
			return (char *)"cal";
		case 6://
			return (char *)"inc";
		case 7://
			return (char *)"jmp";
		case 8://
			return (char *)"jpc";
		case 9://
			return (char *)"sio";
		case 10://
			return (char *)"sio";
		case 11://
			return (char *)"neg";
		case 12://
			return (char *)"add";
		case 13://
			return (char *)"sub";
		case 14://
			return (char *)"mul";
		case 15://
			return (char *)"div";
		case 16://
			return (char *)"odd";
		case 17://
			return (char *)"mod";
		case 18://
			return (char *)"eql";
		case 19://
			return (char *)"neq";
		case 20://
			return (char *)"lss";
		case 21://
			return (char *)"leq";
		case 22://
			return (char *)"gtr";
		case 23://
			return (char *)"geq";
		default://
			return (char *)"default";
	}
}

void printRegFile(){
	int i;
	printf("RegStack: ");
	for(i = 0; i < 16; i++){
		printf("%d\t",rf[i]);
	}
	printf("\n");

		
}
