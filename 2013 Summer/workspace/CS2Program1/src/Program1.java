//Alex Berliner
//a2737438
public class Program1 {
	public static int CantHasSum(int [] array) {
		int sum=0,end = array.length;
		for(int i = 0;i<end;i++){
			if(array[i] - sum > 1)//basically, sum represents the previous subset's sum. 
				return sum+1;	  //it's being used to see if there are any breaks where a number could be placed, which would be p
			sum+=array[i];		  //if there's no break, update the subset sum
		}
		return sum+1;			  //return the "biggest element"in the array, the sum, plus 1
	}
	public static int difficultyRating() {
		//i had to think for this but a Szumlansky program that takes under 20 hours is great!
		return 3;
	}
}
