#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int tableSize = 97;


typedef struct kvp{
	int data;
	char* str;
	struct kvp* next;
} kvp;

void add(kvp*** internalTable, int data);
void addStr(kvp*** internalTable, char* str);
int getHash(int x);

int main(){
	kvp** table = malloc(sizeof(kvp*) * tableSize);
	printf("%d\n", getStrHash("derps"));
	// int i;
	// for(i = 0; i < tableSize; i++)
	// 	table[i] = NULL;
	// add(&table, 2);
	// add(&table, 2);
	// add(&table, 2);
	// add(&table, 2);
	// add(&table, 2);
	// add(&table, 2);
	// add(&table, 2);
	return 0;
}

void add(kvp*** internalTable, int data){
	kvp** table = *internalTable;
	int hash = getHash(data)%tableSize;
	int quadIter = 0;
	int collisionHash;
	int foundSpace = 0;
	while(!foundSpace){
		collisionHash = 1;
		int i;
		for(i = 0; i < quadIter; i++)
			collisionHash = collisionHash << 1;
		collisionHash = (hash + ((quadIter > 0)? collisionHash : 0))%tableSize;
		quadIter++;
		foundSpace = (table[collisionHash] == NULL) ? 1 : 0;
	}
	hash = collisionHash;
	printf("Hash Number: %d\n", hash);
	table[hash] = malloc(sizeof(kvp));

}

// void addStr(kvp*** internalTable, int data){
// 	kvp** table = *internalTable;
// 	int hash = getHash(data)%tableSize;
// 	int quadIter = 0;
// 	int collisionHash;
// 	int foundSpace = 0;
// 	while(!foundSpace){
// 		collisionHash = 1;
// 		int i;
// 		for(i = 0; i < quadIter; i++)
// 			collisionHash = collisionHash << 1;
// 		collisionHash = (hash + ((quadIter > 0)? collisionHash : 0))%tableSize;
// 		quadIter++;
// 		foundSpace = (table[collisionHash] == NULL) ? 1 : 0;
// 	}
// 	hash = collisionHash;
// 	printf("Hash Number: %d\n", hash);
// 	table[hash] = malloc(sizeof(kvp));

// }

int getHash(int x){
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x);
    return x;
}

int getStrHash(char* str){
	if(str==NULL)
		return -1;
	int len = strlen(str);
	int i;
	int hash = 0;
	for(i = 0;i < len; i++){
		hash = (hash * 37 + (int) str[i]) % tableSize;
	}
    return hash;
}
