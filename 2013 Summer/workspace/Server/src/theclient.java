import java.io.*;
import java.util.*;
import java.net.Socket;


public class theclient {
	public static void main(String[] args) {
		
	    Socket MyClient = null;
	    try {
	           MyClient = new Socket("Alex-Acer-PC", 2000);
	    }
	    catch (IOException e) {
	        System.out.println(e);
	    }
	    
	    DataInputStream input = null;
	    try {
	       input = new DataInputStream(MyClient.getInputStream());
	    }
	    catch (IOException e) {
	       System.out.println(e);
	    }
	    
	    PrintStream output = null;
	    try {
	       output = new PrintStream(MyClient.getOutputStream());
	    }
	    catch (IOException e) {
	       System.out.println(e);
	    }
	    try {
	           output.close();
	           input.close();
	       MyClient.close();
	    } 
	    catch (IOException e) {
	       System.out.println(e);
	    }
	    
	}

}
