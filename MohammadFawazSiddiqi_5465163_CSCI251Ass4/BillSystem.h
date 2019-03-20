/**********************************************************************
 * BillSystem.h - CSCI251 - Ass4- BillSystem class declaration
 * Mohammad Fawaz Siddiqi 5465163/mfs995 23/12/2018
 **********************************************************************/
#ifndef BILLSYS_H
#define BILLSYS_H

#include <iostream>
#include <vector>
#include <map>
#include "BillRecord.h"
using namespace std;


class BillSystem {
    
public:
    ~BillSystem();
    bool ReadFile(char *fname);
    int GetNumRecs();
    void DisplayRec(int i); // prints ith record on screen
    void CalDiscounts(); // Calculate discount
    void CalBills();  // Calculate the bill
    void PrintReport();  // Print a report
private:
    vector<BillRecord*> BillRecords; // vector of pointers to class BillRecord
    multimap<string, BillRecord*> recordsMap; // multimap of all customer keys, pointers
    map<string, string> discCust;  // map of customers with discounts only
};

#endif

