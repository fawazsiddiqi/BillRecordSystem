/**********************************************************************
 * BillSystem.cpp - CSCI251 - Ass4 - BillSystem class definition
 * Mohammad Fawaz Siddiqi 5465163/mfs995 23/12/2018
 **********************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <set>
#include <map>
#include <typeinfo>
#include "BillSystem.h"
using namespace std;


// ========== class BillSystem Public Function definitions ==========

// Destructor
BillSystem::~BillSystem()
{
    //Iterate BillRecords vector and delete each ptr
    for(int i=0; i < BillRecords.size(); i++) { delete BillRecords[i]; }
}

// Reads data in "usage.txt" into BRecs vector
bool BillSystem::ReadFile(char *fname)
{
    ifstream fin;
    fin.open(fname);
    if(!fin.good()) {
        return false;
    }
    
    while(!fin.eof()) {
        string billType; BillRecord *temp;
        fin>>billType; // read BillType
        if(fin.fail()) {
            break;
        }
        
        if(billType.compare("Elect")==0) {
            temp = new ElectBillRecord();
        }
        else if(billType.compare("Gas")==0) {
            temp = new GasBillRecord();
            
        }
        else{
            temp = new PhoneBillRecord();
        }
        
        temp->ReadCustDetails(fin);
        temp->ReadUsageInfo(fin);   // polymorphic call to overloaded fn
        BillRecords.push_back(temp);
    }
    
    fin.close();
    return true;
}

// Returns the number of records in BRecs
int BillSystem::GetNumRecs()
{
	return BillRecords.size();
}

 // Displays ith record on screen
void BillSystem::DisplayRec(int i)
{
	BillRecords[i]->DisplayCustDetails(i);
	BillRecords[i]->DisplayUsageInfo();
	cout<<endl;
}
//calculates discouns
void BillSystem::CalDiscounts()
{
    multimap<string, BillRecord*>::iterator RecordItr;
    
    for(int i=0; i<BillRecords.size(); i++) {
        string temp2;
        temp2 = BillRecords[i]->GetSupplier() + BillRecords[i]->GetName() + BillRecords[i]->GetAddress();
        recordsMap.insert(pair<string, BillRecord*>(temp2, BillRecords[i]));
    }
    
    for(RecordItr= recordsMap.begin(); RecordItr != recordsMap.end(); ++RecordItr) {
        // Count how many times a (supplier, name, address) key appears in multimap
        if(recordsMap.count((*RecordItr).first)==3) {
            BillRecord *tempPtr = (*RecordItr).second;
            if(tempPtr->GetSupplier().compare("Dodo")==0) tempPtr->SetDiscount(0.85);
            else if(tempPtr->GetSupplier().compare("Alinta")==0) tempPtr->SetDiscount(0.8);
            discCust.insert(pair<string, string>(tempPtr->GetName(), tempPtr->GetSupplier()));
        }
    }
}

void BillSystem::CalBills()
{
    for(int i=0; i<BillRecords.size(); i++) {
        BillRecords[i]->UpdateBalance();
    }
}

void BillSystem::PrintReport()
{
    cout<<right<<setw(3)<<"# "<<left<<setw(14)<<"Service"<<setw(10)<<"Supplier";
    cout<<setw(20)<<"Customer"<<setw(30)<<"Address"<<right<<setw(10)<<"Bill Amount"<<endl<<endl;
    
    for(int i=0; i<GetNumRecs() && i<10; i++) {
        BillRecord *tempPtr = BillRecords[i];
        cout<<right<<setw(2)<<i+1<<" "<<setw(5)<<tempPtr->BillTypeString();
        cout<<setw(15)<<tempPtr->GetSupplier();
        cout<<setw(17)<<tempPtr->GetName();
        cout<<setw(70)<<tempPtr->GetAddress();
        cout<<right<<setw(85)<<fixed<<setprecision(2)<<tempPtr->GetBillAmount()<<endl;
    }
    cout<<endl;
    
    // Discounted customers
    cout<<left<<setw(24)<<"Discounted Customers"<<setw(10)<<"Supplier"<<endl;
    map<string, string>::iterator iterator;
    iterator = discCust.begin();
    for(;iterator!=discCust.end();iterator++) {
        cout<<setw(40)<<(*iterator).first<<setw(80)<<(*iterator).second<<endl;
    }
}


// ========== class BillSystem Private Function definitions ==========

