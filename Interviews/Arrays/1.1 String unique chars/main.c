#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int uniqueWDS(char* str);
int uniqueNDS(char* str);

int main(){
	char* str = "adsfnjsdfnjdsn";
	//printf("%s\n", (uniqueWDS(str)==1)?"unique":"not unique");
	printf("%s\n", (uniqueNDS(str)==1)?"unique":"not unique");

}

int uniqueWDS(char* str){
	if(str==NULL)
		return 1;
	int* bucket = calloc(26, sizeof(int));
	int len = strlen(str);
	int i;

	for(i = 0; i < len; i++){
		int index = str[i]-'a';
		if(bucket[index]!=0)
			return 0;
		bucket[index] = 1;
	}


	return 1;	
}

int uniqueNDS(char* str){
	if(str==NULL)
		return 1;
	int* bucket = calloc(26, sizeof(int));
	int len = strlen(str);
	int i;

	for(i = 0; i < len; i++){
		int index = str[i]-'a';
		if(bucket[index]!=0)
			return 0;
		bucket[index] = 1;
	}


	return 1;	
}
