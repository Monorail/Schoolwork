import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;
import java.util.concurrent.atomic.AtomicBoolean;

public class Philosopher implements Runnable {

	static int numThreads = 5;
	static ArrayList<Thread> threads = new ArrayList<Thread>();
	static ArrayList<Philosopher> workers = new ArrayList<Philosopher>();
	static AtomicBoolean[] chopsticks;
	static boolean run = true;
	public static void main(String[] args) throws InterruptedException, FileNotFoundException {
		if(numThreads<1){
			System.out.println("You can't use ");
		}
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
	}

	int ID;

	public Philosopher(int ID) {
		this.ID = ID;
	}

	//state enum
	public enum philState {
		THINKING, HUNGRY, EATING
	}

	@Override
	public void run() {
		Random R = new Random();
		philState state = philState.THINKING;
		while (run) {
			switch (state) {
			case THINKING:
				System.out.println(ID +" is now thinking.");
				if (R.nextInt() % 100 < 30) {
					state = philState.HUNGRY;
				}
				break;
			case HUNGRY:
				System.out.println(ID + " is now hungrying.");
				while(run){
					while(sticksDown() && run);
					if(!tryAcquire()){
						break;
					}
					
				}
				if(!run)
					break;
				state = philState.EATING;
				break;
			case EATING:
				System.out.println(ID + " is now eating");
				//reset chopsticks when done eating
				chopsticks[ID].set(false);
				chopsticks[(ID + 1) % numThreads].set(false);
				state = philState.THINKING;
				break;
			default:
				break;
			}
		}

	}
	boolean sticksDown(){
		return chopsticks[(ID + 1) % numThreads].get() && chopsticks[ID].get(); 
	}
	boolean tryAcquire(){ 
		//raise both chopsticks 
		boolean c1 = chopsticks[ID].getAndSet(true);
		boolean c2 = chopsticks[(ID + 1) % numThreads].getAndSet(true);
		//return true if both were raised successfully
		return !c1 && !c2;
		
	}
}
