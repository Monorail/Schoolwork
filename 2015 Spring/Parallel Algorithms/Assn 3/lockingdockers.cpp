// my first boat rental in C++
#include <iostream>
#include <random>
#include <atomic>
#include <stdio.h>
#include <stdlib.h>
#include <mutex>
#include <string>
#include <thread>
#include "BoundedQ.cpp"
#include "tbb/concurrent_queue.h"

int numThreads = 4;
BoundedQ BQ(10, numThreads, false);
BoundedQ BQL(10, numThreads, true);
tbb::concurrent_queue<int> queue;

struct threadData{
	int ID;
	std::unique_ptr<int[]> randPool;
	std::unique_ptr<int[]> nodePool;
	int numElems;
	int numOps;
};
void run(BoundedQ* BQ, threadData* data){//(threadData* in){
	//BQ->sayHello();
	//printf("%d\n", data->ID);
	for(int i = 0; i < data->numOps; i++){
		bool success;
		if(data->randPool[i]==1) {
			success = BQ->add(data->nodePool[i]);
		}
		else {
			int* res = new int; 
			success = BQ->remove(res);
			if(success) printf("%d\n", *res);	
			else printf("e\n");			
		}
	}
}

int main() {
	numThreads = 4;
	int numElems = 100;
	int numOps = 101;
	std::thread myThreads[numThreads];
	srand(time(NULL));
	threadData bats[numThreads];
	for (int i=0; i<numThreads; i++) {
		bats[i].ID = i;
		bats[i].numElems = numElems;
		bats[i].numOps = numOps;
		bats[i].randPool.reset(new int[numOps]);
		bats[i].nodePool.reset(new int[numElems]);
		for(int j = 0; j < numElems; j++){;
			bats[i].nodePool[j] = rand()%1000;
		}
		for (int j=0; j<numOps; j++) {
			bats[i].randPool[j] = rand()%2;
		}
	}
	for (int i=0; i<numThreads; i++){
		myThreads[i] = std::thread(run, &BQ, &bats[i]);
	}
	for (int i=0; i<numThreads; i++){
		myThreads[i].join();
	}
	return 0;
}


























