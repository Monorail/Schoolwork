import java.io.File;
import java.io.FileNotFoundException;
import java.io.InputStreamReader;
import java.util.Scanner;


public class crcfile {
	
	//Lookup table to convert from hex to binary
	public static String[] binaryLookup = {"0000","0001","0010","0011","0100","0101","0110",
											"0111","1000","1001","1010","1011","1100","1101","1110","1111"};
	public static String[] hexLookup = {"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};
	public static String poly = "111111011";//"10000100110001101";
	
	public static String file = "Input.txt";
	public static String CRCanswer = "";
	
	public static String readFile() throws FileNotFoundException{
		File inputfile = new File(file);
		Scanner scanin = new Scanner(inputfile);
		String Hex = scanin.next();
		scanin.close();
		return Hex;
	}
	
	public static String hexToBinary(String Hex){
		String bi = "";
		Scanner str = new Scanner(Hex);
		str.useDelimiter("");
		for(int i=0; i<Hex.length(); i++){
			String temp =binaryLookup[Integer.valueOf(str.next(), 16)];
			bi += temp;
		}
		str.close();
		return bi;
	}
	
	
	public static String binaryToHex(String bi){
		String Hex1 = "";
		Scanner str = new Scanner(bi);
		str.useDelimiter("");
		int counter=0;
		String temp="";
		for(int i=0; i<bi.length(); i++){
			
			temp=temp+str.next();
			counter++;
			
			if(counter==4){
				counter=0;
				temp = hexLookup[Integer.valueOf(temp, 2)];
				Hex1+=temp;
				temp = "";
			}
		}
		str.close();
		return Hex1;
	}
	
	//poly is divisor in XOR, bi is dividend
	public static String xOR(String bi, String poly){
		String temp = "";
		
		char[] tempa = bi.toCharArray();
		char[] tempb = poly.toCharArray();
		
		if(bi.length()==poly.length()){
			for(int i=0; i<poly.length(); i++){
				if(tempa[i]!=tempb[i]){
					temp += "1";
				}
				else if(tempa[i]==tempb[i]){
					temp += "0";
				}
			}
		}
		else if(bi.length()<poly.length()){
			for(int i=0; i<bi.length(); i++){
				if(tempa[i]!=tempb[i]){
					temp += "1";
				}
				else if(tempa[i]==tempb[i]){
					temp += "0";
				}
			}
		}
		return temp;		
	}
	
	public static void checkCRC16(String binInput, String poly){
		String zeros = "";			//number of zeros preceding XOR
		String XORresult = "";		//result of current XOR
		String last = "";			//bits left after XOR in binInput
		int bitcounter=0;
		int resetcount = 0;
		for(int i = 0; i<poly.length()-1; i++){
			binInput += "0";
		}
		last = binInput;
		while(binInput.charAt(zeros.length()) == '0'){
			zeros += "0";
		}
		
		xOR(binInput.substring(0, poly.length()), poly);
		
		int XORtarget;
		while(last.length()+XORresult.length() > poly.length()){
			
			XORtarget = zeros.length()+poly.length();
			XORresult = xOR(binInput.substring(zeros.length(), XORtarget), poly);
			last = binInput.substring(zeros.length()+XORresult.length());
			binInput = zeros + XORresult + last;
			
			CRCanswer = XORresult.substring(1);
			while(binInput.charAt(zeros.length()) == '0'){
				zeros += "0";
			}
			
			for(int i=0; i<binInput.length(); i++){
				if(bitcounter==4){
					System.out.print(" ");
					bitcounter=0;
					resetcount++;
					if(resetcount==binInput.length()/4){
						System.out.println("");
						resetcount=0;
					}
				}

				System.out.print(binInput.charAt(i));
				bitcounter++;
			}
			
		}
	}
	
	public static boolean verifyCRC16(String binInput, String poly){
		String zeros = "";			//number of zeros preceding XOR
		String XORresult = "";		//result of current XOR
		String last = "";			//bits left after XOR in binInput
		last = binInput;
		String allzero = "";
		int bitcounter= 0;
		int resetcount = 0;
		
		while(binInput.charAt(zeros.length()) == '0'){
			zeros += "0";
		}
		
		xOR(binInput.substring(0, poly.length()), poly);
		
		int XORtarget;
		while(last.length()+XORresult.length() > poly.length()){
			
			XORtarget = zeros.length()+poly.length();
			XORresult = xOR(binInput.substring(zeros.length(), XORtarget), poly);
			last = binInput.substring(zeros.length()+XORresult.length());
			binInput = zeros + XORresult + last;
			
			allzero = zeros+XORresult+last;
			
			if(zeros.length()==binInput.length()){
				return true;
			}
			while(zeros.length()!=binInput.length() && binInput.charAt(zeros.length()) == '0'){
				zeros += "0";
			}
			
			for(int i=0; i<binInput.length(); i++){
				if(bitcounter==4){
					System.out.print(" ");
					bitcounter=0;
					resetcount++;
					if(resetcount==binInput.length()/4){
						System.out.println("");
						resetcount=0;
					}
				}

				System.out.print(binInput.charAt(i));
				bitcounter++;
			}
			
		}
		for(int i=0; i<binInput.length(); i++){
			if(allzero.charAt(i)!='0'){
				System.out.print("\n\nDid the CRC check pass?: ");
				return false;
			}
		}
		
		System.out.print("\n\nDid the CRC check pass?: ");
		return true;
		
	}
	
	public static void main(String[] args) throws FileNotFoundException{
		file = args[1];
		if(args[0].charAt(0)!='c' && args[0].charAt(0)!='v'){
			System.err.println("Error: Invalid mode"+"\nPlease input\nc: for calculate CRC\nv: for verify CRC\nfile: Input.txt\nverify file: VerifyInput.txt");
			System.exit(0);
		}
		if(!new File(file).exists()){
			System.err.println("Error: File not found"+"\nPlease input\nc: for calculate CRC\nv: for verify CRC\ncalculate file: Input.txt\nverify file: VerifyInput.txt");
			System.exit(0);
		}
		String Hex = readFile();
		System.out.println("Input file in binary: "+hexToBinary(Hex));
		System.out.println();
		String bi = hexToBinary(Hex);
		System.out.println("Input file in hex: "+binaryToHex(bi)+"\n");
		
		
		
		if(args[0].charAt(0)=='c'){
			System.out.println("This is the CRC including the XOR for every step:\n");
			checkCRC16(bi, poly);
			System.out.println();
			System.out.println("\nThis is the CRC code for the file in binary:"+CRCanswer);
			String CRChex = binaryToHex(CRCanswer);
			System.out.println("In hex:"+CRChex);
		}
		
		String newbinInput = bi;
		
		if(args[0].charAt(0)=='v'){
			System.out.println("\nThis is the CRC code for the file in binary:"+CRCanswer);
			String CRChex = binaryToHex(CRCanswer);
			System.out.println("In hex:"+CRChex);
			System.out.println("\nVerify mode:\n");
			System.out.println(verifyCRC16(newbinInput, poly));
		}
		
		
		System.exit(0);

		
	}
}
