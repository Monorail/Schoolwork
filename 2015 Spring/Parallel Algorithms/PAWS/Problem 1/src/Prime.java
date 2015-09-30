// Alex Berliner
// al298842
// COP 4520

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Collections;

public class Prime implements Runnable {

	static int numThreads = 8;
	static ArrayList<Thread> threads = new ArrayList<Thread>();
	static ArrayList<Prime> workers = new ArrayList<Prime>();

	public static void main(String[] args) throws InterruptedException,
			FileNotFoundException, UnsupportedEncodingException {
		//create all threads
		for (int i = 0; i < numThreads; i++) {
			Prime temp = new Prime(i);
			workers.add(temp);
			threads.add(new Thread(temp));
		}
		long startTime = System.currentTimeMillis();

		// start all threads
		for (int i = 0; i < numThreads; i++) {
			threads.get(i).start();
		}
		
		// wait for all threads to finish before continuing
		for (int i = 0; i < numThreads; i++)
			threads.get(i).join();
		// System.out.println("all done");

		// initialize sum = 2 and numPrimes = 1 to count
		// for 2 without logic
		long sum = 2;
		long numPrimes = 1;
		// combine top prime lists from all threads, then cut to top 10
		ArrayList<Integer> finalSortedList = new ArrayList<Integer>();
		for (Prime p : workers) {
			sum += p.sumCtr;
			numPrimes += p.numFound;
			finalSortedList.addAll(p.sortedList);

			Collections.sort(finalSortedList);
			Collections.reverse(finalSortedList);

			while (finalSortedList.size() > 10)
				finalSortedList.remove(10);

			Collections.reverse(finalSortedList);
		}
		
		// write statistics to prime.txt
		PrintWriter writer = new PrintWriter("primes.txt");
		writer.println("Number of primes found: " + numPrimes);
		writer.println("Sum of primes: " + sum);
		writer.println("Time taken: "
				+ (System.currentTimeMillis() - startTime) + "ms");
		writer.println("Top primes L-H");
		for (int num : finalSortedList)
			writer.println(num);
		writer.close();
		System.out.println("Done.");
	}

	int ID;
	long sumCtr = 0;
	long numFound = 0;
	ArrayList<Integer> sortedList = new ArrayList<Integer>();

	public Prime(int ID) {
		this.ID = ID;
	}

	public void run() {
		// System.out.println(ID + " start");
		int incVal = 2 * numThreads;
		for (int i = (ID * 2) + 3; i < 100000000; i += incVal) {
			if (isPrime(i)) {
				sumCtr += i;
				numFound++;
				sortedList.add(i);
				// all threads maintain a sorted list of top primes 
				// found for final global comparison at the end.
				// sort list to remove lowest value
				Collections.sort(sortedList);
				
				// remove lowest value if there are more than 10
				if(sortedList.size() > 10)
					sortedList.remove(0);
			}
		}
		// System.out.println(ID + " done at " + System.currentTimeMillis());
	}

	boolean isPrime(int num) {
		if (num % 2 == 0)
			return false;
		for (int i = 3; i * i <= num; i += 2)
			if (num % i == 0)
				return false;
		return true;
	}
}