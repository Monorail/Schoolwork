
public class Card {
	private int face, suit;
	private String[] faces = {"Ace", "Deuce", "Three", "Four", "Five", "Six",
			"Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
	private String[] suits = {"Hearts", "Diamonds", "Clubs", "Spades"};
	public Card(int face, int suit){
		this.face = face;
		this.suit = suit;
	}
	
	public String toString(){
		//tostring passes the face and suit numbers through the arrays and returns it
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
