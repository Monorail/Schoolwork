import java.util.Random;
import java.util.concurrent.Semaphore;


public class Reindeer implements Runnable {

	public enum ReindeerState {AT_BEACH, AT_WARMING_SHED, AT_THE_SLEIGH};
	private ReindeerState state;
	private SantaScenario scenario;
	private Random rand = new Random();
	private Semaphore deerSem;

	/**
	 * The number associated with the reindeer
	 */
	private int number;
	
	public Reindeer(int number, SantaScenario scenario) {
		this.number = number;
		this.scenario = scenario;
		this.state = ReindeerState.AT_BEACH;
		deerSem = scenario.deerSemaphore;
	}

	@Override
	public void run() {
		while(scenario.day < 371) {
		// wait a day
		try {
			Thread.sleep(scenario.sleepTime);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		// see what we need to do:
		switch(state) {
		case AT_BEACH: { // if it is December, the reindeer might think about returning from the beach
			if (scenario.isDecember) {
				if (rand.nextDouble() < 0.1) {
					state = ReindeerState.AT_WARMING_SHED;
				}
			}
			break;			
		}
		case AT_WARMING_SHED: 
			// if all the reindeer are home, wake up santa
			try {
				deerSem.acquire();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			while(deerSem.availablePermits() > 0);
			state = ReindeerState.AT_THE_SLEIGH;
			scenario.santa.wakeUpByDeer();
			break;
		case AT_THE_SLEIGH: 
			// keep pulling
			break;
		}
		}
	};
	
	/**
	 * Report about my state
	 */
	public String toHtml() {
		return "<b>Reindeer " + number + "</b> : " + state + "<br/>";
	}
	
}
