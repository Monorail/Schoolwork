// Sean Szumlanski
// COP 3503, Fall 2013

// TestCases.java
// ==============
// When you have your Maze class implemented properly, you should be able to
// run this program and produce the following output:
//
//   Test Case #1: PASS
//   Test Case #2: PASS
//   Test Case #3: PASS
//   Test Case #4: PASS
//   Test Case #5: PASS
//   Test Case #6: PASS
//
// Recall that your Maze.solve() method should not print anything to the screen.


import java.io.*;
import java.util.Queue;
import java.util.ArrayDeque;
import java.util.Scanner;

public class TestCases
{
	// A method for printing mazes.
	public static void printMaze(char [][] maze)
	{
		for (int i = 0; i < maze.length; i++)
		{
			for (int j = 0; j < maze[i].length; j++)
				System.out.print(maze[i][j]);

			System.out.println();
		}

		System.out.println();
	}

	// A method for reading mazes from a text file into a 2D char array. Assumes
	// there are no blank lines in the input file, and all lines are the same
	// length. Returns a reference to the 2D char array containing the maze.
	public static char [][] loadMaze(String filename) throws Exception
	{
		Scanner in = new Scanner(new File(filename));
		Queue<String> q = new ArrayDeque<String>();
		
		while (in.hasNextLine())
			q.add(in.nextLine());
		
		char [][] maze = new char[q.size()][q.element().length()];
		
		for (int i = 0; !q.isEmpty(); i++)
		{
			String s = q.remove();
			
			for (int j = 0; j < s.length(); j++)
				maze[i][j] = s.charAt(j);
		}
		
		return maze;
	}

	// A method for comparing two 2D char arrays. Returns 'true' if they're
	// identical, 'false' otherwise.
	public static boolean mazeCompare(char [][] a, char [][] b)
	{
		if (a == null && b == null)
			return true;

		if (a == null || b == null)
			return false;

		if (a.length != b.length)
			return false;

		for (int i = 0; i < a.length; i++)
		{
			if (a[i].length != b[i].length)
				return false;

			for (int j = 0; j < a[i].length; j++)
				if (a[i][j] != b[i][j])
					return false;
		}

		return true;
	}

	public static void main(String [] args) throws Exception
	{
		for (int i = 1; i <= 6; i++)
		{
			// Load the test case maze and its solution.
			char [][] maze = loadMaze("maze0" + i + ".txt");
			char [][] soln = loadMaze("soln0" + i + ".txt");

			// Solve the maze. (This is the method you must write yourself.)
			Maze.solve(maze);

			// Check whether your solution is correct.
			System.out.println("Test Case #" + i + ": " +
			                   (mazeCompare(maze, soln) ? "PASS" : "FAIL"));
		}
	}
}
