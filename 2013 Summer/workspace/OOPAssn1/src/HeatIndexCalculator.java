/* Name: Alex Berliner
COP 3330 Spring 2013 
Assignment title: Program 1: Creating A Java Application From A UML Diagram 
Date: Wednesday January 30, 2013 */

public class HeatIndexCalculator {
	public int temperature;
	public double humidity;
	public double heatIndex;
	
	public double calculateHeatIndex(int currentTemp, double currentHumidity){
		double c1 = -42.379, c2 = 2.04901523,//declaring all the constants
		c3 = 10.14333127, c4 = -0.22475541,
		c5 = -6.83783*Math.pow(10,-3), c6 = -5.481717*Math.pow(10,-2),
		c7 = 1.22874*Math.pow(10,-3), c8 = 8.5282*Math.pow(10,-4), c9 = -1.99*Math.pow(10,-6);
		

		return c1 + c2 * currentTemp + c3 * currentHumidity +//calculating and returning the heat index
			c4 * currentTemp * currentHumidity + c5 * currentTemp * currentTemp +
			c6 * currentHumidity * currentHumidity + c7 * currentTemp * currentTemp * currentHumidity +
			c8 * currentTemp * currentHumidity * currentHumidity + c9 * currentTemp * currentTemp * currentHumidity * currentHumidity;
	}
	public void printHeatIndex(int currentTemp, double currentHumidity, double calculatedHeatIndex){
		System.out.print("At a temperature of " + currentTemp + "F and a humidity of ");//printing the output
		System.out.printf("%.2f . . .\nIt actually feels like: %.2fF\n", currentHumidity, calculatedHeatIndex);
	}
}
