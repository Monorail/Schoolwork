//Alex Berliner
//a2737438
public class RunLikeHell {

	static int DParr[];
	// for any index i, this function will take the greater of the indexes i-2
	// and i-3 from a dynamically constructed  DP array and deposit it
	// plus the value of the current knowledge block (i) and deposit it in the
	// dynamic array. This will build up a DP solution for
	// determining the max knowledge gained and requires that the dynamic array
	// have the base cases of [0], [1], and [2] and that we start building at [3].
	// This is based off of a recursive solution to this problem that would 
	// continually choose every possible path at every possible block.
	// The three possible paths are skipping to the next block, hitting the
	// next block available, or skipping two blocks and then hitting the next one.
	public static int maxGain(int[] blocks) {
		// checks for arrays that aren't large enough to perform the function on
		if (blocks == null || blocks.length == 0) {
			return 0;
		} else if (blocks.length == 1) {
			return blocks[0];
		} else if (blocks.length == 2) {
			return Math.max(blocks[0], blocks[1]);
		}

		DParr = new int[blocks.length];
		// set up base cases
		DParr[0] = blocks[0];
		DParr[1] = blocks[1];
		DParr[2] = blocks[2] + blocks[0];
		// for every array element starting with the third, add the array's
		// value to the max of the previous two numbers of the DP array,
		//which have already been memoized or are base cases
		for (int i = 3; i < blocks.length; i++) {
			DParr[i] = blocks[i] + Math.max(DParr[i - 2], DParr[i - 3]);
		}
		return Math.max(DParr[DParr.length - 1], DParr[DParr.length - 2]);
	}

	public static double difficultyRating() {
		return 3.5;
	}

	public static double hoursSpent() {
		return 4;
	}
}