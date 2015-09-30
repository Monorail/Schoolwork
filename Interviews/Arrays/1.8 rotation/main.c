#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Assume you have a method isSubstring which checks if one word is a substring
of another. Given two strings, s1 and s2, write code to check If s2 is a rotation of s1
using only one call to isSubstring (e.g., "waterbottLe" is a rotation of "erbottLewat").
*/

int isRotation(char* s1, char* s2);
int isSubstring(char* s1, char* s2);
int main(){
	char* s1 = "waterbottle";
	char* s2 = "ttlewaterbo";
	printf("%s is%s a rotation of %s\n", s1, (isRotation(s1,s2)?"":"n't"), s2);
	return 0;
}

int isRotation(char* s1, char* s2){
	if(s1==NULL || s2==NULL)
		return 0;
	int s1Len = strlen(s1);
	int s2Len = strlen(s2);
	if(s1Len != s2Len)
		return 0;
	char* s1s1 = malloc(sizeof(char) * s1Len*2);
	strcpy(s1s1, s1);
	strcpy(s1s1+s1Len, s1);
	return isSubstring(s1s1, s2);
}

int isSubstring(char* s1, char* s2){
	if(s1==NULL || s2==NULL)
		return 0;
	return strstr(s2,s1)==NULL;
}
