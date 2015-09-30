import java.util.Random;


public class Deck {
	private final int numCards = 52;
	private int cardsDealt = 0;
	private Card[] deck = new Card[numCards];
	private int[] faces = {0,1,2,3,4,5,6,7,8,9,10,11,12};
	private int[] suits = {0,1,2,3};
	public Deck(){
		//initializing decks
		for(int i = 0; i< numCards;i++){
			deck[i] = new Card(i%13,i/13);
		}
		shuffle();
	}
	public void shuffle(){
		Random rand = new Random();
		int swapNum = 0;
		//swaps each card with a random card to completely randomize
		for(int i = 0;i<numCards;i++){
			Card temp = deck[i];
			deck[i]= deck[swapNum = rand.nextInt(52)];
			deck[swapNum]= temp;
		}
	}
	public void printDeck(){
		for(int i = 0; i<numCards;i++)
			System.out.println(i+1 + ": " + deck[i]);
	}
	public Card deal(){
		return deck[cardsDealt++];
	}

}
