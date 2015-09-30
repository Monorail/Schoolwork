#include <stdio.h>
#include <stdlib.h>
char* RLE1(char* str);
/*
Implement a method to perform basic string compression using the counts
of repeated characters. For example, the string aabcccccaaa would become
a2blc5a3. If the "compressed" string would not become smaller than the orig-
inal string, your method should return the original string.
*/
char* RLE1(char* str){
	if(str==NULL)
		return;
	int len = 0;
	while(str[len] != '\0')
		len++;
	
	char* newStr = malloc(sizeof(char)*len);
	char* newStrIter = newStr;
	int letCount=1;
	int newLen = 0;
	char* cur = str;
	//abbcc
	//1a2b3c
	int place = 0;
	while(cur[0]!='\0'){
		if(cur[0] == cur[1]) {
			letCount++;
		} else {
			printf("%d%c",letCount, cur[0]);
			letCount=1;
		}
		cur++;
	}
	printf("\n");

	return str;
}

int main(){
	RLE1("abbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbcccdddd");

	return 0;
}