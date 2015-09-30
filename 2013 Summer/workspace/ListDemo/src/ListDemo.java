import java.awt.BorderLayout;

import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JScrollPane;


public class ListDemo extends JFrame{
	final int NUMFLAGS = 9;
	private String[] flags = {"1","2","3","4","5","6","7","8","9"};
	private JList jlst = new JList(flags);
	
	public static void main(String[] args) {
		ListDemo frame = new ListDemo();
		frame.setSize(650,500);
		frame.setTitle("ListDemo");
		frame.setLocationRelativeTo(null);
		frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
		frame.setVisible(true);
		
	}
	public ListDemo(){
		add(new JScrollPane(jlst), BorderLayout.WEST);
		
	}

}
