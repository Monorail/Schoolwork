#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int i;
	FILE *ifp;
	ifp = fopen("input.txt", "r");
	int numWords = 0;
	char word[30];
	fscanf(ifp, "%d", &numWords);
	int *bucket;
	for(i = 0; i < numWords; i++){
		fscanf(ifp, "%s", word);
		int invalid = 0;

		bucket = calloc(26, sizeof(int));
		int wordSize = strlen(word);
		int j;
		for(j = 0; j < wordSize; j++){
			bucket[word[j] - 'a']++;
		}

		for(j = 0; j < 26; j++){
			if(bucket[j] == 0 || bucket[j] == 2) {
				continue;
			}
			invalid = 1;
			break;
		}
		printf("%s is %sa pair isogram\n", word, ((invalid == 1)? "not ": ""));
	}
	printf("\n");
	free(bucket);
}