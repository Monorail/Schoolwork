import javax.swing.text.Highlighter.HighlightPainter;

public class notmain {
	public static void main(String[] args) {
		final int handSize = 5;
		Deck dick = new Deck();
		dick.printDeck();
		Card[] hand1 = new Card[handSize];
		Card[] hand2 = new Card[handSize];
		Card[] hand1Sorted =new Card[handSize];
		Card[] hand2Sorted =new Card[handSize];
		for (int i = 0; i < handSize; i++) {
			hand1[i] =  dick.deal();
			hand1Sorted[i] = new Card(hand1[i].getFace(),hand1[i].getSuit());
			System.out.println(hand1[i]);
			hand2[i] =  dick.deal();
			hand2Sorted[i] = new Card(hand2[i].getFace(),hand2[i].getSuit());
		}
		hand1[0] = new Card(1, 2);
		hand1[1] = new Card(2, 2);
		hand1[2] = new Card(3, 1);
		hand1[3] = new Card(4, 2);
		hand1[4] = new Card(6, 2);
		
		hand2[0] = new Card(1, 2);
		hand2[1] = new Card(2, 2);
		hand2[2] = new Card(3, 3);
		hand2[3] = new Card(4, 2);
		hand2[4] = new Card(6, 2);
		
		Comparator comp = new Comparator(hand1,hand2);
		printHands(comp.getHand1(), comp.getHand2());
		comp.pickWinner();
	}
	static int highPair(Card[] hand) {
		int high = -1;
		for (int i = 0; i < hand.length; i++)
			for (int j = 0; j < hand.length; j++)
				if (hand[i].getFace() == hand[j].getFace() && i != j && hand[i].getFace() > high) {
					high = hand[i].getFace();
				}
		return high;
	}

	static int lowPair(Card[] hand) {
		int high = -1;
		for (int i = 0; i < hand.length; i++)
			for (int j = 0; j < hand.length; j++)
				if (hand[i].getFace() == hand[j].getFace() && i!=j) {
					if (high == -1)
						high = hand[i].getFace();
					else if (high > hand[i].getFace())
						high = hand[i].getFace();
				}
		return high;
	}

	static void printHands(Card[] hand1, Card[] hand2) {
		System.out.printf("%s\t\t\t%-30s\n", "Player 1", "Player 2");
		for (int i = 0; i < hand1.length; i++) {
			System.out.print(hand1[i]);
			System.out.printf("\t\t\t%-30s\n", hand2[i]);
		}
	}
	static int numOfSuit(Card[] hand, int suit){
		int ctr = 0;
		for (int i =0;i<hand.length;i++){
			if (hand[i].getSuit() == suit)
				ctr++;
		}
		return ctr;
	}
	static int numOfFace(Card[] hand, int face){
		int ctr = 0;
		for (int i =0;i<hand.length;i++){
			if (hand[i].getFace() == face)
				ctr++;
		}
		return ctr;
	}
	static void sortHand(Card[] hand){
		Card tempCard;
		for(int i = 0;i<hand.length;i++){
			for(int j = 0;j<hand.length;j++)
				if(hand[i].getFace()<hand[j].getFace()){
					tempCard = hand[i];
					hand[i] = hand[j];
					hand[j] = tempCard;
				}
		}
	}
}
