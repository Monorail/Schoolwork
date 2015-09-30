/* Name: Alex Berliner
COP 3330 Spring 2013 
Assignment title: Assignment 4 - Tic-Tac-Toe 
Date: Saturday July 13, 2013 */
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class TicTacToe extends JFrame {
	private boolean playerTurn = true;
	private JButton[][] buttArr;
	private final String emptyString = "";
	private String winner = emptyString;
	private int numMoves = 0;
	private Label turnText;

	public static void main(String[] args) {
		initGame();
	}
	public static void initGame(){
		TicTacToe frame = new TicTacToe();
		frame.setTitle("Tic-Tac-Toe!");
		frame.setSize(300, 300);
		frame.setLocationRelativeTo(null);
		// frame.pack();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
		
	}
	public TicTacToe() {

		JPanel p1 = new JPanel();
		JPanel p2 = new JPanel(new BorderLayout(1, 1));
		p1.setBackground(Color.black);
		turnText = new Label("Player 1 Turn");
		turnText.setForeground(Color.RED);
		turnText.setFont(new Font("sansserif", Font.BOLD, 25));
		turnText.setAlignment(Label.CENTER);
		p2.add(turnText, BorderLayout.NORTH);
		p1.setLayout(new GridLayout(3, 3, 3, 3));
		buttArr = new JButton[3][3];
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				buttArr[i][j] = new JButton(emptyString);
				buttArr[i][j].setFont(new Font("sansserif", Font.BOLD, 36));
				buttArr[i][j].addMouseListener(new MouseAdapter() {
					public void mouseClicked(MouseEvent evt) {
						if (((JButton) evt.getSource()).getText() == emptyString && playerTurn) {
							((JButton) evt.getSource()).setText("O");
							playerTurn = !playerTurn;
							((JButton) evt.getSource()).setForeground(Color.RED);
							turnText.setForeground(Color.BLUE);
							turnText.setText("Player 2 Turn");
						} else if (((JButton) evt.getSource()).getText() == emptyString && !playerTurn) {
							((JButton) evt.getSource()).setText("X");
							playerTurn = !playerTurn;
							((JButton) evt.getSource()).setForeground(Color.BLUE);
							turnText.setForeground(Color.RED);
							turnText.setText("Player 1 Turn");
						}
						checkWin(buttArr);
						if ((winner == "X" || winner == "O")) {
							turnText.setText("Winner!");
							turnText.setForeground(Color.BLACK);
							if (JOptionPane.showConfirmDialog(null, (winner == "O" ? "Player 1" : "Player 2")
									+ " wins!\nWould you like to play again?", "Winner!", JOptionPane.YES_NO_OPTION,
									JOptionPane.QUESTION_MESSAGE) == JOptionPane.YES_OPTION) {
								resetBoard();
							} else {
								setVisible(false);
								dispose();
							}
						} else if (winner == "NoMoves") {
							if (JOptionPane.showConfirmDialog(null, "No remaining moves!\nWould you like to play again?",
									"Winner!", JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE) == JOptionPane.YES_OPTION) {
								resetBoard();
							} else {
								setVisible(false);
								dispose();
							}
						}
					}
				});
				p1.add(buttArr[i][j], BorderLayout.SOUTH);
			}
		p2.add(p1);
		add(p2, BorderLayout.CENTER);
	}

	public String checkWin(JButton[][] buttArr) {
		if (winner.equals(emptyString)) {
			for (int i = 0; i < 3; i++)
				// row check
				if (buttArr[i][0].getText() == buttArr[i][1].getText() && buttArr[i][1].getText() == buttArr[i][2].getText()
						&& buttArr[i][0].getText() != emptyString) {
					// System.out.print("Row: ");
					winner = buttArr[i][0].getText();
					return buttArr[i][0].getText();
				}
			for (int i = 0; i < 3; i++)
				// column check
				if (buttArr[0][i].getText() == buttArr[1][i].getText() && buttArr[1][i].getText() == buttArr[2][i].getText()
						&& buttArr[0][i].getText() != emptyString) {
					// System.out.print("Column: ");
					winner = buttArr[0][i].getText();
					return buttArr[0][i].getText();
				}
			if (buttArr[0][0].getText() == buttArr[1][1].getText() && buttArr[1][1].getText() == buttArr[2][2].getText()
					&& buttArr[0][0].getText() != emptyString) {
				// System.out.print("Slope Down Diag: ");
				winner = buttArr[0][0].getText();
				return buttArr[0][0].getText();
			}
			if (buttArr[2][0].getText() == buttArr[1][1].getText() && buttArr[1][1].getText() == buttArr[0][2].getText()
					&& buttArr[2][0].getText() != emptyString) {
				// System.out.print("Slope Down Diag: ");
				winner = buttArr[1][1].getText();
				return buttArr[1][1].getText();
			}
		}
		numMoves++;
		if (numMoves >= 9)
			return (winner = "NoMoves");

		return "tie";
	}
	public void resetBoard() {
		turnText.setText("Player 1 Turn");
		turnText.setForeground(Color.RED);
		playerTurn = true;
		winner = emptyString;
		numMoves = 0;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				buttArr[i][j].setText(emptyString);
			}
	}



}
