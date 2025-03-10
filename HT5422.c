# include <stdio.h>
int main(){
    double loanAmt, interestRate, monthlyPmt, monthlyInterest, remainingBal, firstMonInt;
    int monthlyCount = 0;

    printf("Enter the amount of the loan: ");
    scanf("%f\n", &loanAmt);
    printf("Enter the interest rate per year (in %): ");
    scanf("%f\n", &interestRate);
    printf("Enter your desired monthly payment: ");
    scanf("%f\n", monthlyPmt);

    monthlyInterest = (interestRate / 100) /12; 
    firstMonInt = loanAmt * monthlyInterest;

    if (monthlyPmt <= firstMonInt){
        printf("Your Loan cannot be repaid at that amount. First Months interest = %lf", firstMonInt);
    }
}