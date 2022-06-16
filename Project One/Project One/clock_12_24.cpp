/*
* clock_12_24.cpp
*
*  Date: 5/17/2022
*  Author: Nicholas Kreuziger
*/


/*
    * Question: How to pull system time?
    *date time documentation referenced:
    *https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm#:~:text=To%20access%20date%20and%20time%20related%20functions%20and,time%20and%20date%20as%20some%20sort%20of%20integer.

    * Question: How to disable "function or variable may be unsafe compile error...
    * https://stackoverflow.com/questions/22450423/how-to-use-crt-secure-no-warnings
    * #define _CRT_SECURE_NO_WARNINGS
    *
    * Question: How do I pass the variables into the addone() functions
    * https://www.genuinecoder.com/cpp-exchange-values-of-two-variables-swapping-html/#:~:text=C%2B%2B%20program%20to%20exchange%20values%20of%20two%20variables,function%20will%20reflect%20in%20the%20main%20method%20also.
    *
    * Question: How do I clear the screen?
    * https://mrcodehunter.com/how-to-clear-screen-in-c/#:~:text=For%20clear%20screen%20in%20C%2B%2B%20you%20can%20use,screen%20in%20C%2B%2B%20in%20both%20Windows%20and%20Linux%3A
    *
*/


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <stdlib.h>
using namespace std;

int gethour() {
    int hour;
    time_t now = time(0);
    tm* ltm = localtime(&now);

    hour = ltm->tm_hour; //get minute

    return hour;
}

int getminute() {
    int minute;
    // current date/time based on current system
    time_t now = time(0);
    tm* ltm = localtime(&now);

    minute = ltm->tm_min; //get minute

    return minute;
}

int getsecond() {
    int second;
    // current date/time based on current system
    time_t now = time(0);
    tm* ltm = localtime(&now);

    second = ltm->tm_sec; //get second
    return second;
}

void addonehour(int* h) {

    if ((*h >= 0) && (*h <= 22)) {
        *h = (*h + 1);
    }
    else {
        *h = 0;
    }
}

void addoneminute(int* h, int* m) {
    if ((*m >= 0) && (*m <= 58)) {
        *m = (*m + 1);
    }
    else {
        *m = 0;
        addonehour(h);
    }
}

void addonesecond(int* h, int* m, int* s) {
    if ((*s >= 0) && (*s <= 58)) {
        *s = (*s + 1);
    }
    else {
        *s = 0;
        addoneminute(h, m);
    }
}

string twoDigitString(unsigned int n) {
    string minutes;
    minutes = to_string(n); //convert int to string

    //check if string has only one number, if so insert 0
    if (minutes.size() == 1) {
        minutes.insert(0, "0");
    }

    // return the two digit string
    return minutes;
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

string formatTime24(unsigned int h, unsigned int m, unsigned int s) {
    string hour;
    string minute;
    string second;
    string formattedTime;

    hour = twoDigitString(h);
    minute = twoDigitString(m);
    second = twoDigitString(s);

    formattedTime = hour + ':' + minute + ':' + second;

    // return time as hh:mm:ss
    return formattedTime;
}

string formatTime12(unsigned int h, unsigned int m, unsigned int s) {
    string hour;
    string minute;
    string second;
    string formattedTime;

    //account for hours in 12 hr format
    if (h == 0) {

        hour = "12";

    }
    else if (h > 12) {

        hour = twoDigitString(h - 12);
    }
    else {

        hour = twoDigitString(h);

    }
    //rest are consistent with military time...
    minute = twoDigitString(m);
    second = twoDigitString(s);

    //account for AM or PM...
    if (h >= 0 && h < 12) {

        formattedTime = hour + ':' + minute + ':' + second + " A M";

    }
    else if (h > 11) {

        formattedTime = hour + ':' + minute + ':' + second + " P M";

    }
    return formattedTime;
}

void printMenu(string strings[], unsigned int width, char c) {

    cout << nCharString(width, c) << endl;
    //size of a pointer is 2 bytes, sizeof yields 8 total. Divide by 2
    int sizeArray = sizeof(strings);
    sizeArray = sizeArray / 2;

    for (int i = 0; i < sizeArray; ++i) {
        int spacesInsert = (22 - (strings[i].length()));
        cout << "* " << (i + 1) << "-" << strings[i] << nCharString(spacesInsert, ' ') << '*' << endl;
    }

    // outside the loop print another width *s followed by an endl
    cout << nCharString(width, c) << endl;
}

void displayClocks(unsigned int h, unsigned int m, unsigned int s) {

    cout << nCharString(27, '*') + nCharString(3, ' ') + nCharString(27, '*') << endl; //top line
    cout << '*' << nCharString(6, ' ') << "12-HOUR CLOCK" << nCharString(6, ' ') << '*' << nCharString(3, ' ') //labels
        << '*' << nCharString(6, ' ') << "24-HOUR CLOCK" << nCharString(6, ' ') << '*' << endl;
    cout << endl;
    cout << '*' << nCharString(6, ' ') << formatTime12(h, m, s) << nCharString(7, ' ') << '*' << nCharString(3, ' ') //clocks
        << '*' << nCharString(8, ' ') << formatTime24(h, m, s) << nCharString(9, ' ') << '*' << endl;
    cout << nCharString(27, '*') + nCharString(3, ' ') + nCharString(27, '*') << endl; //top line

}

int main()
{
    //system time variable
    time_t now = time(0);
    tm* ltm = localtime(&now);

    //initialize program with system time
    int h = gethour();
    int m = getminute();
    int s = getsecond();

    ////test h, m ,s
    //int h = 1;
    //int m = 20;
    //int s = 59;

    //length of line
    int line_width = 27;

    //array of instruction options
    string strings[4] = { "Add One Hour", "Add One Minute", "Add One Second", "Exit Program" };

    //initialize user input variable
    int userInput = 0;

    //where loop for menu -> menu selection -> display clocks

    while (userInput != 4) {

        system("CLS");

        displayClocks(h, m, s);

        printMenu(strings, line_width, '*');

        cin >> userInput;

        //add one hour
        if (userInput == 1) {

            addonehour(&h);

        }
        //add one minute
        else if (userInput == 2) {

            addoneminute(&h, &m);

        }
        //add one second
        else if (userInput == 3) {
            addonesecond(&h, &m, &s);
        }
        //exit program
        else if (userInput == 4) {
            break;
        }

    }

    return 0;
}
