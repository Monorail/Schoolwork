
// ** Removed: import com.sun.org.apache.xml.internal.security.utils.HelperNodeList;

public class Santa implements Runnable {

	enum SantaState {
		SLEEPING, READY_FOR_CHRISTMAS, WOKEN_UP_BY_ELVES, WOKEN_UP_BY_REINDEER
	};

	private SantaState state;
	private SantaScenario scenario; // ** Added variable GOOD JOB THANKS

	public Santa(SantaScenario scenario) {
		this.state = SantaState.SLEEPING;
		this.scenario = scenario; // ** Used unused constructor parameter
	}

	@Override
	public void run() {
		while (scenario.day < 371) {
			// wait a day...
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			//check elf states for wakeup
			
			
			for (Elf elf : scenario.elves) {
				if (elf.getState() == Elf.ElfState.AT_SANTAS_DOOR) {
					state = SantaState.WOKEN_UP_BY_ELVES;
					break;
				}
			}
			
			switch (state) {
			case SLEEPING: // if sleeping, continue to sleep
				break;
			case WOKEN_UP_BY_ELVES:
				// FIXME: help the elves who are at the door and go back to sleep
				for (Elf elf : scenario.elves) {
					if (elf.getState() == Elf.ElfState.AT_SANTAS_DOOR) {
						elf.setState(Elf.ElfState.WORKING);
					}
				}
				state = SantaState.SLEEPING;
				break;
			case WOKEN_UP_BY_REINDEER:
				// FIXME: assemble the reindeer to the sleigh then change state
				// to ready
				break;
			case READY_FOR_CHRISTMAS: // nothing more to be done
				break;
			}
		}
	}

	/**
	 * Report about my state
	 */
	
	public String toHtml() {
		return "<b>Santa : </b>" + state + "<br/>";
	}

}
