#include <stdlib.h>
#include <stdio.h>

#define STR_MAX_SIZE 100

void reverseString(char* str);
void reverseStringPointers(char* str);


int main(){
	printf("Enter string to be reversed\n");
	char* str= malloc(sizeof(char)*STR_MAX_SIZE );
	scanf("%s", str);
	printf("%s\n", str);
	reverseStringPointers(str);
	printf("%s\n", str);
}

void reverseString(char* str){
	if(str == NULL){
		printf("str is null\n");
		return;
	}
	int len = 0;
	while(str[len] != '\0'){
		len++;
	}
	int i,j;
	for(i = 0,j = len-1; i < len/2; i++,j--) {
		char temp = str[i];
		str[i]=str[j];
		str[j] = temp;
	}
}


void reverseStringPointers(char* str){
	if(str == NULL || !(str)){
		printf("str is null\n");
		return;
	}
	int len = 0;
	while(str[len] != '\0'){
		len++;
	}
	char* beg = str;
	char* end = str+len-1;
	char temp;
	while(beg < end){
		temp = *beg;
		*beg = *end;
		*end = temp;
		beg++;
		end--;
	}
}

