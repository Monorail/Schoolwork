public class ICalculator3 extends ICalculator { 
	public int div(int x) {
		if (x!=0)
			return super.div(x); 
		System.out.println("ZERO DIVIDE ATTEMPTED"); 
		return getCurrentValue();
	}
}