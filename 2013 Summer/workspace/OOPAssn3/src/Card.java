
public class Card {
	int face, suit;
	String[] faces = {"Ace", "Deuce", "Three", "Four", "Five", "Six",
			"Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
	String[] suits = {"Hearts", "Diamonds", "Clubs", "Spades"};
	public Card(int face, int suit){
		this.face = face;
		this.suit = suit;
	}
	
	public String toString(){
		//to string just passes the suit and face through the string arrays
		return faces[face] + " of " + suits[suit];
	}
	
	public int getFace(){
		return face;
	}

	public int getSuit(){
		return suit;
	}
	public void setFace(int val){
		this.face= val;
	}
	public void setSuit(int val){
		this.suit = val;
	}

}
