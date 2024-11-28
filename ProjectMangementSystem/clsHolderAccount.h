#ifndef CLSHOLDERACCOUNT_H
#define CLSHOLDERACCOUNT_H

#include <iostream>

using namespace std;

class clsHolderAccount {
public:
    string _Name;
    string _Address;
    string _Email;
    string _PhoneNumber;
    string _AccountID;
    string _PINCode;
    double _AccountBalance;
    struct Branch
    {
        string _ID;
        string _BName;
    };
    Branch _Branch;
    clsHolderAccount *Next;

    clsHolderAccount()
    {
        Next=NULL;
    };

    clsHolderAccount(string BranchID,string Name ,string Address,
    string Email,string PhoneNumber,string AccountID,string PINCode,
    double AccountBalance)
    {
        _Branch._ID = BranchID;
        _Name = Name;
        _Address = Address;
        _Email = Email;
        _PhoneNumber = PhoneNumber;
        _AccountID = AccountID;
        _PINCode = PINCode;
        _AccountBalance = AccountBalance;
         Next = NULL;

    }

};

#endif // CLSHOLDERACCOUNT_H
