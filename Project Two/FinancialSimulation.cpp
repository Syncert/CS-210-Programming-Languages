#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <stdexcept>

using namespace std;

#include "FinancialSimulation.h"

//utility
string FinancialSimulation::nCharString(int n, char c) {
    //initialize blank string
    string str = "";

    //for loop to populate string with character n times
    for (int i = 0; i < n; i++) {
        str = str + c;
    }

    // return the n character string
    return str;
}

//account for user error in getting doubles or integers
double FinancialSimulation::GetDouble() {
    double userDouble;
    //get user info
    cin >> userDouble;

    //error checking
    if (cin.fail()) {
        throw runtime_error("Input entered is not a number.");
    }
    return userDouble;
}

int FinancialSimulation::GetInt() {
    int userInt;
    //get user info
    cin >> userInt;

    //error checking
    if (cin.fail()) {
        throw runtime_error("Input entered is not a positive integer. Value set to 0");
    }
    if (userInt < 0) {
        throw runtime_error("Cannot have negative years! Try again.");
    }

    return userInt;
}

FinancialSimulation::FinancialSimulation() {
    initialInvestment = 0;
    monthlyDeposit = 0;
    numberYears = 0;
    interestAnnual = 0;
}

void FinancialSimulation::requestDataInput() {
    int loopInt = 0;
    int totalLineSize;
    totalLineSize = 34;

    //first line
    cout << nCharString(totalLineSize, '*') << endl;

    //second line , use nCharString totalLineSize - size of center text divided by 2 to surround statement
    cout << nCharString((totalLineSize - 12) / 2, '*') << " Data Input " <<
        nCharString((totalLineSize - 12) / 2, '*') << endl;
    while (loopInt != 1){
        try {
            //clear screen for loop re-attempts
            system("cls");

            //first line
            cout << nCharString(totalLineSize, '*') << endl;
            //second line , use nCharString totalLineSize - size of center text divided by 2 to surround statement
            cout << nCharString((totalLineSize - 12) / 2, '*') << " Data Input " <<
                nCharString((totalLineSize - 12) / 2, '*') << endl;
            //gather initial investment amount
            cout << left << setfill(' ') << setw(28) << "Initial Investment Amount: ";
            cout << right << "$";
            initialInvestment = GetDouble();
            cout << left << setfill(' ') << setw(28) << "Monthly Deposit: ";
            cout << right << "$";
            monthlyDeposit = GetDouble();
            cout << left << setfill(' ') << setw(28) << "Annual Interest: ";
            cout << right << "%";
            interestAnnual = GetDouble();
            cout << left << setfill(' ') << setw(28) << "Number of years: ";
            numberYears = GetInt();
            cout << endl;
            loopInt = 1;
            }
        catch (runtime_error& excpt) {
            cout << excpt.what() << endl;
            system("pause");
        }
    //clear cin
    cin.clear();
    //skip bad line
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    //pause
    system("pause");
    system("cls");

}

double FinancialSimulation::calculateCompoundInterestNoDeposit(int calcYear) {
    double compoundInterest;
    double convertInterestRateYearly;
    double convertInterestRateMonthly;
    double runningTotalInterest = 0.0;
    int numMonths;


    //convert interest rate
    convertInterestRateYearly = interestAnnual / 100;
    convertInterestRateMonthly = interestAnnual / 100 / 12;
    //calculate numMonths
    numMonths = calcYear * 12;

    //loop to calculate most recent years interest earnings
    //I need the year end interest calculated by <CURR Year INTEREST> minus <LAST Year INTEREST>
    if (calcYear == 1) {
        compoundInterest = (initialInvestment * pow((1 + convertInterestRateMonthly), numMonths) - initialInvestment);
    }
    else {
        compoundInterest = (initialInvestment * pow((1 + convertInterestRateMonthly), numMonths) - initialInvestment) -
            (initialInvestment * pow((1 + convertInterestRateMonthly), numMonths - 12) - initialInvestment);
    }

    return compoundInterest;
}

double FinancialSimulation::calculateAccountBalanceNoDeposit(int calcYear) {
    double accountBalance;
    double convertInterestRateYearly;
    double convertInterestRateMonthly;
    int numMonths;


    //convert interest rate
    convertInterestRateYearly = interestAnnual / 100;
    convertInterestRateMonthly = interestAnnual / 100 / 12;
    //calculate numMonths
    numMonths = calcYear * 12;

    accountBalance = initialInvestment * pow((1 + convertInterestRateMonthly), numMonths);

    return accountBalance;
}

double FinancialSimulation::calculateCompoundInterestDeposit(int calcYear) {
    double compoundInterest;
    double compoundInterestLastYear;
    double convertInterestRateMonthly;
    double runningTotalInterest = 0;
    double runningTotalInterestLastYear = 0;
    int numMonths;
    double accountBalance;
    double accountBalanceLastYear;


    //convert interest rate
    convertInterestRateMonthly = interestAnnual / 100 / 12;

    //calculate numMonths
    numMonths = calcYear * 12;

    //account balance for compounding
    accountBalance = initialInvestment;
    accountBalanceLastYear = initialInvestment;

        if (calcYear == 1) {
            for (int i = 1; i < numMonths + 1; ++i) {
                compoundInterest = ((accountBalance + monthlyDeposit) * convertInterestRateMonthly);
                runningTotalInterest = runningTotalInterest + compoundInterest;
                accountBalance = accountBalance + monthlyDeposit + compoundInterest;
            }
        }
        else {
            //calculate total interest
            for (int i = 1; i < numMonths + 1; ++i) {
                compoundInterest = ((accountBalance + monthlyDeposit) * convertInterestRateMonthly);
                runningTotalInterest = runningTotalInterest + compoundInterest;
                accountBalance = accountBalance + monthlyDeposit + compoundInterest;
            }
            //calculate last years interest to subtract
            for (int i = 1; i < numMonths - 11; ++i) {
                compoundInterestLastYear = ((accountBalanceLastYear + monthlyDeposit) * convertInterestRateMonthly);
                runningTotalInterestLastYear = runningTotalInterestLastYear + compoundInterestLastYear;
                accountBalanceLastYear = accountBalanceLastYear + monthlyDeposit + compoundInterestLastYear;
            }
            //total interest minus last years interest
            runningTotalInterest = runningTotalInterest - runningTotalInterestLastYear;
        }

    return runningTotalInterest;
}

double FinancialSimulation::calculateAccountBalanceDeposit(int calcYear) {
    double compoundInterest;
    double convertInterestRateYearly;
    double convertInterestRateMonthly;
    int numMonths;
    double accountBalance;


    //convert interest rate
    convertInterestRateYearly = interestAnnual / 100;
    convertInterestRateMonthly = interestAnnual / 100 / 12;

    //calculate numMonths
    numMonths = calcYear * 12;

    //account balance for compounding
    accountBalance = initialInvestment;

    for (int i = 1; i < numMonths + 1; ++i) {
        compoundInterest = (accountBalance + monthlyDeposit) * convertInterestRateMonthly;
        accountBalance = accountBalance + monthlyDeposit + compoundInterest;
        //check the calculation
        //cout << "month " << i << " interest :" << compoundInterest << endl;
        //cout << "closing balance: " << accountBalance << endl;
    }

    return accountBalance;
}

void FinancialSimulation::printTables() {
    //clear menu options when applicable
    system("cls");
    //BALANCE AND INTEREST WITHOUT ADDITIONAL MONTHLY DEPOSITS TABLE//
    //set fixed and precision for cout
    cout << fixed << setprecision(2);
    cout << nCharString(30, ' ') << "Balance and Interest WITHOUT Additional Monthly Deposits" 
        << nCharString(30, ' ')
        << endl;
    cout << nCharString(105, '=') << endl;

    //print the facts of the table
    cout << left << setw(15) << "Initial Investment: " << right << "$" << initialInvestment;
    cout << left << setw(15) << " |  Monthly Deposit: " << right << "$0.00";
    cout << left << setw(15) << " |  Number Years: " << numberYears;
    cout << left << setw(15) << " |  Annual Interest: " << interestAnnual << "%" << endl;
    cout << nCharString(105, '=') << endl;
    cout << endl;
    cout << endl;

    //headers for table values
    cout << left << setw(32) << "Year";
    cout << left << setw(27) << "Year End Balance";
    cout << left << setw(25) << "Year End Earned Interest" << endl;
    cout << nCharString(105, '-') << endl;

    //loop over values for every year of table
    for (int i = 1; i < numberYears + 1; ++i) {
        cout << nCharString(1, ' ') << left << setw(31) << i;
        cout << left << "$" << setw(27) << calculateAccountBalanceNoDeposit(i);
        cout << left << "$" << setw(25) << calculateCompoundInterestNoDeposit(i);
        cout << endl;
    }

    //set up next table 
    cout << endl;
    cout << endl;

    //BALANCE AND INTEREST WITH ADDITIONAL MONTHLY DEPOSITS TABLE//
    cout << nCharString(30, ' ') << "Balance and Interest WITH Additional Monthly Deposits" << nCharString(30, ' ')
        << endl;
    cout << nCharString(105, '=') << endl;

    //print the facts of the table
    cout << left << setw(15) << "Initial Investment: " << right << "$" << initialInvestment;
    cout << left << setw(15) << " |  Monthly Deposit: " << right << "$" << monthlyDeposit;
    cout << left << setw(15) << " |  Number Years: " << numberYears;
    cout << left << setw(15) << " |  Annual Interest: " << interestAnnual << "%" << endl;
    cout << nCharString(105, '=') << endl;
    cout << endl;
    cout << endl;

    //headers for table values
    cout << left << setw(32) << "Year";
    cout << left << setw(27) << "Year End Balance";
    cout << left << setw(25) << "Year End Earned Interest" << endl;
    cout << nCharString(105, '-') << endl;

    //loop over values for every year of table
    for (int i = 1; i < numberYears + 1; ++i) {
        cout << nCharString(1, ' ') << left << setw(31) << i;
        cout << left << "$" << setw(27) << calculateAccountBalanceDeposit(i);
        cout << left << "$" << setw(25) << calculateCompoundInterestDeposit(i);
        cout << endl;
    }

    //pause
    cout << endl;
    system("pause");
    system("cls");

}

void FinancialSimulation::printMenu() {
    cout << setw(12) << setfill(' ') << "User Menu";
    cout << setw(12) << setfill(' ') << endl;
    cout << "1. Change Initial Investment from $" << DisplayInitialInvestment() << endl;
    cout << "2. Change Monthly Deposit from $" << DisplayMonthlyDeposit() << endl;
    cout << "3. Change Number of Years from " << DisplayNumberYears() << endl;
    cout << "4. Change Annual Interest Rate from %" << DisplayInterestAnnual() << endl;
    cout << "5. Print Tables" << endl;
    cout << "6. Exit Program" << endl;
    cout << "Your Selection: ";
}

//mutator & accessor for initialInvestment
void FinancialSimulation::ChangeInitialInvestment(double newInvestment) {
    initialInvestment = newInvestment;
}

double FinancialSimulation::DisplayInitialInvestment() {
    return initialInvestment;
}

//mutator & accessor for monthlyDeposit
void FinancialSimulation::ChangeMonthlyDeposit(double newMonthlyDeposit) {
    monthlyDeposit = newMonthlyDeposit;
}

double FinancialSimulation::DisplayMonthlyDeposit() {
    return monthlyDeposit;
}

//mutator & accessor for number Years
void FinancialSimulation::ChangeNumberYears(unsigned int newNumberYears) {
    numberYears = newNumberYears;

}

int FinancialSimulation::DisplayNumberYears() {

    return numberYears;
}

//mutator & accessor for interest Annual
void FinancialSimulation::ChangeInterestAnnual(double newInterestAnnual) {
    interestAnnual = newInterestAnnual;
}

double FinancialSimulation::DisplayInterestAnnual() {
    return interestAnnual;
}

