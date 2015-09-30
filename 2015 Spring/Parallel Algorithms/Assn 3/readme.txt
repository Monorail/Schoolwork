Alex Berliner

Usage
	To compile under Linux:
		g++ lockingdockers.cpp -pthread -std=c++11
	To run under Linux:
		./a.out [c1] [c2] [c3]
		where c1, 2, 3 are the following command line parameters:
		c1: number of threads
		c2: queue mode
			0: Locking queue
			1: Non-locking queue
			2: Intel TBB queue
		c3: Load type
			0: High push, low remove
			1: Average push and remove
			2: High remove, low push





