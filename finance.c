//Author: Ben Nguyen
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*struct definition
*/
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
	float savingInterest;
	float debtInterest;
	double debtAddPay;
	bool hasHouse;
	double rent;
	float houseInterest;
	double housePrice;
} person;

/* function for calculation interest added to savings account
*/

int savingsPlacement(person* x, float interest) 
{
	x->savings = x->savings + (x->savings * interest); 
return 0;

}

/* function for calculating debt subtracted from savings account
*/
int debt(person* x, float interest, double addPay){
	int i ;
	double payment;

	for (i = 1; i <=12; i = i+1){ //for loop calculates debt per month
		if (x->debt <=0 ){ //if debt less than or equal to 0,debt = 0
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

/* function for calculatin rent
*/
int rent(person* x, int rent){
	int i;
	for (i = 1; i <= 12; i = i+1){ //for loop that subtracts rent for savings for 12 months
		x->savings = x->savings - rent;
	}

	x->yearsRented = x->yearsRented + 1;
	return 0;
}


//nfl has loan amount of 166250
//fl has loan amount of 140000
/*functino for calculating loan for a house
*/
int house(person* x, double housePrice, float interest, double mortgageTerm){
	int i; 
	double I = interest/12;
	double N = mortgageTerm * 12;
	double Initloan = housePrice - x->downPayment; 
	double L = ((I * Initloan)/(1-(pow(1+I,-N)))) * N; //formula for calculating montly loan payment
	double P = L/N;
	for (i = 1; i <= 12; i = i+1){ //for loop that subtracts loan paymemt from loan and checking for 12 months
		if (x->loan > 0){ // checks if loan still exists
			x->loan = x->loan - P;
			x->checking =  x->checking - P;	
			}

		else{
			x->loan = 0; //if loan is less than zero, loan becomes 0		
		}
	};
return 0;


};

/* simulator for 40 years
*/
int simulator(person* x, double yearlySalary){
	int* wealthArray = malloc(sizeof(int) * 41); //mallocs space for array
	int i;
	int wealth;
	FILE *fptr;
	fptr = fopen("/Users/Bennguyen/Documents/CMPST2/Project1/nfl.txt","w"); //opens file for writing
	
	wealth = x->savings + x->checking - x->debt - x->loan;
	wealthArray[0] = wealth;
	fprintf(fptr,"%f + %f - %f - %f = %d \n",x->savings, x->checking, x->debt, x->loan, wealthArray[0]);
	for (i = 1; i < 41; i = i+1){ // for loop for 40 years
		x->checking += yearlySalary *.30; // adds percent of yearly salary to checking account
		x->savings += yearlySalary *.20; // adds percent of yearly salary to savings account
		savingsPlacement(x, x->savingInterest);
		debt(x, x->debtInterest, x->debtAddPay);
		if (x->hasHouse == false){ // checks if person has a house or not
			if (x->checking > x->downPayment){
				x->loan = x->housePrice - x->downPayment;
				x->hasHouse = true;

			}

			else{
				rent(x, x->rent);
			}
		}
		else if (x->hasHouse == true){	
			house(x, x->housePrice, x->houseInterest, 30);


		}
		wealth = x->savings + x->checking - x->debt - x->loan; // calculates wealth
		wealthArray[i] = wealth;
		
		fprintf(fptr,"%f + %f - %f - %f = %d \n",x->savings, x->checking, x->debt, x->loan, wealth); // writes wealth to file
		
	}
	printf("%d\n",wealthArray[0] );

	return *wealthArray; //returns pointer to first element of the array
}

// function for inputing and reading a file
person * createPerson(char fileName[]){
	FILE* inputFile = NULL;
	inputFile = fopen(fileName, "r");

	person* new;
	new = malloc(sizeof(person));

	new->loan = 0;
	new->hasHouse = false;
	new->yearsInDebt = 0;
	new->yearsRented = 0;
	new->debtPaid = 0;

	double n_savings = 0;
	float n_SavingInterest = 0;
	double n_checking = 0;
	double n_debt = 0;
	double n_debtAddPay = 0;
	float n_houseInterest = 0;
	double n_downPayment = 0;
	float n_debtInterest = 0;
	double n_rent = 0;


	if (inputFile != NULL){
		fscanf(inputFile, "%lf %f %lf %lf %lf %f %lf %f %lf",
			&n_savings, 
			&n_SavingInterest, 
			&n_checking,
			&n_debt, 
			&n_debtAddPay, 
			&n_houseInterest, 
			&n_downPayment, 
			&n_debtInterest, 
			&n_rent);

		
	}
	else {
		printf( "error input file is null \n");

		fclose(inputFile);
	}

	new->savings = n_savings;
	new->savingInterest = n_SavingInterest;
	new->checking = n_checking;
	new->debt = n_debt;
	new->debtAddPay = n_debtAddPay;
	new->houseInterest = n_houseInterest;
	new->downPayment = n_downPayment;
	new->debtInterest = n_debtInterest;
	new->rent = n_rent;

	return new;
}


	


/* main function
*/
int main() {

	person* fl;
	fl = malloc(sizeof(person));

	fl->savings = 5000.;
	fl->debt = 30100.;
	fl->checking = 1000.;
	fl->yearsInDebt = 0.;
	fl->yearsRented = 0.;
	fl->downPayment = 35000;
	fl->debtPaid = 0.;
	fl->savingInterest = .07;
	fl->debtInterest = .20;
	fl->debtAddPay = 15.;
	fl->hasHouse = false;
	fl->houseInterest =.045;
	fl->loan = 0;
	fl->rent = 850; 
	fl->housePrice = 175000;

	person* nfl;
	nfl = malloc(sizeof(person));

	nfl->savings = 5000.;
	nfl->debt = 30100.;
	nfl->checking = 1000.;
	nfl->yearsInDebt = 0.;
	nfl->yearsRented = 0.;
	nfl->downPayment = 8750;
	nfl->debtPaid = 0.;
	nfl->savingInterest = .01;
	nfl->debtInterest = .20;
	nfl->debtAddPay = 1.;
	nfl->hasHouse = false;
	nfl->houseInterest = .05;
	nfl->loan = 0;
	nfl->rent = 850; 
	nfl->housePrice = 175000;



	//simulator(fl,59000.);
	printf("debt paid %f \n", fl->debtPaid );
	printf("Years in debt: %f \n",fl->yearsInDebt);
	printf("Years rented: %f \n",fl->yearsRented);

	printf("debt paid %f \n", nfl->debtPaid );
	printf("Years in debt: %f \n",nfl->yearsInDebt);
	printf("Years rented: %f \n",nfl->yearsRented);


	simulator(nfl, 59000);

}