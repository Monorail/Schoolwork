import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Isogram {
	public static void main(String args[]) throws FileNotFoundException {
		Scanner sc = new Scanner(new File("input.txt"));
		System.out.println();
		int numWords = sc.nextInt();
		for(int i = 0; i < numWords; i++){
			String word = sc.next();
			char[] wordarr = word.toCharArray();
			int[] bucket = new int[26];
			boolean invalid = false;
			for(int j = 0; j < wordarr.length; j++){
				bucket[(int)wordarr[j] - 'a']++;
			}
			for(int j = 0; j < 26; j++){
				if(bucket[j] == 0 || bucket[j] == 2) {
					continue;
				}
				invalid = true;
				break;
			}
			System.out.println(word + " is " + ((invalid)? "not ": "") + "a pair isogram");
		}
		sc.close();
		System.out.println();
	}
}
