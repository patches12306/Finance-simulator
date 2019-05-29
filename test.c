
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
typedef struct people

{
	double savings;
	double checking;
	double debt;
	double yearsInDebt;
	double yearsRented;
	double loan;
	double downPayment;
	double debtPaid;
	double savingInterest;
	double debtInterest;
	double debtAddPay;
	bool hasHouse;
	double rent;
	double houseInterest;
} person;

int savingsPlacement(person* x, float interest) 
{
	x->savings = x->savings + (x->savings * interest);
return 0;

}


int debt(person* x, float interest, double addPay){
	int i ;
	double payment;

	for (i = 1; i < 13; i = i+1){
		if (x->debt <=0 ){
			x->debt =0;
			return 0;
			}
		else{
			payment = (x->debt * .03) + addPay;
			x->savings = x->savings - payment;
			x->debt = x->debt - payment;
			x->debtPaid = x->debtPaid + payment;
			}	
		}
	x->yearsInDebt = x->yearsInDebt + 1;
	x->debt = x->debt + (x->debt * interest);

	
	return 0;
}


int rent(person* x, int rent){
	int i;
	for (i = 1; i < 13; i = i+1){
		x->savings = x->savings - rent;
		x->yearsRented = x->yearsRented + 1;
	}
	return 0;
}
//nfl has loan amount of 166250
//fl has loan amount of 140000
int house(person* x, double housePrice, double interest, double mortgageTerm){
	double i = interest/12;;
	double N = mortgageTerm * 12;
	double D = ((1+pow(i,N)))/ (i*pow((1+i),N));
	double P = (x->loan)/(D);
	x->loan = x->loan - P;
	x->checking =  x->checking - P;
	

return 0;
}

int simulator(person* x, double yearlySalary){
	int* wealthArray = malloc(sizeof(int) * 41);
	int i;
	int wealth;
	FILE *fptr;
	fptr = fopen("/Users/Bennguyen/Documents/CMPST2/Project1/project.txt","w");
	wealthArray[0] = -24100;
	fprintf(fptr,"%f + %f - %f - %f = %d \n",x->savings, x->checking, x->debt, x->loan, wealth);
	for (i = 1; i < 41; i = i+1){
		x->checking += yearlySalary *.30;
		x->savings += yearlySalary *.20;
		savingsPlacement(x, x->savingInterest);
		debt(x, x->debtInterest, x->debtAddPay);
		if (x->hasHouse == false){
			if (x->checking > x->downPayment){
				x->hasHouse = true;
			}	
			else{
				rent(x, x->rent);
			}
		}
		else if (x->hasHouse == true){	
			x->loan = 140000;
			printf("has hosue");
			house(x, 175000, x->houseInterest, 30);
		}
		wealth = x->savings + x->checking - x->debt - x->loan;
		wealthArray[i] = wealth;
		fprintf(fptr,"%f + %f - %f - %f = %d \n",x->savings, x->checking, x->debt, x->loan, wealth);
	}
	return wealthArray;
}




	



int main() {

	person* fl;
	fl = malloc(sizeof(person));
	fl->savings = 5000.;
	fl->debt = 30100.;
	fl->checking = 0.;
	fl->yearsInDebt = 0.;
	fl->yearsRented = 0.;
	fl->downPayment = 140000.;
	fl->debtPaid = 0.;
	fl->savingInterest = .07;
	fl->debtInterest = .20;
	fl->debtAddPay = 15.;
	fl-> hasHouse = false;
	fl->houseInterest = .045;
	


	person* nfl;
	nfl = malloc(sizeof(person));
	fl->savings = 5000.;
	fl->debt = 30100;
	fl->checking = 0;
	nfl->yearsInDebt = 0;
	nfl->yearsRented = 0;


	simulator(fl,59000.);
	printf("%f\n", fl->debt);
	//debt(fl, fl->debtInterest,);
	printf("%f\n",fl->savings);
}