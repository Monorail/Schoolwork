/* Alex Berliner
 * a2737438
 * 7/28/13
 * COP 3330
 * Comets
 * A simple comets game
 */
package comets;

public class Shot extends SpaceObject{
	protected int age=0;
	Shot(double xPos, double yPos, double xVel, double yVel) {
		super(xPos, yPos, xVel, yVel, 3);
	}
	public int getAge(){
		//returns the age of the bullet
		return age;
	}

	void move(){
		//wrap around code
		if(xPos>500)xPos-=500;
		if(xPos<0)xPos+=500;
		if(yPos>500)yPos-=500;;
		if(yPos<0)yPos+=500;
		xPos+=xVelocity*1;
		yPos+=yVelocity*1;
		//increments the age of the shot
		age++;
	}
	
}
