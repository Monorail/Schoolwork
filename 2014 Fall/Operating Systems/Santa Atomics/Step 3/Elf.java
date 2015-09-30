import java.util.Random;

public class Elf implements Runnable {

	enum ElfState {
		WORKING, TROUBLE, AT_SANTAS_DOOR
	};

	private ElfState state;
	/**
	 * The number associated with the Elf
	 */
	private int number;
	private Random rand = new Random();
	private SantaScenario scenario;
	private boolean movingToDoor = false;
	public Elf(int number, SantaScenario scenario) {
		this.number = number;
		this.scenario = scenario;
		this.state = ElfState.WORKING;
		scenario.elvesInTrouble[number-1] = false;
	}
	
	
	public ElfState getState() {
		return state;
	}

	/**
	 * Santa might call this function to fix the trouble
	 * @param state
	 */
	public void setState(ElfState state) {
		this.state = state;
	}
	public boolean isTroubled(){
		return state == Elf.ElfState.TROUBLE;
	}
	public void backToWork(){
		state = ElfState.WORKING;
	}
	
	public boolean isAtDoor(){
		return state == ElfState.AT_SANTAS_DOOR;
	}
	
	@Override
	public void run() {
		// ** Moved the sleep into the while loop		
		while (scenario.day < 371) {
			// wait a day
			try {
				Thread.sleep(scenario.sleepTime);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			switch (state) {
			case WORKING: {
				// at each day, there is a 1% chance that an elf runs into
				// trouble.
				if (rand.nextDouble() < .01) {
					state = ElfState.TROUBLE;
					scenario.elvesInTrouble[number-1] = true;
				}
				break;
			}
			case TROUBLE:
				// FIXME: if possible, move to Santa's door
				int troubledElves = 0;
				for(Boolean bool : scenario.elvesInTrouble){
					troubledElves += bool?1:0;
				}
				
				if(troubledElves >= 3){
					state=ElfState.AT_SANTAS_DOOR;
					movingToDoor = true;
				}
				break;
				
			case AT_SANTAS_DOOR:
				// FIXME: if feasible, wake up Santa
				
				scenario.santa.wakeUp();
				if(movingToDoor){
					movingToDoor = false;
					scenario.elvesInTrouble[number-1] = false;
				}
				break;
			}
		}
	}
	
	/**
	 * Report about my state in the HTML format
	 */
	public String toHtml() {
		String temp = "<b>Elf " + number + " </b>: ";
		switch(state) {
		case WORKING:
			temp += "<span color=green> WORKING </span>";
			break;
		case TROUBLE:
			temp += "<span color=red> TROUBLE </span>";
			break;
		case AT_SANTAS_DOOR:
			temp += "<span color=blue> AT_SANTAS_DOOR </span>";
			break;			
		}
		temp += "<br/>";
		return temp;
	}

}
