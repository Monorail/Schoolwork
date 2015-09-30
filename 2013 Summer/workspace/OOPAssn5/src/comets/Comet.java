/* Alex Berliner
 * a2737438
 * 7/28/13
 * COP 3330
 * Comets
 * A simple comets game
 */
package comets;

public abstract class Comet extends SpaceObject{

	public Comet(double xPos, double yPos, double xVel, double yVel, double radius) {
		super(xPos, yPos, xVel, yVel, radius);
		// TODO Auto-generated constructor stub
	}
	
	public abstract java.util.Vector<Comet> explode();
}
