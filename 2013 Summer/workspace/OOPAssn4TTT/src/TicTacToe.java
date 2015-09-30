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

	public void resetBoard() {
		//resets all variables relevant to the game state
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

	public TicTacToe() {
		//make a board panel p1 and a main panel p2
		JPanel p1 = new JPanel();
		JPanel p2 = new JPanel(new BorderLayout(1, 1));
		//set the background color of the game panel
		p1.setBackground(Color.black);
		//initialize text
		turnText = new Label("Player 1 Turn");
		turnText.setForeground(Color.RED);
		turnText.setFont(new Font("sansserif", Font.BOLD, 25));
		turnText.setAlignment(Label.CENTER);
		p2.add(turnText, BorderLayout.NORTH);
		p1.setLayout(new GridLayout(3, 3, 3, 3));
		//tic tac toe button creation
		//making and array of buttons for the game to be based on
		buttArr = new JButton[3][3];
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				buttArr[i][j] = new JButton(emptyString);
				buttArr[i][j].setFont(new Font("sansserif", Font.BOLD, 36));
				//construct the button click code
				buttArr[i][j].addMouseListener(new MouseAdapter() {
					public void mouseClicked(MouseEvent evt) {
						//checks to see whose turn it is, and sets the button text appropriately, then passes the turn
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
						//updates the winner variable that holds who had won the game, if any
						checkWin(buttArr);
						if ((winner == "X" || winner == "O")) {
							//updates the scoreboard to say Winner!
							turnText.setText("Winner!");
							turnText.setForeground(Color.BLACK);
							//makes a popup that says who the winner is and asks if they want to play again
							if (JOptionPane.showConfirmDialog(null, (winner == "O" ? "Player 1" : "Player 2")
									+ " wins!\nWould you like to play again?", "Winner!", JOptionPane.YES_NO_OPTION,
									JOptionPane.QUESTION_MESSAGE) == JOptionPane.YES_OPTION) {
								resetBoard();
							} else {
								setVisible(false);
								dispose();
							}
							//popup if it's a tie
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
					//if a win is detected, it takes the string from one of the winning buttons and passes it to the winner function
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
		//increments to 9 to see if the game is a tie
		numMoves++;
		if (numMoves >= 9)
			return (winner = "NoMoves");

		return "tie";
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
	public static void main(String[] args) {
		initGame();
	}

}
