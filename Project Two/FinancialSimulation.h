#ifndef FINANCIALSIMULATION H
#define FINANCIALSIMULATION H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class FinancialSimulation
{
public:

	//utility
	double GetDouble();
	int GetInt();
	string nCharString(int n, char c);	
	
	//default Constructor
	FinancialSimulation();

	//function to gather user input, assign variable values
	void requestDataInput();

	//function for calculating compound interest without deposit
	double calculateCompoundInterestNoDeposit(int calcYear);

	//function for calculating year end balance without deposit;
	double calculateAccountBalanceNoDeposit(int calcYear);

	//function for calculating compound interest with deposit
	double calculateCompoundInterestDeposit(int calcYear);

	//function for calculating year end balance without deposit
	double calculateAccountBalanceDeposit(int calcYear);

	//function for printing tables
	void printTables();

	//function for printing usermenu
	void printMenu();

	//mutator & accessor for initialInvestment
	void ChangeInitialInvestment(double newInvestment);
	double DisplayInitialInvestment();

	//mutator & accessor for monthlyDeposit
	void ChangeMonthlyDeposit(double newMonthlyDeposit);
	double DisplayMonthlyDeposit();

	//mutator & accessor for number Years
	void ChangeNumberYears(unsigned int newNumberYears);
	int DisplayNumberYears();

	//mutator & accessor for interest Annual
	void ChangeInterestAnnual(double newInterestAnnual);
	double DisplayInterestAnnual();


private:
	double initialInvestment;
	double monthlyDeposit;
	int numberYears;
	double interestAnnual;
};

#endif

