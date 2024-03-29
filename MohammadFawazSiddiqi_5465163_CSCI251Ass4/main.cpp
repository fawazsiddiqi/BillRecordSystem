/**********************************************************************
 * main.cpp - CSCI251 - Ass4- main() tester for class BillSystem
 * Mohammad Fawaz Siddiqi 5465163/mfs995 23/12/2018
 **********************************************************************/
#include <iostream>
#include "BillSystem.h"
using namespace std;
 
char Menu();

int main(){

	BillSystem BS;

	cout << "Begin tests for BillSystem\n\n";

	if(!BS.ReadFile("usage.txt")){
		cout << "File not found!\n\n";
		exit(1);
	}
	int n = BS.GetNumRecs();

	cout << "Num records read: " << n << endl << endl;

	for(int i=0; i<n && i<10; i++){
		BS.DisplayRec(i);
		cout << endl;
	}
	
    BS.CalDiscounts(); // uncoment when step 3 complete
    
    BS.CalBills();     // uncoment when step 4 complete
    BS.PrintReport();  // uncoment when step 4 complete

	cout << endl << "End tests for BillSystem\n";
    exit(0);
	return 0;
}

