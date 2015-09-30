//Alex Berliner
//a2737438
import java.io.*;
import java.util.*;

public class HillCipher {
	static String body;
	static String keyInput;	
	static int blockSize;
	static boolean mainDebug = false;
	static boolean periodDebug = false;
	static boolean encryptDebug = false;
	static boolean verboseOut = false;
	

	public static void main(String[] args) throws FileNotFoundException {
		//data collection from user
		Scanner sc = new Scanner(System.in);
		System.out.println("Please enter the name of the file storing the key.");
		String keyInput = sc.next();
		System.out.println("Please enter the name of the file to encrypt.");
		String body = sc.next();
		System.out.println("Please enter the name of the file to store the ciphertext.");
		String outFile = sc.next();
		
		sc = new Scanner(new File(keyInput));
		PrintWriter os = new PrintWriter(outFile);
		
		blockSize = sc.nextInt();
		
		int[][] key = makeMatrix(sc);
		
		sc = new Scanner(new File(body));
		//using delimiter of "" so that there is finer control over the iteration 
		sc.useDelimiter("");
		
		int numCharsStored = 0;
		String strAccu = "";
		while (sc.hasNext()) {
			String in[] = getNextBlock(sc);
			in = encrypt(in,key);
			if (mainDebug)System.out.println(catBlock(in));
			numCharsStored += blockSize;
			// if(mainDebug)System.out.println(numCharsStored);
			//a block must be printed out when there's at least 80 characters stored
			if (numCharsStored >= 80) {
				int overflow = numCharsStored - 80;
				// if(mainDebug)System.out.println("numCharsStored >= 80. Overflow: "  + overflow);
				//first a check must be made to see if there was overflow over 80 when accumulating the encrypted text
				strAccu += catBlock(in, 0, blockSize - overflow);// to be printed
				if(verboseOut)System.out.println(strAccu);
				os.println(strAccu);
				strAccu = catBlock(in, blockSize - overflow, blockSize);// to be  saved
				numCharsStored = overflow;
				continue;
			}
			strAccu += catBlock(in);
		}
		//the final print if there's left-over encrypted data that doesn't reach to 80 characters
		if (strAccu.length() != 0) {
			if(verboseOut)System.out.println(strAccu);
			os.println(strAccu);
		}
		sc.close();
		os.flush();
		os.close();
	}
	// this will encrypt a string with a matrix on the condition that 
	// the matrix's length and width and the string's length are the same 
	public static String[] encrypt(String[] in, int[][] key) {
		if(encryptDebug)System.out.println(catBlock(in));
		// get the length of the string, which is also the matrix dimensions
		int matLen = in.length;
		int[] out = new int[matLen];
		//perform the matrix multiplication
		for (int i = 0; i < matLen; i++) {
			for (int j = 0; j < matLen; j++) {
				out[i] += ((in[j].charAt(0)) - 'a') * key[i][j];
				//if(encryptDebug)System.out.println(out[i]);
				out[i] = out[i]%26;
				}
			//if(encryptDebug)System.out.println(out[i]);
		}
		//turn the integer string into a character string
		String[] strOut = new String[matLen];
		for(int i = 0;i<matLen;i++){
			strOut[i] = (char)('a' + out[i]) + "";
		}
		return strOut;
	}
	// concatenates a string array's elements together, from index pos to numElem
	// usually for printing 
	public static String catBlock(String[] arr, int pos, int numElem) {
		String cat = "";
		for (int i = pos; i < numElem; i++)
			cat += arr[i];
		return cat;
	}
	//concatenates a string array's elements together, usually for printing
	public static String catBlock(String[] arr) {
		String cat = "";
		for (String str : arr) {
			cat += str;
		}
		return cat;
	}
	
	//creates the matrix to be used for encryption out of the key file
	//the scanner sc assumes that it is being pointed at the key file
	public static int[][] makeMatrix(Scanner sc) {
		int[][] matrix = new int[blockSize][blockSize];
		for (int i = 0; i < blockSize; i++) {
			for (int j = 0; j < blockSize; j++) {
				matrix[i][j] = sc.nextInt();
			}
		}
		return matrix;
	}
	//parses and sanitizes the next three incoming characters in the body
	//assumes that the sc refers to the body of text
	public static String[] getNextBlock(Scanner sc) {
		String in[] = new String[blockSize];
		int i = 0;
		while (sc.hasNext() && i < blockSize) {
			in[i] = sc.next().toLowerCase();
			if (!in[i].matches("[a-z]")) 
				continue;
			i++;
		}
		for (i = 0; i < blockSize; i++) {
			if (in[i] == null || !in[i].matches("[a-z]"))
				in[i] = "x";
		}
		return in;
	}

}