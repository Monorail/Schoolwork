import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Font;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.Border;
import javax.swing.border.LineBorder;
import javax.swing.border.TitledBorder;


public class TestSwingCommonFeatures extends JFrame{
	public TestSwingCommonFeatures(){
		JPanel p1 = new JPanel ( new FlowLayout(FlowLayout.LEFT,2,2));
		JButton jbtLeft = new JButton("Left");
		JButton jbtCenter= new JButton("Center");
		JButton jbtRight= new JButton("Right");
		jbtLeft.setBackground(Color.white);
		jbtCenter.setBackground(Color.green);
		jbtRight.setBackground(Color.black);
		jbtLeft.setToolTipText("DIUCKS");
		p1.add(jbtLeft);
		p1.add(jbtCenter);
		p1.add(jbtRight);
		p1.setBorder(new TitledBorder("THree buttons"));
		Font largeFont = new Font("TimesRoman", Font.BOLD, 20);
		Border lineBorder = new LineBorder(Color.black,2);
		
	}
	public static void main(String[] args) {
		
	}

}
