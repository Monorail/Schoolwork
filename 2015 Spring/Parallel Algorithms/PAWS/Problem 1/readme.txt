Alex Berliner
al298842
COP 4520

Language used: Java

To compile under Windows with console:
	Change directory to the directory containing Primes.java
	run "javac Primes.java"
	run "java Primes"

"primes.txt" will appear in the same directory when "Done." is printed in the console.

This program enumerates all of the numbers that must be checked for primality by assigning each thread a subset of the 10^8 numbers based on their ID. The naive method of solving this problem is to break up the 10^8 numbers sequentially, so that the first thread tests the first set of 10^8/8 numbers, the second thread tests the second set of 10^8/8 numbers, etc. Although this method works, it is terribly slow since the first thread has to do significantly less calculations than the last thread, since the numbers in the beginning of the 10^8 range are magnitudes smaller than those at the end of the range. As a synchronization-free solution to this load balancing problem, this program assigns each thread to check every 16th number (twice the number of threads) for primality. This ensures that all threads get an equal share of the numbers with all sizes to check. The equation that is used to determine which numbers a thread works on is 
	(thread_id * 2 + 3) + (num_threads * 2 * i)
where i iterates by 1 each loop. The loop this iterator is used in will break when the number yielded by the equation exceeds 10^8. It also guarantees that all possible primes (all odds) are attempted since it is of the form 2k + 1.

In regard to the statistics that must be provided at the end of the run, I originally wanted to have all threads work on the same "top" list and sum counter in main, but quickly discovered that the constant locking of the common list and sum counter to add the most recently found prime was causing constant locking with accompanying slowdowns. I found that it was best to have each thread maintain its own local prime list and sum counter that it can work on in its own time, and have main compile the final results when all of the threads were done executing.

Deadlock / starvation:
This program will not incur deadlock or starvation because the threads work autonomously until completion; no synchronization constructs were used. The bounds are also rigidly defined with only purely mathematical operations being performed, so it is very unlikely that a thread will fail to terminate.

Efficiency:
When running this program serially, it took around 105 seconds to complete. After converting the program to a multi-threaded approach, the subsequent time taken was reduced to around 43 seconds, a major improvement.