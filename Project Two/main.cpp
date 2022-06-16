#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <stdlib.h>
#include <stdexcept>
#include "FinancialSimulation.h"
#undef max


//account for user error in getting doubles or integers
double GetDouble() {
	double userDouble;
	//get user info
	cin >> userDouble;

	//error checking
	if (cin.fail()) {
		throw runtime_error("Input entered is not a number.");
	}
	return userDouble;
}

int GetInt() {
	int userInt;
	//get user info
	cin >> userInt;

	//error checking
	if (cin.fail()) {
		throw runtime_error("Input entered is not a positive integer.");
	}
	if (userInt < 0) {
		throw runtime_error("Cannot have negative years! Try again.");
	}
	return userInt;
}

int GetMenuInt() {
	int userInt;
	//get user info
	cin >> userInt;

	//error checking
	if (cin.fail()) {
		throw runtime_error("Input entered is not a positive integer.");
		userInt = 0;
	}
	return userInt;

}


int main() {
	//set console colors green
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole,
		FOREGROUND_GREEN);

	//variables for userInput
	int userInput = 0;
	double newDouble = 0.00;
	int newInteger = 0;
	unsigned int menuInt = 0;

	FinancialSimulation sim1;

	sim1.requestDataInput();
	//print the table of values with and without deposit
	sim1.printTables();

	//loop over menu to allow additional changes to scenario
	while (userInput != 6) {
		try {
			if (userInput == 0){
				sim1.printMenu();
				userInput = GetMenuInt();
			}
			else if (userInput == 1) {
				//allow user to enter new initial investment
				system("cls");
				cout << "Enter new Initial Investment: $";
				newDouble = GetDouble();
				sim1.ChangeInitialInvestment(newDouble);
				sim1.printTables();
				//back to main menu
				userInput = 0;
			}
			else if (userInput == 2) {
				//allow user to enter new monthly deposit
				system("cls");
				cout << "Enter new Monthly Deposit Amount: $";
				newDouble = GetDouble();
				system("cls");
				sim1.ChangeMonthlyDeposit(newDouble);
				sim1.printTables();
				//back to main menu
				userInput = 0;
			}
			else if (userInput == 3) {
				//allow user to change years
				system("cls");
				cout << "Enter new number of Years: ";
				newInteger = GetInt();
				sim1.ChangeNumberYears(newInteger);
				sim1.printTables();
				//back to main menu
				userInput = 0;
			}
			else if (userInput == 4) {
				//allow user to change interest rate
				system("cls");
				cout << "Change Annual Interest Rate: %";
				newDouble = GetDouble();
				sim1.ChangeInterestAnnual(newDouble);
				sim1.printTables();
				//back to main menu
				userInput = 0;
			}
			else if (userInput == 5) {
				sim1.printTables();
				//back to main menu
				userInput = 0;
				continue;
			}
			else if (userInput == 6) {
				//terminate program
				break;
			}
			else {
				cout << "Menu Selection was not between 1-6. Please Try Again." << endl;
				userInput = 0;
				system("pause");
				system("cls");
				continue;
			}
		}
		catch (runtime_error& excpt) {
			//print error message
			cout << excpt.what() << endl;
			system("pause");
			system("cls");
			//back to main menu
			userInput = 0;
		}
		//since reaching end of while is only in error...
		//clear cin
		cin.clear();
		//skip bad line
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return 0;
}
