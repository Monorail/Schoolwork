public class Comparator {
	String handVal1 = "", handVal2 = "";
	private final int numFaces = 13, numSuits = 4;
	Card[] hand1, hand2;
	private int handSize;
	int[] faceBuck1 = new int[numFaces], faceBuck2 = new int[numFaces];
	int[] suitBuck1 = new int[numSuits], suitBuck2 = new int[numSuits];
	boolean debug = false;

	public Comparator(Card[] hand1, Card[] hand2) {
		handSize = hand1.length;
		this.hand1 = new Card[handSize];
		this.hand2 = new Card[handSize];
		for (int i = 0; i < handSize; i++) {
			this.hand1[i] = new Card(hand1[i].getFace(), hand1[i].getSuit());
			this.hand2[i] = new Card(hand2[i].getFace(), hand2[i].getSuit());
		}
		sortHand(this.hand1);
		sortHand(this.hand2);
		for (int i = 0; i < numFaces; i++) {
			faceBuck1[i] = numOfFace(hand1, i);
			faceBuck2[i] = numOfFace(hand2, i);
		}
		for (int i = 0; i < numSuits; i++) {
			suitBuck1[i] = numOfSuit(hand1, i);
			suitBuck2[i] = numOfSuit(hand2, i);
		}
	}
	public void printHands(){
		System.out.println("Hand Values:");
		System.out.println(handVal1 + "\t\t" + handVal2);
	}

	public void pickWinner(){
		int winner = fourOak();
		if (handVal1 == "")
			handVal1 = "high card";
		if (handVal2 == "")
			handVal2 = "high card";
		printHands();
		if(winner == 1)
			System.out.println("Player 1 wins!");
		else if (winner ==2)
			System.out.println("Player 2 wins!");
		else 
			System.out.println("It was a tie!");
	}
	public int fourOak() {// noted
		boolean hasHand1 = false, hasHand2 = false;
		int num1 = 0, num2 = 0;
		if (debug)
			System.out.println("fourOak()");
		for (int i = numFaces - 1; i >= 0; i--) {
			if (faceBuck1[i] == 4) {
				// System.out.println(faceBuck1[i]);
				hasHand1 = true;
				num1 = i;
			}
			if (faceBuck2[i] == 4) {
				// System.out.println("facebuck2" + faceBuck2[i]);
				hasHand2 = true;
				num2 = i;
			}
		}
		if (hasHand1 && handVal1 == "")
			handVal1 = "four of a kind";
		if (hasHand2 && handVal2 == "")
			handVal2 = "four of a kind";
		if (hasHand1 && hasHand2)
			return (num1 > num2 ? 1 : 2);
		else if (hasHand1 && !hasHand2)
			return 1;
		else if (!hasHand1 && hasHand2)
			return 2;
		else
			return fullHouse();
	}

	public int fullHouse() {// noted
		if (debug)
			System.out.println("fullHouse()");
		boolean hasHand1 = false, hasHand2 = false;
		int twoCtr1 = 0, twoCtr2 = 0;
		int threeCtr1 = 0, threeCtr2 = 0;
		int twoNum1 = 0, threeNum1 = 0, twoNum2 = 0, threeNum2 = 0;
		for (int i = numFaces - 1; i >= 0; i--) {
			if (faceBuck1[i] == 2) {
				twoCtr1++;
				twoNum1 = i;
			}
			if (faceBuck2[i] == 2) {
				twoCtr2++;
				twoNum2 = i;
			}
			if (faceBuck1[i] == 3) {
				threeCtr1++;
				threeNum1 = i;
			}
			if (faceBuck2[i] == 3)
				threeCtr2++;
			threeNum2 = i;
		}
		if (hasHand1 && handVal1 == "")
			handVal1 = "full house";
		if (hasHand2 && handVal2 == "")
			handVal2 = "full house";
		if (twoCtr1 == 2 && threeCtr1 == 3)
			hasHand1 = true;
		if (twoCtr2 == 2 && threeCtr2 == 3)
			hasHand2 = true;
		if (hasHand1 && hasHand2)
			return (threeNum1 > threeNum2 ? 1 : 2);
		else if (hasHand1 && !hasHand2)
			return 1;
		else if (!hasHand1 && hasHand2)
			return 2;
		else
			return flush();
	}

	public int flush() {// noted
		if (debug)
			System.out.println("flush()");
		boolean hasHand1 = true, hasHand2 = true;
		for (int i = 0; i < handSize - 1; i++) {
			if (hand1[i].getSuit() != hand1[i + 1].getSuit()) {
				hasHand1 = false;
			}
			if (hand2[i].getSuit() != hand2[i + 1].getSuit())
				hasHand2 = false;
		}
		if (hasHand1 && handVal1 == "")
			handVal1 = "flush";
		if (hasHand2 && handVal2 == "")
			handVal2 = "flush";
		if (!hasHand1 && !hasHand2)
			return straight();
		else if (hasHand1 && !hasHand2)
			return 1;
		else if (!hasHand1 && hasHand2)
			return 2;
		else
			return highCard();
	}

	public int straight() {
		boolean hasHand1 = true, hasHand2 = true;
		if (debug)
			System.out.println("straight()");
		for (int i = 0; i < handSize - 1; i++) {
			if (hand1[i].getFace() != hand1[i + 1].getFace() - 1) {
				hasHand1 = false;
			}
			if (hand2[i].getFace() != hand2[i + 1].getFace() - 1)
				hasHand2 = false;
		}
		if (hasHand1 && handVal1 == "")
			handVal1 = "straight";
		if (hasHand2 && handVal2 == "")
			handVal2 = "straight";

		if (hasHand1 && hasHand2)
			return highCard();
		else if (hasHand1 && !hasHand2)
			return 1;
		else if (!hasHand1 && hasHand2)
			return 2;
		else if (!hasHand1 && !hasHand2)
			return threeOak();
		else
			return -1;

	}

	public int threeOak() {
		boolean hasHand1 = false, hasHand2 = false;
		if (debug)
			if (debug)
				System.out.println("threeOak()");
		for (int i = numFaces - 1; i >= 0; i--) {
			if (faceBuck1[i] == 3) {
				if (handVal1 == "")
					handVal1 = "three of a kind";
				hasHand1 = true;
			}
			if (faceBuck2[i] == 3) {
				if (handVal2 == "")
					handVal2 = "three of a kind";
				hasHand2 = true;
			}
			if (hasHand1 && hasHand2)
				return onePair();
			else if (hasHand1 && !hasHand2)
				return 1;
			else if (!hasHand1 && hasHand2)
				return 2;
			else if (!hasHand1 && !hasHand2)
				return twoPair();
		}
		return -1;
	}

	public int twoPair() {
		boolean hasHand1 = false, hasHand2 = false;// stopping point: about to
													// assimilate 106-114
		if (debug)
			System.out.println("twoPair()");
		int ctr1 = 0, ctr2 = 0;
		for (int i = numFaces - 1; i >= 0; i--) {
			if (faceBuck1[i] == 2)
				ctr1++;
			if (faceBuck2[i] == 2)
				ctr2++;
		}
		if (ctr1 != 2 && ctr2 != 2)
			return onePair();
		for (int i = numFaces - 1; i >= 0; i--) {
			if (faceBuck1[i] == 2 && faceBuck2[i] == 2)
				continue;
			else if (faceBuck1[i] == 2) {
				if (handVal1 == "")
					handVal1 = "two pair";
				hasHand1 = true;
			} else if (faceBuck2[i] == 2) {
				if (handVal2 == "")
					handVal2 = "two pair";
				hasHand2 = true;
			}
		}

		if (hasHand1 && hasHand2)
			return highCard();
		else if (hasHand1 && !hasHand2)
			return 1;
		else if (!hasHand1 && hasHand2)
			return 2;
		else if (!hasHand1 && !hasHand2)
			return onePair();
		else
			return -1;
	}

	public int onePair() {
		boolean hasHand1 = false, hasHand2 = false;// stopping point: about to
													// assimilate 106-114
		if (debug)
			System.out.println("OnePair()");
		int ctr1 = 0, ctr2 = 0;
		for (int i = numFaces - 1; i >= 0; i--) {
			if (faceBuck1[i] == 2)
				ctr1++;
			if (faceBuck2[i] == 2)
				ctr2++;
		}
		if (ctr1 == 1) {
			if (handVal1 == "")
				handVal1 = "one pair";
			hasHand1 = true;
		}
		if (ctr2 == 1) {
			if (handVal2 == "")
				handVal2 = "one pair";
			hasHand2 = true;
		}
		if (hasHand1 && !hasHand2)
			return 1;
		else if (!hasHand1 && hasHand2)
			return 2;
		else
			return highCard();
	}

	public int highCard() {
		boolean hasHand1 = false, hasHand2 = false;
		if (debug)
			System.out.println("highCard()");
		for (int i = handSize - 1; i >= 0; i--) {
			if (hand1[i].getFace() > hand2[i].getFace()) {
				hasHand1 = true;
				break;
			} else if (hand1[i].getFace() < hand2[i].getFace()) {
				hasHand2 = true;
				break;
			}
		}
		if (hasHand1 && !hasHand2)
			return 1;
		else if (!hasHand1 && hasHand2)
			return 2;
		else
			return -1;
	}

	public void sortHand(Card[] hand) {
		Card tempCard;
		for (int i = 0; i < hand.length; i++) {
			for (int j = 0; j < hand.length; j++)
				if (hand[i].getFace() < hand[j].getFace()) {
					tempCard = hand[i];
					hand[i] = hand[j];
					hand[j] = tempCard;
				}
		}
	}

	public int numOfSuit(Card[] hand, int suit) {
		int ctr = 0;
		for (int i = 0; i < hand.length; i++) {
			if (hand[i].getSuit() == suit)
				ctr++;
		}
		return ctr;
	}

	public int numOfFace(Card[] hand, int face) {
		int ctr = 0;
		for (int i = 0; i < hand.length; i++) {
			if (hand[i].getFace() == face)
				ctr++;
		}
		return ctr;
	}

	public Card[] getHand1() {
		return hand1;
	}

	public Card[] getHand2() {
		return hand2;
	}
}
