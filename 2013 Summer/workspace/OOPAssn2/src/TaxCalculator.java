import java.util.Scanner;
public class TaxCalculator {
	//the next arrays are the tax brackets for each type of filer
	int[] singleArr = {0,8350,33950,82250,171550,372950,372951};//Single person
	int[] marriedArr = {0,16700,67900,137050,208850,372950,372951};// Married Person
	int[] separateArr = {0,8350,33950,68525,104425,186475,186476};//Married but separated
	int[] householdArr = {0,11950,45500,117450,190200,372950,372951};//Head of household
	double[] taxArr = {0,.10,.15,.25,.28,.33,.35};//values of the tax brackets
	public double calculateTax(int filingStatus, double taxableIncome){
		double tax = 0;//amount owed to government
		//get ready for switch-case town
		switch(filingStatus){
		//calculates taxes for case 0 single filers
		case 0:return taxMath(taxableIncome,singleArr);
		//calculates taxes for case 1 married filers
		case 1:return taxMath(taxableIncome,marriedArr);
		//calculates taxes for case 2 separate filing separately
		case 2:return taxMath(taxableIncome,separateArr);
		//calculates taxes for case 3 Head of Household
		case 3:return taxMath(taxableIncome,householdArr);
		//returns -1 in case a bad value's entered
		default: {System.out.println("Valid number not entered.");return -1;}
		}
	}
	public double taxMath(double taxableIncome, int[] taxBracket){
		int i=1;
		double tax=0;
		//the while loop continues when there's still income higher than the currently looked at tax bracket and while the array is still in bounds
		//When the loop completes, it's either because the amount of income doesn't make it to the next bracket or the income is past the highest bracket
		while(taxableIncome>taxBracket[i] && i<taxBracket.length-1)
			//this will subtract the values of the previous tax bracket from the current one to determine the amount of money in that particular range and multiply by the corresponding tax percentage
			tax+=(taxBracket[i] - taxBracket[i-1]) * taxArr[i++];
		//this is like the line in the loop except it uses any remaining funds instead of the value of a bracket
		tax+=(taxableIncome - taxBracket[i-1]) * taxArr[i]; 
		return tax;
	}
}