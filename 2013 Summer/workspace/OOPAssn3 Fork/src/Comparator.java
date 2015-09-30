public class Comparator {
	private String handVal1 = "", handVal2 = "";
	private final int numFaces = 13, numSuits = 4;
	private boolean hasHand1 = false, hasHand2 = false;
	private Card[] hand1, hand2;
	private int handSize;
	private int[] faceBuck1 = new int[numFaces], faceBuck2 = new int[numFaces];
	private int[] suitBuck1 = new int[numSuits], suitBuck2 = new int[numSuits];
	private boolean debug = false;
	private int winner;
	// the buckets are arrays with the number of elements equal to the number of
	// suits and faces.

	// the number of each face or suit in a hand is put into the bucket and can
	// be used to quickly see
	// how many of each card there is in a hand.
	public Comparator(Card[] hand1, Card[] hand2) {
		handSize = hand1.length;
		this.hand1 = new Card[handSize];
		this.hand2 = new Card[handSize];
		for (int i = 0; i < handSize; i++) {
			// set the internal hands equal to the values of the passed in ones
			this.hand1[i] = new Card(hand1[i].getFace(), hand1[i].getSuit());
			this.hand2[i] = new Card(hand2[i].getFace(), hand2[i].getSuit());
		}
		// sort internal hands
		sortHand(this.hand1);
		sortHand(this.hand2);
		// set up the buckets
		for (int i = 0; i < numFaces; i++) {
			faceBuck1[i] = numOfFace(hand1, i);
			faceBuck2[i] = numOfFace(hand2, i);
		}
		for (int i = 0; i < numSuits; i++) {
			suitBuck1[i] = numOfSuit(hand1, i);
			suitBuck2[i] = numOfSuit(hand2, i);
		}
	}

	public void printHands( ) {
		System.out.printf("%-30s%-30s\n", "Player 1", "Player 2");
		//print hands and players with formatting
		for (int i = 0; i < hand1.length; i++) {
			System.out.printf("%-30s%-30s\n", hand1[i], hand2[i]);
		}
		System.out.println();
		System.out.printf("%-30s%-30s\n\n", handVal1, handVal2);
		if (winner == 1)
			System.out.println("Player 1 wins!");
		else if (winner == 2)
			System.out.println("Player 2 wins!");
		else
			System.out.println("It was a tie!");
	}

	public void pickWinner() {
		// this method contains the logic for determining the winner
		winner = -1;
		winner = highCard();
		int temp;
		handVal1 = "high card";
		handVal2 = "high card";
		// all the rank functions return 1 if the first player won
		// 2 if the second player won, and -1 if neither had the hand or if it
		// was a tie.
		// this makes it easy to just set the winner equal to the winning player
		// if the number returned isn't -1
		if ((temp = onePair()) != -1)
			winner = temp;
		setHandVals("one pair");
		if ((temp = twoPair()) != -1)
			winner = temp;
		setHandVals("two pair");
		if ((temp = threeOak()) != -1)
			winner = temp;
		setHandVals("three of a kind");
		if ((temp = straight()) != -1)
			winner = temp;
		setHandVals("straight");
		if ((temp = flush()) != -1)
			winner = temp;
		setHandVals("flush");
		if ((temp = fullHouse()) != -1)
			winner = temp;
		setHandVals("full house");
		if ((temp = fourOak()) != -1)
			winner = temp;
		setHandVals("four of a kind");
	}

	public int fourOak() {//
		hasHand1 = false;
		hasHand2 = false;
		int num1 = 0, num2 = 0;
		if (debug)
			System.out.println("fourOak()");
		// backwards for loop to see if there are any four of a kinds.
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
		// logic path for determining who has this rank
		if (hasHand1 && hasHand2)
			return (num1 > num2 ? 1 : 2);
		else if (hasHand1 && !hasHand2)
			return 1;
		else if (!hasHand1 && hasHand2)
			return 2;
		else
			return -1;
	}

	public int fullHouse() {//
		hasHand1 = false;
		hasHand2 = false;
		if (debug)
			System.out.println("fullHouse()");
		int twoCtr1 = 0, twoCtr2 = 0;
		int threeCtr1 = 0, threeCtr2 = 0;
		//using counters to see if there are exactly a two pair and a three pair in a hand
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
		//ifs to see if there's a full house based on the couners
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
			return -1;
	}

	public int flush() {//
		hasHand1 = true;
		hasHand2 = true;
		if (debug)
			System.out.println("flush()");
		//checks to see if the current card has the same suit as the next card
		//terminates at n-1 cards to avoid overflow
		for (int i = 0; i < handSize - 1; i++) {
			if (hand1[i].getSuit() != hand1[i + 1].getSuit()) {
				hasHand1 = false;
			}
			if (hand2[i].getSuit() != hand2[i + 1].getSuit())
				hasHand2 = false;
		}
		if (!hasHand1 && !hasHand2)
			return -1;
		else if (hasHand1 && !hasHand2)
			return 1;
		else if (!hasHand1 && hasHand2)
			return 2;
		else
			return -1;
	}

	public int straight() {
		hasHand1 = true;
		hasHand2 = true;
		if (debug)
			System.out.println("straight()");
		//checks to see if the sorted cards in hand are sequential
		for (int i = 0; i < handSize - 1; i++) {
			if (hand1[i].getFace() != hand1[i + 1].getFace() - 1) {
				hasHand1 = false;
			}
			if (hand2[i].getFace() != hand2[i + 1].getFace() - 1)
				hasHand2 = false;
		}
		if (hasHand1 && hasHand2){
			setHandVals("straight");
			//sets both hands to straight and breaks by doing highcard
			return highCard();
		}
		else if (hasHand1 && !hasHand2)
			return 1;
		else if (!hasHand1 && hasHand2)
			return 2;
		return -1;

	}

	public int threeOak() {
		hasHand1 = false;
		hasHand2 = false;
		if (debug)
			System.out.println("threeOak()");
		//goes through each element of the face bucket to see if there's a 3 of a kind
		for (int i = numFaces - 1; i >= 0; i--) {
			if (faceBuck1[i] == 3) {
				hasHand1 = true;
			}
			if (faceBuck2[i] == 3) {
				hasHand2 = true;
			}
		}
			//sets both hands to threeoak and returns the high card if there's a tiebreaker
			if (hasHand1 && hasHand2){
				setHandVals("three of a kind");				
				return onePair();
			}
			else if (hasHand1 && !hasHand2)
				return 1;
			else if (!hasHand1 && hasHand2)
				return 2;
		return -1;
	}

	public int twoPair() {
		hasHand1 = false;
		hasHand2 = false;
		if (debug)
			System.out.println("twoPair()");
		int ctr1 = 0, ctr2 = 0;
		//searches both face buckets to see if there's two different pairs
		for (int i = numFaces - 1; i >= 0; i--) {
			if (faceBuck1[i] == 2)
				ctr1++;
			if (faceBuck2[i] == 2)
				ctr2++;
		}
		if (ctr1 != 2 && ctr2 != 2)
			return -1;
		//sets hasHandX to true if there's two pairs (ctr == 2)
		for (int i = numFaces - 1; i >= 0; i--) {
			if (faceBuck1[i] == 2 && faceBuck2[i] == 2)
				continue;
			if (ctr1 == 2) {
				hasHand1 = true;
			}
			if (ctr2 == 2) {
				hasHand2 = true;
			}
		}
		//return logic
		if (hasHand1 && hasHand2){
			return highCard();
		}
		else if (hasHand1 && !hasHand2)
			return 1;
		else if (!hasHand1 && hasHand2)
			return 2;
		else
			return -1;
	}

	public int onePair() {//functions like twopair() ex
		hasHand1 = false;
		hasHand2 = false;
		if (debug)
			System.out.println("OnePair()");
		int ctr1 = 0, ctr2 = 0;
		//sets hasHandX to true if there's one pair (ctr == 1)
		for (int i = numFaces - 1; i >= 0; i--) {
			if (faceBuck1[i] == 2)
				ctr1++;
			if (faceBuck2[i] == 2)
				ctr2++;
		}
		if (ctr1 == 1) {
			hasHand1 = true;
		}
		if (ctr2 == 1) {
			hasHand2 = true;
		}
		//return logic
		if (hasHand1 && !hasHand2)
			return 1;
		else if (!hasHand1 && hasHand2)
			return 2;
		else
			return -1;
	}

	public int highCard() {
		hasHand1 = false;
		hasHand2 = false;
		if (debug)
			System.out.println("highCard()");
		//runs until a difference in the hand is found and sets the hand with
		//the higher card to true
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
		//swaps cards unil they're in order
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
		//returns the number of cards in hand with the specified suit
		for (int i = 0; i < hand.length; i++) {
			if (hand[i].getSuit() == suit)
				ctr++;
		}
		return ctr;
	}

	public int numOfFace(Card[] hand, int face) {
		int ctr = 0;
		//returns the number of cards in hand with the specified face
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

	public void setHandVals(String rank) {
		if (hasHand1)
			handVal1 = rank;
		if (hasHand2)
			handVal2 = rank;
	}
}