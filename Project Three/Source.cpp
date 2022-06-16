#include <Python.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <stdexcept>
#undef max

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void printMenu()	 {
	cout << "1: Display the number of times an item appears." << endl;
	cout << "2: Count Purchases of a specific Item." << endl;
	cout << "3: Display Histogram of items." << endl;
	cout << "4: Exit Program" << endl;
	cout << "Enter your selection as a number 1, 2, 3 or 4." << endl;
}

int GetInt() {
	int userInt;
	//get user info
	std::cin >> userInt;

	//error checking
	if (std::cin.fail()) {
		throw runtime_error("Input entered is not a number or larger than 2147483647. Please try again.");
		//clear cin
		std::cin.clear();
		//skip bad line
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	if (userInt < 0) {
		throw runtime_error("Input entered is not a positive number. Please try again.");
		//clear cin
		std::cin.clear();
		//skip bad line
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return userInt;
}


int GetMenuInt() {
	int userInt;
	//get user info
	std::cin >> userInt;

	//error checking
	if (std::cin.fail()) {
		throw runtime_error("Input entered is not a number or larger than 2147483647. Please try again.");
		return 0;
	}
	if (userInt < 0) {
		throw runtime_error("Input entered is not a positive number. Please try again.");
		return 0;
	}
	if (userInt > 4) {
		throw runtime_error("You did not select a number between 1 - 3. Please try again.");
		return 0;
	}
	if (!std::cin.fail()) {
		return userInt;
	}
}

string nCharString(int n, char c) {
	//initialize blank string
	string str = "";

	//for loop to populate string with character n times
	for (int i = 0; i < n; i++) {
		str = str + c;
	}

	// return the n character string
	return str;
}

int main()
{
	//user menu
	int userMenuSelect = 0;
	//user input integer
	int userValue = 0;
	//user input item
	string userItem;

	//file stream variables
	ifstream inFS;
	string line;
	string itemName;
	int itemCount;


		while (userMenuSelect != 4) {

		try{
			if (userMenuSelect == 0) {
				//print menu
				printMenu();

				//gather user int with error checking
				userMenuSelect =  GetMenuInt();
				std::system("cls");
				}
			else if (userMenuSelect == 1) {
				//count total purchases for each item
				CallProcedure("CountPurchases");
				cout << "Press Enter to continue";

				//back to user menu
				userMenuSelect = 0;
			}
			else if (userMenuSelect == 2) {
				//prompt user
				cout << "What item would you like a count of?" << endl;
				std::cin >> userItem;
				std::system("cls");
				//call python function to calculate value occurrence
				userValue = callIntFunc("CountOccurencePurchases", userItem);
				//print result
				cout << userItem << " was purchased " << userValue << " times." << endl;

				//back to user menu
				userMenuSelect = 0;
				cout << "Press Enter to continue";
				//getchar() to pause screen
				getchar();

			}
			else if (userMenuSelect == 3) {
				//write .dat file
				CallProcedure("HistogramFile");
				//open file from procedure
				inFS.open("Data\\frequency.dat");

				//validate success
				if (inFS.fail()) {
					cout << "could not open file" << endl;
					return 1;
				}

				//iterate over lines
				while (!inFS.fail()) {

					inFS >> itemName;
					inFS >> itemCount;

					if (!inFS.good()) {
						//no more data, break
						break;
					}

					cout << left << setw(12) << itemName;
					cout << ": ";
					cout << nCharString(itemCount, '*');
					cout << endl;

				}

				inFS.close();
				cout << "Press Enter to continue";
				//back to main menu
				userMenuSelect = 0;
			}
			else if (userMenuSelect == 4) {
				//end program
				break;
			}
			else {
				//bring back to userMenu
				userMenuSelect = 0;
			}
		}
		catch (runtime_error& excpt) {
			//print error message
			cout << excpt.what() << endl;
			//reset userMenu value to 0 
			// 
			//pause for user input and then clear screen to show menu again
			std::system("pause");
			std::system("cls");
		}
		//clear cin
		std::cin.clear();
		//skip bad line
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::system("cls");
	}
	cout << "Thanks for your time. Goodbye!" << endl;
}
