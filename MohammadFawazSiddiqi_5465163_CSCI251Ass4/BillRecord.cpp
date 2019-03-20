/**********************************************************************
 * BillRecord.cpp - CSCI251 - Ass4 - BillRecord class definition
 * Mohammad Fawaz Siddiqi 5465163/mfs995 23/12/2018
 **********************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include "BillRecord.h"
using namespace std;

// ========== class BillRecord function definitions ==========

// Default constructor
BillRecord::BillRecord()
{

}

// Reads customer details part of record from file
bool BillRecord::ReadCustDetails(ifstream &fin)
{
    fin>>Supplier;
    fin.ignore(2, '\n');
    getline(fin, Name,'\n');
    getline(fin, Address, '\n');
    fin>>accBal>>DaysSinceLastReading;
    return true;
}

// Displays customer details part of record on screen
void BillRecord::DisplayCustDetails(int i)
{
	//display customer details (only) from private data members
    cout<<right<<setw(2)<<i+1<<" ";
    cout<<left<<setw(8)<<Supplier<<setw(20)<<Name<<setw(30)<<Address;
    cout<<right<<setw(10)<<accBal<<setw(10) << "Days: " <<DaysSinceLastReading;
}

// Virtual fn for reading usage info part of record from file in derived classes
bool BillRecord::ReadUsageInfo(ifstream &fin)
{
	return true;
}


// virtual fn for displays usage info part of record in derived classes
void BillRecord::DisplayUsageInfo()
{
}

string BillRecord::GetSupplier() {
    return Supplier;
}
string BillRecord::GetName() {
    return Name;
}
string BillRecord::GetAddress() {
    return Address;
}
float BillRecord::GetDiscount() {
    return Discount;
}
float BillRecord::GetBillAmount() {
    return BillAmount;
}
string BillRecord::BillTypeString()
{
    
    if(typeid(*this) == typeid(GasBillRecord)) {
        return "Gas";
    }
    else if(typeid(*this) == typeid(ElectBillRecord)) {
        return "Elect";
    }
    else if(typeid(*this) == typeid(PhoneBillRecord)) {
        return "Phone";
    }
    else{
        return "Unknown Type";
    }
}
void BillRecord::SetDiscount(float discount) {
    Discount = discount;
}
// ========== Derived Class function definitions ==========


// write the function definitions of the derived classes here
bool ElectBillRecord::ReadUsageInfo(ifstream &fin)
{
    fin>>prevReading>>currReading>>rate1>>rate1Thr>>rate2>>suppCharge;
    return true;
}

void ElectBillRecord::DisplayUsageInfo()
{
    cout<<"\n"<<setw(17)<<" "<<"(Previous Reading: " <<prevReading<<", " << "Current Reading: " <<currReading<<" ";
    cout<<"R1: "<<rate1<<" R1Th: "<<rate1Thr<<" ";
    cout<<"R2: "<<rate2<<" SuppC: "<<suppCharge<<")";
}

void ElectBillRecord::UpdateBalance()
{
    float c = currReading - prevReading;
    double p = suppCharge * DaysSinceLastReading;
    if(BillAmount == (c<=rate1Thr)) {
        (c*rate1+p)*Discount - accBal;
    }
    else{
        (rate1Thr*rate1+(c-rate1Thr)*rate2+p) * Discount - accBal;
    }
}

/******************** GasBillRecord FUNC DEFINITIONS ********************/
bool GasBillRecord::ReadUsageInfo(ifstream &fin)
{
    fin>>prevReading>>currReading>>heatValue>>rate>>suppCharge; return true;
}

void GasBillRecord::DisplayUsageInfo()
{
    cout<<endl<<setw(17)<<" "<<"(Previous Reading: " <<prevReading<<", " << "Current Reading: " <<currReading<<" ";
    cout<<"HV: "<<heatValue<<" ";
    cout<<"Rate: "<<rate<<" ";
    cout<<"SuppC: "<<suppCharge<<")";
}

void GasBillRecord::UpdateBalance()
{
    float c = currReading - prevReading;
    double p = suppCharge * DaysSinceLastReading;
    BillAmount = (c * heatValue * rate) * Discount - accBal;
}

/******************** PhoneBillRecord FUNCTION DEFINITIONS ********************/
bool PhoneBillRecord::ReadUsageInfo(ifstream &fin)
{
    fin>>numLocalCalls>>rateLocalCalls>>longDistCall>>rateLongDistCall>>lineRent;
    return true;
}

void PhoneBillRecord::DisplayUsageInfo()
{
    cout<<"\n"<<setw(17)<<" "<<"(LCalls: "<<numLocalCalls<<", "<<rateLocalCalls<<" ";
    cout<<"DCalls: "<<longDistCall<<", "<<rateLongDistCall<<" ";
    cout<<"Rental: "<<lineRent<<")";
}

void PhoneBillRecord::UpdateBalance()
{
    float l = rateLocalCalls * numLocalCalls;
    float d = rateLongDistCall * longDistCall;
    float p = lineRent * DaysSinceLastReading;
    BillAmount = (l + d + p) * Discount - accBal;
}
