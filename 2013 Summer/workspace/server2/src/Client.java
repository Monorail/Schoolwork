//must start server before client
//upon further thought I realize that this is quite obvious

import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

class Client {
   public static void main(String args[]) throws IOException {
	   String pooass = "SQUODS";
      try {
         Socket skt = new Socket("192.168.62.51", 2000);
         BufferedReader in = new BufferedReader(new
            InputStreamReader(skt.getInputStream()));
         System.out.print("Received string: '");

         while (!in.ready()) {}
         System.out.println(pooass = in.readLine()); // Read one line and output it

         System.out.print("'\n");
         in.close();
      }
      catch(Exception e) {
         System.out.print("Whoops! It didn't work!\n");
      }
      if (pooass.equals("SQUIDS")){
  		PrintWriter out = new PrintWriter(new FileWriter("C:\\theserverstuffworkedyayaya.txt")); 
  		out.print("Hello "); 
  		out.println("world"); 
  		out.close();
      }
   }
}
