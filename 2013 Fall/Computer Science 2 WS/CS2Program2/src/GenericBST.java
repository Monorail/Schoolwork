// Alex Berliner a2737438
// COP 3503, Fall 2013

// GenericBST.java
// ========
// Basic binary search tree (BST) implementation that supports insert() and
// delete() operations and can be used with any type.

import java.io.*;
import java.util.*;
import java.math.*;

class Node<AnyType extends Comparable<AnyType>> {
	AnyType data;
	Node<AnyType> left, right;// Left and right child nodes of any type

	Node(AnyType data) {
		this.data = data;// sets the class data equal to the incoming data
	}
}

public class GenericBST<AnyType extends Comparable<AnyType>> {

	private Node<AnyType> root;
	public void insert(AnyType data) {
		root = insert(root, data);// inserts the data in the bst and sets the root equal to the new tree location
	}

	// inserts a data element into the root node
	// this function is recursive so that when a root has two children it recurs until it find a leaf node
	private Node<AnyType> insert(Node<AnyType> root, AnyType data) {
		if (root == null) {
			return new Node<AnyType>(data);
		} else if (data.compareTo(root.data) < 0) {
			root.left = insert(root.left, data);//  
		} else if (root.data.compareTo(data) < 0) {
			root.right = insert(root.right, data);
		} else {
			// Stylistically, Sean has this here to explicitly state that we are
			// disallowing insertion of duplicate values.
			;
		}

		return root;
	}
	
	// this function is used to make deletion simpler for the user
	// it takes the global root node and sets it equal to the real delete function
	public void delete(AnyType data) {
		root = delete(root, data); 
	}
	
	// this is a private function that will take a bst node and delete an element out of it
	// it returns null if the root is null, then tries to recur if there is a left and right element
	// else it returns an existing node if its sibling is null 
	// finally it will perform a rotation based on the data and its left node
	private Node<AnyType> delete(Node<AnyType> root, AnyType data) {
		if (root == null) {// returns null if the tree has no elements
			return null;
		} else if (data.compareTo(root.data) < 0) {	// comparison logic using delete instead of insert
			root.left = delete(root.left, data);	
		} else if (root.data.compareTo(data) < 0) {
			root.right = delete(root.right, data);
		} else {
			if (root.left == null && root.right == null) {// returns null if there's no children for the node
				return null;
			} else if (root.right == null) {
				return root.left;
			} else if (root.left == null) {
				return root.right;
			} else {
				root.data = findMax(root.left);// if there's a left and right child for this node, a swap must be done before the delete
				root.left = delete(root.left, root.data);
			}
		}

		return root;
	}

	// This method assumes root is non-null, since this is only called by
	// delete() on the left subtree, and only when that subtree is non-empty.
	private AnyType findMax(Node<AnyType> root) {
		while (root.right != null) { // find the right-most node in the bst
			root = root.right;
		}

		return root.data;
	}

	// Returns true if the value is contained in the BST, false otherwise.
	public boolean contains(AnyType data) {
		return contains(root, data);
	}
	
	// a recursive function to determine if an element is in a bst
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
	
	// the user-side function for printing a tree in LPR order
	public void inorder() {
		System.out.print("In-order Traversal:");
		inorder(root);
		System.out.println();
	}
	
	// prints a bst recursively in LPR order
	private void inorder(Node<AnyType> root) {
		if (root == null)
			return;

		inorder(root.left);
		System.out.print(" " + root.data);
		inorder(root.right);
	}
	// the user-side function for printing a tree in PLR order
	public void preorder() {
		System.out.print("Pre-order Traversal:");
		preorder(root);
		System.out.println();
	}

	// prints a bst recursively in PLR order
	private void preorder(Node<AnyType> root) {
		if (root == null)
			return;

		System.out.print(" " + root.data);
		preorder(root.left);
		preorder(root.right);
	}

	// the user-side function for printing a tree in LRP order
	public void postorder() {
		System.out.print("Post-order Traversal:");
		postorder(root);
		System.out.println();
	}
	// prints a bst recursively in LRP order
	private void postorder(Node<AnyType> root) {
		if (root == null)
			return;

		postorder(root.left);
		postorder(root.right);
		System.out.print(" " + root.data);
	}

	public static void main(String[] args) {
		GenericBST<String> myTree = new GenericBST<String>();


		myTree.insert("12");
		myTree.insert("15");
		myTree.insert("11");
		myTree.insert("14");
		myTree.insert("10");
		// for (int i = 0; i < 5; i++) {
		// int r = (int)(Math.random() * 100) + 1;
		// System.out.println("Inserting " + r + "...");
		// myTree.insert(r);
		// }
		System.out.println((hoursSpent()));
		myTree.inorder();
		myTree.preorder();
		myTree.postorder();
	}
	public static double hoursSpent(){
		return Math.sqrt(7);
	}
	public static double difficultyRating(){
		return Math.sqrt(3);
	}
}
