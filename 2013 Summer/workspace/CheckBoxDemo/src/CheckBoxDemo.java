import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JPanel;


public class CheckBoxDemo extends JFrame implements ItemListener{
	private JCheckBox jchkCentered = new JCheckBox("Centered");
	private JCheckBox jchkBold= new JCheckBox("Bold");
	private JCheckBox jchkItalic= new JCheckBox("Italic");
	
	
	public static void main(String[] args) {
		CheckBoxDemo frame = new CheckBoxDemo();
		frame.setTitle("dsfasdfa");
		frame.setLocationRelativeTo(null);
		frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
		frame.setSize(500,200);
		frame.setVisible(true);
	}
	public CheckBoxDemo(){
		jchkCentered.setMnemonic('C');
		jchkBold.setMnemonic('B');
		jchkItalic.setMnemonic('I');
		JPanel jpCheckBoxes = new JPanel();
		jpCheckBoxes.setLayout(new GridLayout(3,1));
		jpCheckBoxes.add(jchkCentered);
		jpCheckBoxes.add(jchkBold);
		jpCheckBoxes.add(jchkItalic);
		add(jpCheckBoxes,BorderLayout.EAST);
		
	}
	@Override
	public void itemStateChanged(ItemEvent arg0) {
		// TODO Auto-generated method stub
		
	}

}
