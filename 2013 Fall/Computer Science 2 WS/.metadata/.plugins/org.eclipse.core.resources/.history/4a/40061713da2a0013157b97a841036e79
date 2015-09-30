// Sean Szumlanski
// COP 3503, Fall 2013

// TestCase.java
// =============
// When you have your Treap class implemented properly, you should be able to
// run this program and produce the following output:
//
//   In-order Traversal: 2 3 5 6 8 20 40
//   Pre-order Traversal: 20 8 3 2 6 5 40
//   Post-order Traversal: 2 5 6 3 8 40 20
//
//   Treap size: 7
//   Treap height: 4
//
//   In-order Traversal: 2 5 6 8 20 40
//   Pre-order Traversal: 20 8 6 5 2 40
//   Post-order Traversal: 2 5 6 8 40 20
//
//   Treap size: 6
//   Treap height: 4


public class TestCase
{
	public static void main(String [] args)
	{
		Treap<Integer> t = new Treap<Integer>();

		// insert values into treap
		t.add(8, 12);
		t.add(2, 190);
		t.add(3, 18);
		t.add(40, 16);
		t.add(5, 47);
		t.add(6, 44);
		t.add(20, 10);
		t.add(40, 1); // notice attempt to insert duplicate value

		// print tree traversals
		Traversals.inorder(t);
		Traversals.preorder(t);
		Traversals.postorder(t);
		System.out.println();

		// print treap stats
		System.out.println("Treap size: " + t.size());
		System.out.println("Treap height: " + t.height());
		System.out.println();

		// attempt to delete values not in treap
		t.remove(42);
		t.remove(43);

		// delete value 3 from treap
		t.remove(3);

		// print tree traversals
		Traversals.inorder(t);
		Traversals.preorder(t);
		Traversals.postorder(t);
		System.out.println();

		// print treap stats
		System.out.println("Treap size: " + t.size());
		System.out.println("Treap height: " + t.height());
	}
}
