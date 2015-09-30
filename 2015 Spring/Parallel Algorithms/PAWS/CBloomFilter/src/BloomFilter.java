import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.atomic.AtomicInteger;

public class BloomFilter<AnyType> implements Runnable{
	
	static int numThreads = 4;
	static ArrayList<Thread> threads = new ArrayList<Thread>();
	static ArrayList<BloomFilter<String>> workers = new ArrayList<BloomFilter<String>>();
	static boolean[][] hash_tables;
	static AtomicInteger finishedThreads = new AtomicInteger(0);
	//set up wait free queue for adding elements
	static ConcurrentLinkedQueue<String> opQueue = new ConcurrentLinkedQueue<String>();
	
	public static void main(String[] args) {
		// some names to insert into our data structure
		String[] names = { "Sean", "Arya", "Robb", "Bran", "Dany" };
		
		if(numThreads <= 1){
			System.out.println("You can't use <= one thread");
			return;
		}
		
		// the sizes of our respective hash tables. another (perhaps more common
		// approach is to use multiple hash functions.
		int[] capacities = {53, 59, 61, 67, 71};
		
		// create an array of 'capacities.length' hash tables
		hash_tables = new boolean[capacities.length][];
		
		ArrayList<String> allOps = new ArrayList<String>();
		
		//generate operations to perform
		Random R = new Random();
		for(int i = 0; i < 10/*000*/; i++){
			Boolean opAdd = R.nextBoolean();
			String operation = "add ";//opAdd?"add ":"con ";
			for(int j = 1+R.nextInt(11); j >=0; j--){
				char derp = (char) (R.nextInt(26) + 'a');
				operation += derp;
			}
			allOps.add(operation.split(" ")[1]);
			opQueue.add(operation);
			
			//System.out.println(operation);
		}
		for(int i = 0; i < 10/*000*/; i++){
			if(R.nextBoolean())
				opQueue.add("con " + allOps.get(i));
			else{
				String operation = "add ";//opAdd?"add ":"con ";
				for(int j = 1+R.nextInt(11); j >=0; j--){
					char derp = (char) (R.nextInt(26) + 'a');
					operation += derp;
				}
			}
			//System.out.println(operation);
		}
		
		
		
//		//replace with adding loads of stuff
//		for(String s : names)
//			insertQueue.add(s);
//		
		// create the hash tables (boolean arrays) with the desired length
		for (int i = 0; i < capacities.length; i++)
			hash_tables[i] = new boolean[capacities[i]];
		
		//initialize threads
		for (int i = 0; i < numThreads; i++) {
			BloomFilter<String> temp = new BloomFilter<String>(i);
			workers.add(temp);
			threads.add(new Thread(temp));
		}
		
		// start all threads
		for (int i = 0; i < numThreads; i++) {
			threads.get(i).start();
		}
		
//		verify that these names made it into the Bloom filter correctly
//		for (String s : names)
//			if (bloomFilter.contains(s))
//				System.out.println("Found name: " + s);
//
//		// let's create a ton of random strings and see whether they appear to
//		// be in the Bloom filter! (It will be fun.)
//		char[] rand = new char[4];
//		int cnt = 0, N = 100000;

//		for (int j = 0; j < N; j++) {
//			// generate a random string of characters; capitalize the first char
//			for (int i = 0; i < rand.length; i++)
//				rand[i] = (char) ((int) (Math.random() * 26) + ((i == 0) ? 'A'
//						: 'a'));
//
//			// convert array of random chars to a string
//			String s = new String(rand);
//
//			// these are our primary data structures: a Bloom filter and a hash set
//			HashSet<String> hashSet = new HashSet<String>();
//
//			// insert the names into the Bloom filter. also, store them in a HashSet
//			// so we can later determine in O(1) time whether a randomly generated
//			// string is one of the names from the original names[] array.
//			for (String s : names) {
//				hashSet.add(s);
//			}
//
//			// count how many randomly generated strings appear to be in the
//			// Bloom
//			// filter, but were not present in the original array (false
//			// positives)
//			if (!hashSet.contains(s) && bloomFilter.contains(s)) {
//				// System.out.println(s);
//				cnt++;
//			}
//		}

		// print the rate at which we encountered false positives
//		System.out.println("False positives: " + (double) cnt / (double) N * 100.0 + "%");
	}

	// we'll use an array of hash tables (an array of arrays) for our Bloom
	// filter
	int ID;
	public BloomFilter(int ID) {
		this.ID = ID;
	}

	@Override
	public void run() {
		String operation="";
		while((operation = opQueue.poll()) != null){
			//System.out.println(ID + " " + operation);
			String[] ops = operation.split(" ");
			if(ops[0].equals("con")){
				System.out.printf("The bloom filter %s the name %s\n", contains((AnyType) ops[1])?"may contain":"does not contain", ops[1]);
			} else {
				add((AnyType)ops[1]);
				System.out.println("Added " + ops[1]);
			}
		}
	}

	public void add(AnyType o) {
		// every object has a hashCode() method
		int hval = o.hashCode();

		// in the event of integer overflow, we want our hash value to be
		// positive
		if (hval < 0)
			hval = hval - Integer.MIN_VALUE;

		// hash the value into each of our hash tables; don't store the value
		// itself, and don't worry about collisions
		for (int i = 0; i < hash_tables.length; i++)
			hash_tables[i][hval % hash_tables[i].length] = true;
	}

	public boolean contains(AnyType o) {
		// every object has a hashCode() method
		int hval = o.hashCode();

		// in the event of integer overflow, we want our hash value to be
		// positive
		if (hval < 0)
			hval = hval - Integer.MIN_VALUE;

		// if the object does not collide with 'true' values in each hash table,
		// then it cannot have been inserted into the Bloom filter. return
		// false.
		for (int i = 0; i < hash_tables.length; i++)
			if (hash_tables[i][hval % hash_tables[i].length] == false)
				return false;

		// if we make it through the gauntlet, then we can say this value was
		// *probably* inserted into the Bloom filter
		return true;
	}

}
