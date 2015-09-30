import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;


public class fauxpas {
	public static void main(String args[]) throws IOException{
		
		PrintWriter out = new PrintWriter(new FileWriter("C:\\outputfile.txt")); 
		out.print("Hello "); 
		out.println("world"); 
		out.close();
	}
	
	
}
