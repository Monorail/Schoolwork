/* Alex Berliner
 * a2737438
 * 7/28/13
 * COP 3330
 * Comets
 * A simple comets game
 */
package comets;

import java.util.Random;
import java.util.Vector;

public class MediumComet extends Comet{

	MediumComet(double xPos, double yPos, double xVel, double yVel) {
		super(xPos, yPos, xVel, yVel, 30);
		// TODO Auto-generated constructor stub
	}
	public java.util.Vector<Comet> explode(){
		Vector<Comet> comets = new Vector<Comet>();
		Random r = new Random();
		comets.add(new SmallComet(xPos,yPos,r.nextInt()%3,r.nextInt()%3));
		comets.add(new SmallComet(xPos,yPos,r.nextInt()%3,r.nextInt()%3));
		comets.add(new SmallComet(xPos,yPos,r.nextInt()%3,r.nextInt()%3));
		comets.add(new SmallComet(xPos,yPos,r.nextInt()%3,r.nextInt()%3));
		return comets;
		
	}
}
