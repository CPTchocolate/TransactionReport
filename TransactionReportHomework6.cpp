//***********************************************************
//* Programmer: Holden Madriaga                             *
//* Date      : 31 August 2022                              *
//*                                                         *
//* Function  : Create a program to format "transaction.txt *
//* to an example provided by customer. Along with          *
//* along with computing new balances, and totals of        *
//* incrementing values.                                    *
//*                                                         *
//* Pseudocode:                                             *
//* initiate Variables and assign set lengths and values if *
//* needed.                                                 *
//* Attempt to open the transaction.txt file                *
//* Attempt to open the TRANSRPT.txt, or create if not found*
//* Output the header for the TRANSRPT file. along with     *
//* columns.                                                *
//* while not eof get values from next/first row.           *
//* output account number then spacing                      *
//* convert number arrays to double to allow math.          *
//* perform increments on initial and check columns.        *
//* determine to add or subtract with D or W for row        *
//* perform math and output initial, transaction code,      *
//* check ammount, and then new balance.                    *
//* perform decision on account status with new balance     *
//* value.                                                  *
//* output blank, *, or, ** with decision                   *
//* get new line or if end of line, output footer           *
//* then output initial balance totals and check ammount    *
//* close files to prevent coruption                        *
//***********************************************************
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>

using namespace std;

int main()
{
    ifstream infile;
    ofstream outfile;
    char accountNumber[6];
    char initialBalance[8];
    char checkAmount[7];
    char operation;
    double incrementInitial = 0;
    double incrementCheckAmount = 0;
    double tempNewBalance;

    infile.open("C:\\transactions.txt"); // attempt to open inputs file
    if (infile.fail()) { //determine if inputs file is open
        cout << "Error opening file inputs.\n" << endl;
        exit(1);
    }
    outfile.open("TRANSRPT.txt"); //attempt to open output file
    if (outfile.fail()) { //determine if output file is open
        cout << "Error opening file output.\n" << endl;
        exit(1);
    }

    outfile << "                         TRANSACTION REPORT" << endl << endl//setup header and columbs for output file
        << "ACCOUNT      INITIAL    TRANSACTION    CHECK         NEW" << endl
        << "NUMBER       BALANCE        CODE       AMOUNT      BALANCE     STATUS" << endl
        << "----------------------------------------------------------------------\n";
    while (!infile.eof())
    {
        infile >> accountNumber;
        infile >> initialBalance;
        infile >> operation;
        infile >> checkAmount;
        double initialBalanceTemp = atof(initialBalance);
        double checkAmountTemp = atof(checkAmount);
        incrementInitial += initialBalanceTemp;
        incrementCheckAmount += checkAmountTemp;
        if (operation == 'D') {
            tempNewBalance = initialBalanceTemp + checkAmountTemp;
        }
        else {
            tempNewBalance = initialBalanceTemp - checkAmountTemp;
        }
        outfile.setf(ios::fixed);
        outfile.setf(ios::showpoint);
        outfile << setprecision(2);

        outfile << accountNumber;
        outfile.width(8);
        outfile << "$";
        outfile.width(8);
        outfile << initialBalanceTemp;
        outfile.width(9);
        outfile << operation;
        outfile.width(8);
        outfile << "$";
        outfile.width(8);
        outfile << checkAmountTemp;
        outfile << "   $";
        outfile.width(8);
        outfile << tempNewBalance;
        if ((tempNewBalance < 200.00) && (tempNewBalance > 0)) {
            outfile.width(8);
            outfile << "*";
        }
        else if (tempNewBalance < 0) {
            outfile.width(8);
            outfile << "**";
        }

        outfile << endl;

    }
    outfile << "             =======                  ========" << endl; // add footer double lines
    outfile.width(13);
    outfile << "$";
    outfile.width(8);
    outfile << incrementInitial;
    outfile.width(17);
    outfile << "$";
    outfile.width(8);
    outfile << incrementCheckAmount;
    infile.close();
    outfile.close();

    return 0;
}