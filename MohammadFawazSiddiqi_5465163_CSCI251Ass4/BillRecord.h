/**********************************************************************
 * BillRecord.h - CSCI251 - Ass4 - BillRecord class declaration
 * Mohammad Fawaz Siddiqi 5465163/mfs995 23/12/2018
 **********************************************************************/
#ifndef BILLRECORD_H
#define BILLRECORD_H

#include <string>
using namespace std;

enum BillType {eElect, eGas, ePhone};

// base class...

class BillRecord {
    
public:
    BillRecord();
    bool ReadCustDetails(ifstream &fin);
    void DisplayCustDetails(int);
    string GetSupplier();
    string GetName();
    string GetAddress();
    float GetDiscount();
    float GetBillAmount();
    string BillTypeString();
    void SetDiscount(float);
    virtual bool ReadUsageInfo(ifstream &fin) = 0;
    virtual void DisplayUsageInfo() = 0;
    virtual void UpdateBalance() = 0;
private:
    BillType BType;
    string Supplier; // Supplier's name
    string Name, Address; // Customer's name and address
protected:
    float BillAmount;// Amount in dollars and cents of this bill
    float Discount;
    int DaysSinceLastReading; // Days since last reading
    double accBal; // Customer's account balance
};

//derived classes...

// declare your derived classes here
class ElectBillRecord : public BillRecord {
    
public:
    bool ReadUsageInfo(ifstream &fin);
    void DisplayUsageInfo();
    void UpdateBalance();
private:
    float prevReading, currReading;
    double rate1, rate1Thr, rate2;
    double suppCharge;
};

class PhoneBillRecord : public BillRecord {
    
public:
    bool ReadUsageInfo(ifstream &fin);
    void DisplayUsageInfo();
    void UpdateBalance();
private:
    double numLocalCalls;
    float rateLocalCalls;
    double longDistCall;
    float rateLongDistCall;
    float lineRent;
};

class GasBillRecord : public BillRecord {
    
public:
    bool ReadUsageInfo(ifstream &fin);
    void DisplayUsageInfo();
    void UpdateBalance();
private:
    float prevReading, currReading;
    double heatValue;
    float rate, suppCharge;
};
#endif

