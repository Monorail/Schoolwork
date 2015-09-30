package comets;

public abstract class SpaceObject {
	static double playfieldHeight, playfieldWidth;
	protected double xVelocity, yVelocity;

	SpaceObject(double xPos, double yPos, double xVel, double yVel, double radius) {
		xVelocity = xVel;
		yVelocity = yVel;
		
	}
	double getRadius(){
		return 0;
	}
	double getXPosition(){
		return 0;
	}
	double getYPosition(){
		return 0;
	}
	void move(){
		
	}
	boolean overlapping(SpaceObject rhs){
		return false;
	}
}
