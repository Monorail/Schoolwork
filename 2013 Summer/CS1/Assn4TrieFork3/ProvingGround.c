//Alex Berliner
//a2737438
//gcc Trie.c && ./a.out corpus01.txt input01.txt
#include "Trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void lowerString(char *str)
  { char* pstr = str;
     while (*pstr++)
       *pstr = (char)tolower(*pstr); }

int main(){
	
	char dicks[]="HELLO\0";
	printf("%s\n",dicks);
	lowerString(dicks);
	printf("%s\n",dicks);
	return 0;
}

