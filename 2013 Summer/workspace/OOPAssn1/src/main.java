/* Name: Alex Berliner
COP 3330 Spring 2013 
Assignment title: Program 1: Creating A Java Application From A UML Diagram 
Date: Wednesday January 30, 2013 */
import java.io.File;
import java.util.*;
public class main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		HeatIndexCalculator HIC =  new HeatIndexCalculator();

		System.out.println("Please enter the current temperature in degree Fahrenheit: ");// asking for and getting temperature
		HIC.temperature = sc.nextInt();
		System.out.println("Please enter the current humidity as a percentage: ");//asking for and getting humidity
		HIC.humidity = sc.nextDouble();
		HIC.heatIndex = HIC.calculateHeatIndex(HIC.temperature, HIC.humidity);//calculating heat index and setting the class variable equal to it 
		HIC.printHeatIndex(HIC.temperature, HIC.humidity, HIC.heatIndex);//telling HIC to print the heat index
		File myFile;
	}
}
public class Accumulator {

	int sum;
	public Accumulator(int crantastic){
		sum = crantastic;
	}
	public int getSum(){
		return sum;
	}
	public void add(int crantastic){
		sum += crantastic;
	}
	
}
public Class Counter{

	private int counter;
	public Counter(int crantastic){
		this.counter = crantastic;
	public void increment(){
		counter++;
	}
	public decrement(){
		decrement--;
	}
	public int getValue(){
		
		return counter;
	}
}













