import java.awt.BorderLayout;
import java.awt.Dimension;
import java.util.ArrayList;
import java.util.List;

// ** Removed: import javax.print.attribute.standard.JobHoldUntil;
import javax.swing.JEditorPane;
import javax.swing.JFrame;
import javax.swing.JPanel;
// ** Removed: import javax.swing.JTextPane;

public class SantaScenario {

	public Santa santa;
	public List<Elf> elves;
	public List<Reindeer> reindeers;
	public boolean isDecember;
	public int day;
	private static JEditorPane textDisplay;
	
	public static void main(String args[]) {
		createVisualizer();
		SantaScenario scenario = new SantaScenario();
		scenario.isDecember = false;
		// create the participants
		// Santa
		scenario.santa = new Santa(scenario);
		Thread th = new Thread(scenario.santa,"Santa"); // ** Added thread name for debugging purposes
		th.start();
		// The elves: in this case: 10
		scenario.elves = new ArrayList<>();
		for(int i = 0; i != 10; i++) {
			Elf elf = new Elf(i+1, scenario);
			scenario.elves.add(elf);
			th = new Thread(elf,"Elf "+i); // ** Added thread name for debugging purposes
			th.start();
		}
		// The reindeer: in this case: 9
		scenario.reindeers = new ArrayList<>();
		for(int i=0; i != 9; i++) {
			//Reindeer reindeer = new Reindeer(i+1, scenario);
			//scenario.reindeers.add(reindeer);
			//th = new Thread(reindeer,"Reindeer "+i); // ** Added thread name for debugging purposes
			//th.start();
		}
		// now, start the passing of time
		for(scenario.day = 1; scenario.day < 500; scenario.day++) {
			updateVisualizer(scenario);
			// wait a day
			try {
				Thread.sleep(500);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			// turn on December
			if (scenario.day > (365 - 31)) {
				scenario.isDecember = true;
			}			
		}
	}
	
	/**
	 *   Creates a window in which we are visualizing the text display
	 */
	private static void createVisualizer() {
		JPanel panel = new JPanel();
		panel.setLayout(new BorderLayout());
		JFrame frame = new JFrame("Santa Fall 2014 visualizer");
		frame.setContentPane(panel);
		// fill in the panel
		textDisplay = new JEditorPane();
		textDisplay.setContentType("text/html");
		textDisplay.setPreferredSize(new Dimension(500,500));
		textDisplay.setEditable(false);
		panel.add(textDisplay);
		frame.pack();
		frame.setVisible(true);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // ** Made program terminate when frame closed
	}
	
	/**
	 *  Update visualizer - call it everytime something happens!!!
	 */
	public static void updateVisualizer(SantaScenario scenario) {
		StringBuffer tmp = new StringBuffer();
		tmp.append("<h1>Day " + scenario.day + "</h1>");
		tmp.append(scenario.santa.toHtml());
		for(Elf elf: scenario.elves) {
			tmp.append(elf.toHtml());
		}
		for(Reindeer reindeer: scenario.reindeers) {
			tmp.append(reindeer.toHtml());
		}
		synchronized(textDisplay) { // ** Added synchronized
			textDisplay.setText(tmp.toString());
		}
	}
	
}
