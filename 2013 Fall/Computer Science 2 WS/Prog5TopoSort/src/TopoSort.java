import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class TopoSort {
	static int numElems = 10;
	ArrayList<Node> topArray = new ArrayList<Node>();//the adjacency list
	
	static int numParents[];// the number of parents that each member of the
							// adjacency list has. 0 means that it can be
							// removed and -1 means that it has been removed

	// a recursive function to determine whether an adjacency list can be sorted
	// topologically
	public int runtime = 0;
	public boolean hasTopoSort(int x, int y) {
		runtime++;
		System.out.println(this);
		// base case: the element x doesn't exist and y does
		if (numParents[x - 1] == -1 && numParents[y - 1] != -1) {
			return true;
		}
		if(numParents[x - 1] != -1 && numParents[y - 1] == -1){
			return false;
		}
		// find all elements equal to 0 in numParents, remove them from the
		// adjacency list and perform the sort again until it completes or finds
		// a valid case
		for (int i = 0; i < numElems; i++) {
			if (numParents[i] == 0) {
				removeEntry(i);
				if (hasTopoSort(x, y)) {
					replaceEntry(i);
					return true;
				}
				replaceEntry(i);
			}
		}
		return false;
	}

	// removes a node from an adjacency list by decrementing the node at pos and
	// then every node connected to pos
	public void removeEntry(int pos) {
		numParents[pos]--;
		Node entry = topArray.get(pos);
		while (entry != null) {
			numParents[entry.pos - 1]--;
			entry = entry.next;
		}
	}

	// adds a node back to an adjacency list by incrementing the node at pos and
	// then every node connected to pos. this is used when resetting a list to
	// be used in a different configuration of the sort
	public void replaceEntry(int pos) {
		numParents[pos]++;
		Node entry = topArray.get(pos);
		while (entry != null) {
			numParents[entry.pos - 1]++;
			entry = entry.next;
		}
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
	public TopoSort(String filename) throws FileNotFoundException {
		Scanner sc = new Scanner(new File(filename));
		numElems = sc.nextInt();
		numParents = new int[numElems];
		for (int i = 0; i < numElems; i++) {
			numParents[i] = 0;
		}
		// adds the proper number of adjacency list elements and sets them to
		// null to indicate no links
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
		return 3;
	}
	public static double hoursSpent(){
		return 1.5;
	}
}

class Node {
	Node next;
	public int pos;

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
