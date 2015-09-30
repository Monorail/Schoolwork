// Alex Berliner a2737438
// COP 3503, Fall 2013

// Treap.java
// ========
// Treap implementation that supports insert() and
// delete() operations and can be used with any type.
// The original BST framework code was created by Sean Szumlanski 

import java.io.*;
import java.util.*;
import java.math.*;

import org.omg.CORBA.Any;

class Node<AnyType extends Comparable<AnyType>> {
	AnyType data;
	Node<AnyType> left, right;// Left and right child nodes of any type
	int priority;

	Node(AnyType data, int priority) {
		this.data = data;// sets the class data equal to the incoming data
		this.priority = priority;
	}
}

public class Treap<AnyType extends Comparable<AnyType>> {

	private Node<AnyType> root;
	HashMap<AnyType, Integer> prioritySet;
	Random r;
	Node<AnyType> found;

	// initializations
	public Treap() {
		r = new Random();
		prioritySet = new HashMap<AnyType, Integer>();
	}

	// performs a right node rotation and returns the new head
	private Node<AnyType> rightRotate(Node<AnyType> root) {
		// //System.out.println("Rotate right");
		Node<AnyType> temp = root.left;
		root.left = temp.right;
		temp.right = root;
		return temp;
	}

	// performs a left node rotation and returns the new head
	private Node<AnyType> leftRotate(Node<AnyType> root) {
		Node<AnyType> temp = root.right;
		root.right = temp.left;
		temp.left = root;
		return temp;
	}

	// makes deletion simpler for the user. takes the global root node and sets
	// it equal to the real delete function
	public void remove(AnyType data) {
		prioritySet.remove(data);
		root = remove(root, data);
	}

	// removes data heap style. recurs until it finds the data element to be
	// removed and then does a series of rotations to make it a leaf node, then
	// sets the node to null
	private Node<AnyType> remove(Node<AnyType> root, AnyType data) {
		if (root == null) {
			return null;
			// finding the right data node
		} else if (data.compareTo(root.data) != 0) {
			root.left = remove(root.left, data);
			root.right = remove(root.right, data);
		} else {

			if (root.left == null && root.right == null) {
				return null;
			} else if (root.right == null) {
				root = rightRotate(root);
				root = remove(root, data);
			} else if (root.left == null) {
				root = leftRotate(root);
				root = remove(root, data);
			} else {
				if (root.left.priority > root.right.priority)
					root = leftRotate(root);
				else
					root = rightRotate(root);
				root = remove(root, data);

			}

		}
		return root;
	}

	// inserts a data element bst style. runs down the tree and compares data
	// values until it finds an empty spot to place the data
	private Node<AnyType> insert(Node<AnyType> root, AnyType data, int priority) {
		if (root == null) {
			return new Node<AnyType>(data, priority);
		} else if (data.compareTo(root.data) < 0) {
			root.left = insert(root.left, data, priority);
			if (root.left.priority < root.priority) {
				return rightRotate(root);
			}
		} else if (root.data.compareTo(data) < 0) {
			root.right = insert(root.right, data, priority);
			if (root.right.priority < root.priority) {
				return leftRotate(root);
			}
		}
		return root;
	}

	// inserts the data in the treap and sets the root equal to the new tree
	// location
	public void add(AnyType data, int priority) {
		prioritySet.put(data, priority);
		root = insert(root, data, priority);
	}

	// wrapper add function, generates priority data
	public void add(AnyType data) {
		int rVal;
		do {
			rVal = Math.abs(r.nextInt() % (Integer.MAX_VALUE - 1)) + 1;// 3000000);
		} while (prioritySet.containsValue(rVal));
		add(data, rVal);
	}
	// height wrapper
	public int height() {
		return height(root);
	}

	// a recursive function to determine treap height
	private int height(Node<AnyType> root) {
		if (root == null)
			return -1;
		return Math.max(height(root.left) + 1, height(root.right) + 1);
	}

	// returns the size of the treap based on the hash map
	public int size() {
		return prioritySet.size();
	}

	// Returns true if the value is contained in the treap, false otherwise.
	public boolean contains(AnyType data) {
		return contains(root, data);
	}

	// a recursive function to determine if an element is in a treap
	// by comparing the data element to the left and right node
	private boolean contains(Node<AnyType> root, AnyType data) {
		if (root == null) {
			return false;
		} else if (data.compareTo(root.data) < 0) {
			return contains(root.left, data);
		} else if (root.data.compareTo(data) < 0) {
			return contains(root.right, data);
		} else {
			return true;
		}
	}

	public static double hoursSpent() {
		return 6;
	}

	public static double difficultyRating() {
		return 2.7;
	}
}
