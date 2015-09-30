import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class HillCipher{
	public static
			String file = "plaintext.txt",
			key = "e-key.txt",
			temp = "",
			line = "",
			outputfile = "enc text.txt";
	public static int counter = 0, x = 0;
	static int keySize=0;
	public int counter1;
	public static int[][] keyMatrix;
	public static void readText() throws FileNotFoundException {

		Scanner inputScan = new Scanner(System.in);
		
		System.out.println("What is the name of your file to be encrypted?");
		file=inputScan.nextLine();
		System.out.println("You entered "+file+" as your input file name\n");
		
		System.out.println("What is the name of encryption key file?");
		key=inputScan.nextLine();
		System.out.println("You entered "+key+" as your encryption key file name\n");
		
		System.out.println("What is the name of your output file?");
		outputfile=inputScan.nextLine();
		System.out.println("You entered "+file+" as your output file name\n");
		
		
		File inputfile = new File(file);
		inputScan = new Scanner(new File(file));
		inputScan.useDelimiter("");
		while (inputScan.hasNext()) {
			temp = inputScan.next().toLowerCase();
			if ((temp.charAt(0) - 'a') >= 0 && (temp.charAt(0) - 'a') < 26) {
				line = line + temp;

			}
		}
		
		
		inputScan.close();
	}

	public static String encryptCharacters(int[][] matrix, String input){
		int[] outputInts = new int[keySize];
		for(int i =0;i<keySize;i++){
			for(int j = 0;j<keySize;j++){
				outputInts[i] +=(matrix[i][j] * (input.charAt(j)-'a'));
			}
			outputInts[i] = outputInts[i]%26;
			//System.out.println(outputInts[i]);
		}
		String output = "";
		for (int i = 0;i<keySize;i++){
			output  += (char)(outputInts[i]+'a');
		}
		return output;
	}
	public static void printOutput(String output, int[][] keyMatrix) throws IOException{
		File outputs=new File(outputfile);
		PrintWriter out = new PrintWriter(new FileWriter(outputs)); 
		encryptCharacters(keyMatrix, output);
		out.print(output);
//		int ctr = 0;
//		for(int i=0; i<output.length(); i++){
//			out.print(output.charAt(i));
//			if(ctr%80==79){
//				out.println();
//			}
//			ctr++;
//			
//		}
		
		out.close();
	}
	public static void readKey(String path) throws FileNotFoundException{
		Scanner scanner = new Scanner(new File(path));
		keySize = scanner.nextInt();
		keyMatrix = new int[keySize][keySize];
		for(int i = 0; i < keySize;i++)
			for(int j = 0; j < keySize;j++)
				keyMatrix[i][j] = scanner.nextInt();
	}
	public static void main(String args[]) throws IOException, FileNotFoundException{
		keyMatrix = new int[keySize][keySize];
		readText();
		readKey(key);
		int numXs = keySize - line.length()%keySize;
		for(int i = 0; i < numXs; i++){
			line +="x";
		}
		String encryptedText = "";
		//System.out.println(line);
		int numblocks = line.length()/keySize;
		//System.out.println(numblocks);
		for(int i = 0;i<numblocks;i++){
			//encryptedText+=
			encryptedText += encryptCharacters(keyMatrix, line.substring(i*keySize, i*keySize+keySize));
		}
		PrintWriter printer = new PrintWriter(new File(outputfile));
		for(int i = 1;i < encryptedText.length()+1;i++){
			printer.print(encryptedText.charAt(i-1));
			if(i%80 == 0){
				printer.print("\n");
			}
		}
		printer.flush();
		printer.close();
		// System.out.print(line);

	}

}
