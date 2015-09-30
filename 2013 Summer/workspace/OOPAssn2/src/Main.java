import java.util.Scanner;


public class Main {
	public static void main(String[] args) {
		//creates scanner
		Scanner sc = new Scanner(System.in);
		//asks for the filing status
		System.out.print("Enter the filing status: ");
		int filingStatus = sc.nextInt();
		//asks for the taxable income
		System.out.print("Enter the taxable income: ");
		double taxableIncome = sc.nextDouble();
		TaxCalculator cal = new TaxCalculator();
		
		System.out.println("Tax is " + cal.calculateTax(filingStatus, taxableIncome));
	}
}
