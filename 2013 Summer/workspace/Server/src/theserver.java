import java.io.DataInputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;


public class theserver {
	public static void main(String[] args) {
	    ServerSocket MyService = null;
	    try {
	       MyService = new ServerSocket(2000);
	        }
	        catch (IOException e) {
	           System.out.println(e);
	        }
	    Socket serviceSocket = null;
	    try {
	       serviceSocket = MyService.accept();
	        }
	    catch (IOException e) {
	       System.out.println(e);
	    }
	    DataInputStream input = null;
	    try {
	       input = new DataInputStream(serviceSocket.getInputStream());
	    }
	    catch (IOException e) {
	       System.out.println(e);
	    }
	    
	    PrintStream output = null;
	    try {
	       output = new PrintStream(serviceSocket.getOutputStream());
	    }
	    catch (IOException e) {
	       System.out.println(e);
	    }
	    
	    try {
	        output.close();
	        input.close();
	        serviceSocket.close();
	        MyService.close();
	     } 
	     catch (IOException e) {
	        System.out.println(e);
	     }
	}

}
