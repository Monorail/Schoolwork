// Sean Szumlanski
// COP 3503, Fall 2013

// TestCases.java
// ==============
// When you have your TopoSort class implemented properly, you should be able to
// run this program and produce the following output:
//
//   Test Case #1: PASS
//   Test Case #2: PASS
//   Test Case #3: PASS
//   Test Case #4: PASS
//   Test Case #5: PASS
//   Test Case #6: PASS
//   Test Case #7: PASS
//   Test Case #8: PASS
//   Test Case #9: PASS
//   Test Case #10: PASS
//   Test Case #11: PASS
//   Test Case #12: PASS
//
// Keep in mind that these test cases are by no means comprehensive! You need to
// create some of your own.

import java.io.IOException;
import java.util.Random;

public class TestCases {
	public static void main(String[] args) throws IOException {
		TopoSort t = new TopoSort("g1.txt");
//		System.out.println(t.difficultyRating());
//		System.out.println(t.hoursSpent());
//		System.out.print("Test Case #1: ");
//		System.out.println((t.hasTopoSort(1, 2) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case #2: ");
//		System.out.println((t.hasTopoSort(1, 3) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case #3: ");
//		System.out.println((t.hasTopoSort(1, 4) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case #4: ");
//		System.out.println((t.hasTopoSort(2, 1) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case #5: ");
//		System.out.println((t.hasTopoSort(2, 3) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case #6: ");
//		System.out.println((t.hasTopoSort(2, 4) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case #7: ");
//		System.out.println((t.hasTopoSort(3, 1) == false) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case #8: ");
//		System.out.println((t.hasTopoSort(3, 2) == false) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case #9: ");
//		System.out.println((t.hasTopoSort(3, 4) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case #10: ");
//		System.out.println((t.hasTopoSort(4, 1) == false) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case #11: ");
//		System.out.println((t.hasTopoSort(4, 2) == false) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case #12: ");
//		System.out.println((t.hasTopoSort(4, 3) == false) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
		t = new TopoSort("g2.txt");
		// System.out.println(t2);

//		System.out.print("Test Case #13: ");
//		System.out.println((t.hasTopoSort(4, 1) == false) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case #14: ");
//		System.out.println((t.hasTopoSort(8, 3) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case #15: ");
//		System.out.println((t.hasTopoSort(14, 11) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case #16: ");
//		System.out.println((t.hasTopoSort(6, 12) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//		for(int i = 1;i<14;i++){
//			System.out.print("Test Case #17: 12 " + i + " ");
//			System.out.println((t.hasTopoSort(12, i) == true) ? "PASS" : "FAIL");
//			System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//			t.runtime = 0;
//			System.out.println();
//		}
		System.out.print("Test Case #17: 12 " + 3 + " ");
		System.out.println((t.hasTopoSort(12, 3) == true) ? "PASS" : "FAIL");
		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
		t.runtime = 0;
		System.out.println();
		

//		for(int i = 1;i<14;i++)
//			for(int j = 1;j<14;j++){
//				System.out.print("Test Case #17: " + i + " " + j + "\n");
//				System.out.println((t.hasTopoSort(i, j) == false) ? "PASS" : "FAIL");
//				System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//				t.runtime = 0;
//			}
		
//		
//		System.out.print("Test Case #18: ");
//		System.out.println((t.hasTopoSort(12, 4) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;

		t = new TopoSort("g3.txt");

//		System.out.print("Test Case (1, 2): ");
//		System.out.println((t.hasTopoSort(1, 2) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case (1, 3): ");
//		System.out.println((t.hasTopoSort(1, 3) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case (1, 4): ");
//		System.out.println((t.hasTopoSort(1, 4) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case (2, 1): ");
//		System.out.println((t.hasTopoSort(2, 1) == false) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case (2, 3): ");
//		System.out.println((t.hasTopoSort(2, 3) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case (2, 4): ");
//		System.out.println((t.hasTopoSort(2, 4) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case (3, 1): ");
//		System.out.println((t.hasTopoSort(3, 1) == false) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case (3, 2): ");
//		System.out.println((t.hasTopoSort(3, 2) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case (3, 4): ");
//		System.out.println((t.hasTopoSort(3, 4) == false) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case (4, 1): ");
//		System.out.println((t.hasTopoSort(4, 1) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case (4, 2): ");
//		System.out.println((t.hasTopoSort(4, 2) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case (4, 3): ");
//		System.out.println((t.hasTopoSort(4, 3) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case (8, 11): ");
//		System.out.println((t.hasTopoSort(8, 11) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case (12, 1): ");
//		System.out.println((t.hasTopoSort(12, 1) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case (13, 1): ");
//		System.out.println((t.hasTopoSort(13, 1) == false) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case (12, 9): ");
//		System.out.println((t.hasTopoSort(12, 9) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case (8, 12): ");
//		System.out.println((t.hasTopoSort(8, 12) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//
//		System.out.print("Test Case (12, 8): ");
//		System.out.println((t.hasTopoSort(12, 8) == true) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//		System.out.println();
//
//		System.out.print("Test Case (16, 14): ");
//		System.out.println((t.hasTopoSort(16, 14) == false) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;
//		System.out.println();
//
//		System.out.print("Test Case (1, 1): ");
//		System.out.println((t.hasTopoSort(1, 1) == false) ? "PASS" : "FAIL");
//		System.out.println("Runtime: " + t.runtime + ". n = " + t.numElems);
//		t.runtime = 0;

	}
}
