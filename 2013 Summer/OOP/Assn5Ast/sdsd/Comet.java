package comets;

public abstract class Comet extends SpaceObject{

	public Comet(double xPos, double yPos, double xVel, double yVel, double radius) {
		super(xPos, yPos, xVel, yVel, radius);
		// TODO Auto-generated constructor stub
	}
	
	public abstract java.util.Vector<Comet> explode();
}
