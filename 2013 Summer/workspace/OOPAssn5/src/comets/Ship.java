/* Alex Berliner
 * a2737438
 * 7/28/13
 * COP 3330
 * Comets
 * A simple comets game
 */
package comets;

public class Ship extends SpaceObject {
	double angle=0;
	public Ship(double xPos,double yPos,double xVel,double yVel){
		super(xPos, yPos, xVel, yVel, 10);
	}

	void accelerate() {
		//response code to the ship being told to accelerate
		//accelerates based on the angle of the ship
		xVelocity+=.1*Math.sin(getAngle());
		yVelocity+=.1*Math.cos(getAngle());
	}
	void decelerate() {
		//response code to the ship being told to decelerate
		//decelerates based on the angle of the ship
		xVelocity-=.1*Math.sin(getAngle());
		yVelocity-=.1*Math.cos(getAngle());
	}

	Shot fire() {
		//creates a new shot with speed based on the ship's speed and angle
		return new Shot(xPos,yPos,3*Math.sin(getAngle()),3*Math.cos(getAngle()));
	}

	double getAngle() {
		//returns the ship's angle in radians
		return angle;
	}

	void rotateLeft() {
		//response to the ship being told to turn leftward
		angle-=.1*Math.PI;
		//makes the ship's angle not exceed 2*pi radians
		if(angle<0)angle=2*Math.PI;
	}

	void rotateRight() {
		//response to the ship being told to turn rightward
		angle+=.1*Math.PI;
		//makes the ship's angle not exceed 2*pi radians
		if(angle>2*Math.PI)angle=0;		
	}
}
