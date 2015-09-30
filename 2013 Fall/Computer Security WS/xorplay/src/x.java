
public class x {
	static String poly = "111111011";
	static int polyLen = poly.length();
	
	public static void main(String[] args){
		String input = "111100110";
		int numZeros = 0;
		while(input.charAt(numZeros) == '0'){
			numZeros++;
		}
		if(!(numZeros + poly.length() > input.length())){
			System.out.println("Before: " + input);
			System.out.println("XOR   : " +poly);
			input = XOR(poly, input);
			System.out.println("After : " + input);
		}
	}
	
	public static String XOR(String poly, String input) {
		// simple XOR function
		char[] toDivide = input.toCharArray();
		int numZeros = 0;
		while(input.charAt(numZeros) == '0'){
			numZeros++;
		}
		//System.out.println("Starting at " + numZeros); 
		for (int i = numZeros,j = 0; i < numZeros + polyLen; i++,j++) {
			if (poly.charAt(j) == input.charAt(i))
				toDivide[i] = '0';
			else
				toDivide[i] = '1';
		}
		return new String(toDivide);
	}
}
