//Alex Berliner
//a2737438
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Queue;

public class Maze {
	static int[] disjointSet;
	static int[] setRank;
	static char[][] maze;

	public static void main(String[] args) {
		//create(10,10);
		printMaze(create(10,10));
	}

	static void printMaze(char[][] maze) {
		for (int i = 0; i < maze.length; i++) {
			for (int j = 0; j < maze[0].length; j++) {
				System.out.print(maze[i][j]);
			}
			System.out.println();
		}
	}

	// generates a maze with width x height free spaces
	// with absolute size (width*2)+1 x (height*2)+1
	public static char[][] create(int width, int height) {
		if (width == 0 || height == 0)
			return null;
		disjointSet = new int[width * height];
		setRank = new int[width * height];
		// initialize sets
		for (int i = 0; i < disjointSet.length; i++)
			disjointSet[i] = i;
		for (int i = 0; i < setRank.length; i++)
			setRank[i] = 0;

		int absWidth = width * 2 + 1;
		int absHeight = height * 2 + 1;
		// generate stock maze
		// 1*n^2
		// generate random order to remove walls and put wall elements in an
		// array list
		ArrayList<wall> wallList = new ArrayList<wall>();
		maze = new char[absWidth][absHeight];
		for (int i = 0; i < maze.length; i++)
			maze[i][0] = '#';
		for (int i = 0; i < maze[0].length; i++)
			maze[0][i] = '#';
		for (int i = 1; i < absWidth; i++) {
			for (int j = 1; j < absHeight; j++) {
				// maze[i][j] = '#';
				maze[i][j] = ((i - 1) % 2 == 0 && (j - 1) % 2 == 0) ? ' ' : '#';
				
			}
		}
		// for (int i = 0; i < width; i++) {
		// for (int j = 0; j < height; j++) {
		// maze[i * 2 + 1][j * 2 + 1] = ' ';
		// }
		// }
		// 1*n^2
		for (int i = 1; i < absWidth - 1; i++)
			for (int j = 1; j < absHeight - 1; j++)
				if ((maze[i - 1][j] == ' ' && maze[i + 1][j] == ' ')
						|| (maze[i][j - 1] == ' ' && maze[i][j + 1] == ' '))
					wallList.add(new wall(i, j));
		// randomize order of wall removal
		Collections.shuffle(wallList);
		// add wallList elements to a queue
		Queue<wall> wallQ = new LinkedList<wall>();
		for (int i = 0; i < wallList.size(); i++) {
			wallQ.add(wallList.get(i));
		}
		// pop a wall from the queue to remove
		// this will pop every wall and only add remove ones that are in
		// different sets
		while (!wallQ.isEmpty()) {
			removeWall(wallQ.remove());
		}
		maze[1][1] = 's';
		maze[width * 2 - 1][height * 2 - 1] = 'e';
		return maze;
	}

	// removes a wall from the maze and updates the set information
	static void removeWall(wall delWall) {
		int absWallWidth = delWall.width;
		int absWallHeight = delWall.height;
		int relMazeWidth = (maze.length - 1) / 2;
		int a, b;
		// if the spaces are horizontally adjacent to the wall, get the set
		// numbers for the spaces on the left and right of it
		if (maze[absWallWidth - 1][absWallHeight] == ' '
				&& maze[absWallWidth + 1][absWallHeight] == ' ') {
			a = getSetNum(absWallWidth - 1, absWallHeight, relMazeWidth);
			b = getSetNum(absWallWidth + 1, absWallHeight, relMazeWidth);
		} else {
			// if it's vertical, bottom and top
			a = getSetNum(absWallWidth, absWallHeight - 1, relMazeWidth);
			b = getSetNum(absWallWidth, absWallHeight + 1, relMazeWidth);
		}
		// do not proceed to union if the two disjoint set indexes belong to the
		// same set
		if (findset(a) == findset(b)) {
			return;
		}
		// finally union the points and break down the wall
		union(a, b);
		maze[absWallWidth][absWallHeight] = ' ';
	}

	// converts coordinates into a disjointset index
	public static int getSetNum(int width, int height, int mazeWidth_r) {
		int Ax_a = width;
		int Ax_r = (Ax_a - 1) / 2;
		int Ay_a = height;
		int Ay_r = (Ay_a - 1) / 2;
		return Ay_r * mazeWidth_r + Ax_r;
	}

	// findset code written by Sean Szumlanski
	public static int findset(int index) {
		if (disjointSet[index] == index)
			return index;

		disjointSet[index] = findset(disjointSet[index]);
		return disjointSet[index];
	}

	// union code written by Sean Szumlanski
	public static void union(int a, int b) {
		int seta = findset(a);
		int setb = findset(b);

		if (setRank[seta] < setRank[setb])
			disjointSet[seta] = setb;
		else if (setRank[setb] < setRank[seta])
			disjointSet[setb] = seta;
		else {
			disjointSet[setb] = seta;
			setRank[seta]++;
		}
	}

	public static double hoursSpent() {
		return 10;
	}

	public static double difficultyRating() {
		return 3.3;
	}
}

// a simple class to store an ordered pair
class wall {
	static int wallNumber = 0;
	int width, height;

	public wall(int width, int height) {
		this.width = width;
		this.height = height;
		wallNumber++;
	}

	public String toString() {
		return "(" + width + "," + height + ")";
	}
}
