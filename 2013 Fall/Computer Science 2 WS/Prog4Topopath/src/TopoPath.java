import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class TopoPath {
	static int numElems = 10;
	ArrayList<Node> topArray = new ArrayList<Node>();
	static int numParents[];// the number of parents that each member of the
							// adjacency list has. 0 means that it can be
							// removed and -1 means that it has been removed
	// takes an adjacency list and removes elements while there is exactly one
	// node with 0 parents. If every element is able to be removed then it's a
	// TopoPath.
	public static boolean hasTopoPath(String filename)
			throws FileNotFoundException {
		
		TopoPath path = new TopoPath(filename);
		int breakCond = 0;
		int runtime1 = 0;
		int runtime2 = 0;
		while (breakCond != numElems) {
			breakCond = 0;
			int numZs = 0;
			int entryPt = -1;
			for (int i = 0; i < numElems; i++) {
				runtime1++;
				if (numParents[i] == 0) {
					numZs++;
					entryPt = i;
					numParents[i] = -1;
				}
				if (numZs > 1) {
					System.out.println("Runtime: " + runtime1 + ". n: " + numElems);
					return false;
				}
				if (numParents[i] == -1)
					breakCond++;
			}
			if (numZs == 0) {
				System.out.println("Runtime: " + runtime1 + ". n: " + numElems);
				return false;
			}
			Node entry = path.topArray.get(entryPt);
			while (entry != null) {
				runtime1++;
				numParents[entry.pos - 1]--;
				entry = entry.next;
			}
		}
		System.out.println("Runtime: " + runtime1 + ". n: " + numElems);
		return true;
	}
	
	// performs a head insert for the element at pos with the contents data.
	// also updates the numParents
	public void insert(int pos, int data) {
		if (pos > numElems) {
			System.err.println("Index element " + pos + " out of bound "
					+ numElems + "!");
			System.exit(0);
		}
		numParents[data - 1]++;
		Node temp = new Node(data);
		if (topArray.get(pos) == null) {
			topArray.set(pos, temp);
		} else {
			temp.next = topArray.get(pos);
			topArray.set(pos, temp);
		}

	}

	public String toString() {
		String out = "";
		for (int i = 0; i < numElems - 1; i++) {
			out += i + 1 + ": " + topArray.get(i) + "(" + numParents[i] + ")"
					+ "\n";
		}
		out += numElems + ": " + topArray.get(numElems - 1) + " ("
				+ numParents[numElems - 1] + ")" + "\n";
		return out;
	}

	// takes in the location of a file and constructs the adjacency list stored
	// in it.
	public TopoPath(String filename) throws FileNotFoundException {
		Scanner sc = new Scanner(new File(filename));
		numElems = sc.nextInt();
		numParents = new int[numElems];
		for (int i = 0; i < numElems; i++) {
			numParents[i] = 0;
		}
		for (int i = 0; i < numElems; i++) {
			topArray.add(null);
		}
		for (int i = 0; i < numElems; i++) {
			int numChildren = sc.nextInt();
			for (int j = 0; j < numChildren; j++) {
				int temp = sc.nextInt();
				insert(i, temp);
			}
		}
		sc.close();
	}

	// public static void main(String[] args) throws FileNotFoundException {
	// hasTopoPath("g3.txt");
	// }
	public static double difficultyRating(){
		return 3.6;
	}
	public static double hoursSpent(){
		return 6;
	}
}

class Node {
	Node next;
	public int pos;
	public int numParents;

	public Node(int pos) {
		this.pos = pos;
		this.next = null;
	}

	public String toString() {
		String out = "";
		Node temp = this;
		while (temp != null) {
			out += temp.pos + ", ";
			temp = temp.next;
		}
		return out;
	}
}
