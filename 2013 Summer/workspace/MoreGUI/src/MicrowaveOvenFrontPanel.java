import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;


public class MicrowaveOvenFrontPanel extends JFrame{
	public MicrowaveOvenFrontPanel(){
		JPanel p1 = new JPanel();
		p1.setLayout(new GridLayout(4,3,5,5));
		for (int i = 1; i <= 9;i++)
			p1.add(new JButton("" + i));
		p1.add(new JButton("" + 0));
		JButton start  = new JButton("Start");
		start.setBackground(Color.GREEN);
		p1.add(start);
		JButton stop = new JButton("stop");
		stop.setBackground(Color.RED);
		p1.add(stop);
		JPanel p2 = new JPanel(new BorderLayout(1,1));
		p2.add(new JTextField("sdfasdfas"), BorderLayout.NORTH);
		p2.add(p1, BorderLayout.EAST);
		add(p2, BorderLayout.EAST);
		//add(new JButton("Fooasd"), BorderLayout.CENTER);
	}
	public static void main(String[] args) {
		MicrowaveOvenFrontPanel frame = new MicrowaveOvenFrontPanel();
		frame.setTitle("sadfssdfd");
		frame.setSize(400,250);
		frame.pack();
		frame.setLocationRelativeTo(null);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}

}
