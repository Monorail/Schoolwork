import java.awt.BorderLayout;
import java.awt.Font;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

public class DescriptionPanel extends JPanel {
	private JLabel jlblImageTitle = new JLabel();
	private JTextArea jtaDescription = new JTextArea();

	public DescriptionPanel() {
		jlblImageTitle.setHorizontalAlignment(JLabel.CENTER);
		jlblImageTitle.setHorizontalTextPosition(JLabel.CENTER);
		jlblImageTitle.setVerticalTextPosition(JLabel.CENTER);

		jlblImageTitle.setFont(new Font("SansSerif", Font.BOLD, 16));
		jlblImageTitle.setFont(new Font("Serif", Font.PLAIN, 14));

		jtaDescription.setLineWrap(true);
		jtaDescription.setWrapStyleWord(true);
		jtaDescription.setEditable(true);

		JScrollPane scrollPane = new JScrollPane(jtaDescription);

		setLayout(new BorderLayout(5, 5));
		add(scrollPane, BorderLayout.CENTER);
		add(jlblImageTitle, BorderLayout.WEST);
	}
	public void setImageIcon(ImageIcon icon){
		jlblImageTitle.setIcon(icon);
	}
	public void setTitle(String title){

		jlblImageTitle.setText(title);
	}
	public void setDescription(String text){
		jtaDescription.setText(text);
	}
	public static void main(String[] args) {
		DescriptionPanel dp = new DescriptionPanel();
		JFrame frame = new JFrame();
		frame.setLocationRelativeTo(null);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		frame.add(dp, BorderLayout.CENTER);
		
		
	}

}
