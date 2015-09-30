//Alex Berliner
//PID: a2737438
#include <stdio.h>
#include <stdlib.h>
#include "Fibonacci.h"
#include "HugeInteger.h"

int main(int argc, char **argv){
	int fibnum;
	int i;
	HugeInteger* printer;
	foo(argc,argv);
	//checks if there are actually arguments
	if (!(argc-1))
		return 0;
	Memo *derp = createMemo();
	for(i=1;i<argc;i++){
		//convert the string argument to an integer
		fibnum = atoi(argv[i]);
		//setting the hugeinteger pointer to be printed from the memo
		printer = fib(fibnum,derp);
		printf("F(%d): ",fibnum);
		HugePrint(printer);
	}
	//destroys the memo when done printing
	destroyMemo(derp);
	return 0;
}

void HugePrint(HugeInteger *p){
	//checks to see if the passed struct actually exists
	if (p==NULL){
		printf("(undefined)\n");
		return;	
	}
	int i;
	//prints the elements of the struct in reverse order
	for(i = p->length-1;i>=0;i--)
		printf("%d",p->digits[i]);
	printf("\n");
}

Memo *destroyMemo(Memo *memo){
	
	int c = 0,j,i;
	//checking to see if memo actually exists
	if(memo == NULL)
		return NULL;
	//freeing all the huge integers
	for(i = 0;i<memo->length;i++){
		free(memo->F[i].digits);
		memo->F[i].digits = NULL;
	}
	//freeing the huge integer array
	free(memo->F);
	memo->F = NULL;
	//freeing the actual memo struct
	free(memo);
	memo = NULL;
	return memo;

}


Memo *createMemo(void){
	int i;
	//Dynamically allocate space for a new Memo struct.
	Memo *tempMemo = malloc(sizeof(Memo));
	if (tempMemo == NULL)
		panic("tempMemo was not allocated correctly!");
	//dynamically allocate INIT_MEMO_SIZE size array of HugeInteger
	tempMemo->F = malloc(sizeof(HugeInteger) * INIT_MEMO_SIZE);
	//malloc error check
	if (tempMemo->F == NULL)
		panic("tempMemo was not allocated correctly!");
	//Once the array is created, initialize memoâ†’length appropriately.
	tempMemo->length = INIT_MEMO_SIZE;
	//initializing base cases
	if(!HugeInit(&tempMemo->F[0],0))
		panic("HugeInit 1 failed");
	if(!HugeInit(&tempMemo->F[1],1))
		panic("HugeInit 2 failed");
	for(i = 2;i<INIT_MEMO_SIZE;i++){
	//initialize the digits field to NULL and the length field to 0 to indicate that F[i] has not yet been memoized.
		tempMemo->F[i].digits = NULL;
		tempMemo->F[i].length = 0;
	}
	return tempMemo;
}

struct HugeInteger *fib(int n, Memo *memo){
	//Base 1: F(n) has been memoized
	if(memo==NULL || n<0){
		return NULL;
	}
	//checks to see if the memo needs to be expanded
	if(memo->length<=n)
		expandMemo(memo,n);
	//checks to see if the current fib element already exists. if so, returns it
	if(memo->F[n].length != 0){
		return &memo->F[n];
	}
	//recursive fibonacci adapted for use with HugeAdd
	HugeAdd(fib(n-2,memo),fib(n-1,memo),&memo->F[n]);
	return &memo->F[n];
}


int expandMemo(Memo *memo, int n){
	//sets the size of the new array length equal 
	int newLen = (memo->length>n?memo->length:n)*2 + 1;
	int i,k;
	HugeInteger *temp = malloc(sizeof(HugeInteger) * newLen);
	//malloc error check
	if(temp == NULL)
		panic("ERROR: out of memory in expandMemo()\n");
	//copying the HugeInteger pointers of the old memo to the new one
	for(i=0;i<memo->length;i++){
		temp[i] = memo->F[i];
	}
	free(memo->F);
	for(i = memo->length;i<newLen;i++){
	//initialize the digits field to NULL and the length field to 0 to indicate that F[i] has not yet been memoized.
		temp[i].digits = NULL;
		temp[i].length = 0;
	}
	//giving memo the new HI array
	memo->F = temp;
	//setting memo's new length
	memo->length = newLen;
	printf("-> Expanded memo capacity to %d.\n",newLen);
	return newLen;
}



int HugeInit(HugeInteger *p,int n){
	//printf("HI()1: \t%d\n",n);
	int i;
	//check if n is longer than 1 digit, negative,  or if p is NULL
	if (n<0 || n>9|| p==NULL)
		return 0;

	//dynamically allocate pâ†’digits to be an array of 1 integer.
	p->digits = malloc(sizeof(int));
	//malloc error check
	if (p->digits == NULL) panic("ERROR: out of memory in HugeInit()\n");
	//set the element to be n
	p->digits[0] = n;
	p->length = 1;

	return 1;
}
