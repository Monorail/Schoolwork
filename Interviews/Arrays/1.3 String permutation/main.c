#include <stdio.h>
#include <stdlib.h>

int isPerm(char* a, char* b);

//Given two strings, write a method to decide if one is a permutation of the other
int main(){
	char* a = "hi";
	char* b = "id";
	printf("%s\n",isPerm(a,b)?"same\n":"different\n");


	return 0;
}
int isPerm(char* a, char* b){
	if(a==NULL && b == NULL)
		return 1;
	else if(a==NULL && b != NULL)
		return 0;
	else if(a!=NULL && b == NULL)
		return 0;
	printf("past checks\n");
	int aLen = 0, bLen = 0;

	while(a[aLen++] != '\0');
	while(b[bLen++] != '\0');
	aLen--;
	bLen--;
	printf("past strlen\n");

	if(aLen != bLen)
		return 0;

	int i;

	char* aBucket = calloc(26, sizeof(char));
	char* bBucket = calloc(26, sizeof(char));
	printf("past calloc\n");

	for(i = 0; i < aLen; i++){
		aBucket[a[i] - 'a']++;
		bBucket[b[i] - 'a']++;
	}
	printf("past bucketing\n");


	for(i = 0; i < 26; i++){
		if(aBucket[i] != bBucket[i])
			return 0;
	}
	printf("past checking\n");

	free(aBucket);
	free(bBucket);
	printf("past\n");

	return 1;
}
