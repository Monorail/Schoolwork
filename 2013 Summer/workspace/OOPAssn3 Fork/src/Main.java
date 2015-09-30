public class Main {
	public static void main(String[] args) {
		final int handSize = 5;
		Deck deck = new Deck();
		Card[] hand1 = new Card[handSize];
		Card[] hand2 = new Card[handSize];
		Card[] hand1Sorted = new Card[handSize];
		Card[] hand2Sorted = new Card[handSize];
		//dealing cards into hand sized card arrays
		for (int i = 0; i < handSize; i++) {
			hand1[i] = deck.deal();
			hand1Sorted[i] = new Card(hand1[i].getFace(), hand1[i].getSuit());
			// System.out.println(hand1[i]);
			hand2[i] = deck.deal();
			hand2Sorted[i] = new Card(hand2[i].getFace(), hand2[i].getSuit());
		}
//		 hand1[0] = new Card(3, 2);
//		 hand1[1] = new Card(3, 2);
//		 hand1[2] = new Card(3, 3);
//		 hand1[3] = new Card(2, 2);
//		 hand1[4] = new Card(2, 2);
//
//		 hand2[0] = new Card(3, 2);
//		 hand2[1] = new Card(3, 2);
//		 hand2[2] = new Card(3, 2);
//		 hand2[3] = new Card(4, 2);
//		 hand2[4] = new Card(4, 1);
		//create object for playing poker
		Comparator comp = new Comparator(hand1, hand2);
		comp.pickWinner();
		comp.printHands();
	}
}
