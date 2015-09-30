import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Random;
import java.util.Scanner;
import java.util.concurrent.atomic.AtomicBoolean;

public class Philosopher implements Runnable {

	static int numThreads = 5;
	static ArrayList<Thread> threads = new ArrayList<Thread>();
	static ArrayList<Philosopher> workers = new ArrayList<Philosopher>();
	static AtomicBoolean[] chopsticks;
	static boolean run = true;
	static PrintWriter write;
	public static void main(String[] args) throws InterruptedException, FileNotFoundException{
		if(args.length == 1)
			numThreads = Integer.valueOf(args[0]);
		
		if(numThreads <= 1){
			System.out.println("You can't use <= one thread");
			return;
		}
		
		write = new PrintWriter("out.txt");
		System.out.println("start");
		chopsticks = new AtomicBoolean[numThreads];
		for(int i = 0; i < numThreads; i++)
			chopsticks[i] = new AtomicBoolean(false);
		// create all threads
		for (int i = 0; i < numThreads; i++) {
			Philosopher temp = new Philosopher(i);
			workers.add(temp);
			threads.add(new Thread(temp));
		}

		// start all threads
		for (int i = 0; i < numThreads; i++) {
			threads.get(i).start();
		}
		Scanner sc = new Scanner(System.in);
		// wait for all threads to finish before continuing
		sc.nextLine();
		run = false;
		write.flush();
	}

	int ID;
	public Philosopher(int ID) {
		this.ID = ID;
	}

	public enum philState {
		THINKING, HUNGRY, EATING
	}

	@Override
	public void run() {
		Random R = new Random();
		philState state = philState.THINKING;
		while (run) {
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			switch (state) {
			case THINKING:
				System.out.println(ID +" is now thinking.");
				if (R.nextInt() % 100 < 30) {
					state = philState.HUNGRY;
				}
				break;
			case HUNGRY:
				System.out.println(ID + " is now hungrying.");
					if(!tryAcquire()){
						//System.out.println("TA() false");
						break;
					} 
				state = philState.EATING;
				//System.out.println(ID + " bazinga");
				break;
			case EATING:
				System.out.println(ID + " is now eating");
				chopsticks[ID].set(false);
				chopsticks[(ID + 1) % numThreads].set(false);
				state = philState.THINKING;
				break;
			default:
				break;
			}
		}

	}
	
	// 
	boolean tryAcquire(){ 
		//System.out.println(ID + " in tryAcquire");
		//raise chopstick 1 and quit if it's already raised
		
		//wait until both chopsticks are lowered
		while(chopsticks[ID].get() || chopsticks[(ID + 1) % numThreads].get());
		
		//raise and lock chopstick 1 
		boolean c1 = chopsticks[ID].compareAndSet(false, true);		
		if(!c1) return false;
		
		// raise and lock chopstick 2. If it's raised then lower cs 1 and quit
		boolean c2 = chopsticks[(ID + 1) % numThreads].compareAndSet(false, true);
		if(!c2) {
			chopsticks[ID].set(false);
			return false;
		}
		if(!chopsticks[ID].get() || !chopsticks[(ID + 1) % numThreads].get())
			System.out.println("I HAVE GOTTEN TO THE END AND AM RETURNING TRUE BUT MY LOCKS ARE WRONG");
//		else System.out.println(ID + " lock acquired");
		return true;
	}
}
