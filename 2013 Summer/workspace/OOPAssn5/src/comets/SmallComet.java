/* Alex Berliner
 * a2737438
 * 7/28/13
 * COP 3330
 * Comets
 * A simple comets game
 */
package comets;

import java.util.Vector;

public class SmallComet extends Comet{

	SmallComet(double xPos, double yPos, double xVel, double yVel) {
		super(xPos, yPos, xVel, yVel, 20);
		// TODO Auto-generated constructor stub
	}
	public java.util.Vector<Comet> explode(){
		
		return new Vector<Comet>();
	}
}
