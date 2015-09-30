/* Alex Berliner
 * a2737438
 * 7/28/13
 * COP 3330
 * Comets
 * A simple comets game
 */
package comets;

public abstract class SpaceObject {
	static double playfieldHeight, playfieldWidth;
	protected double xVelocity, yVelocity,xPos,yPos,radius;

	SpaceObject(double xPos, double yPos, double xVel, double yVel, double radius) {
		xVelocity = xVel;
		yVelocity = yVel;
		this.xPos=xPos;
		this.yPos=yPos;
		this.radius=radius;
	}
	double getRadius(){
		//return the radius of an object
		return radius;
	}
	double getXPosition(){
		//return the x position of an object
		return xPos;
	}
	double getYPosition(){
		//return the y position of an object
		return yPos;
	}
	void move(){
		//calculates the total speed of the ship, and sets it to s
		double s = Math.sqrt(Math.pow(xVelocity,2)+Math.pow(yVelocity,2)); 
		//reduce the speed of the ship if s is greater than 10 pixels per frame
		if(s>10){
			xVelocity*=10/s;
			yVelocity*=10/s;
		}

		//this code makes the objects on the screen wrap around if they go off the game area
		if(xPos>500)xPos-=500;
		if(xPos<0)xPos+=500;
		if(yPos>500)yPos-=500;;
		if(yPos<0)yPos+=500;
		xPos+=xVelocity*1;
		yPos+=yVelocity*1;
	}
	boolean overlapping(SpaceObject rhs){
		//determines if two objects are touching by comparing the combined radius of the two objects to the space between them
		double distance = Math.sqrt(Math.pow(xPos-rhs.xPos, 2)+Math.pow(yPos-rhs.yPos, 2)),comRad = rhs.radius+radius;
		if(distance<comRad){
			return true;
		}
		return false;
	}
}
















