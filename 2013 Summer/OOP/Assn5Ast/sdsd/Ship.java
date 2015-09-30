package comets;

public class Ship extends SpaceObject {
	
	public Ship(double xPos,double yPos,double xVel,double yVel){
		super(xPos, yPos, xVel, yVel, 10);
	}

	void accelerate() {
	}

	Shot fire() {
		return null;
	}

	double getAngle() {
		return 0;
	}

	void rotateLeft() {
	}

	void rotateRight() {
	}
}
