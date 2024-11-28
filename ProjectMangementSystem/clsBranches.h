#ifndef CLSBRANCH_H_INCLUDED
#define CLSBRANCH_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "clsBankMangementSystem.h"
using namespace std;
void DisplayHolderData(const string &AccountID);

class clsBranch
{
public:
    string _BranchID;
    string _BranchName;
    string _BranchLocation;
    vector<string> _AccountIDs;


    clsBranch(string id, string name, string location)
    {
        _BranchID = id;
        _BranchName = name;
        _BranchLocation = location;
    }

    // Getters
    string GetBranchID() const
    {
        return _BranchID;
    }

    string GetBranchName() const
    {
        return _BranchName;
    }
    vector<string> GetAccountIDs() const
    {
         return _AccountIDs;
    }

    // Add an Account to the Branch
    void AddAccount(string AccountID)
    {
        _AccountIDs.push_back(AccountID);
    }

    // Display Branch Information
    void DisplayBranchInfo() const
    {
        cout << "\nBranch ID : " << _BranchID
              << "\nBranch Name : " << _BranchName
                << "\nBranch Location : "<<_BranchLocation;


    }
};

class clsBranchesMangement
{
private:
    vector<clsBranch> _Branches;
public:
    // Method to add a branch
    void AddBranch(clsBranch branch)
    {
        _Branches.push_back(branch);
    }
    // Method to remove a branch by ID
    bool RemoveBranchByID(string BranchID)
    {
        for (int i = 0; i < _Branches.size(); i++)
        {
            if (_Branches[i]._BranchID == BranchID)
            {
                _Branches.erase(_Branches.begin() + i);
                return true;
            }
        }
        return false;
    }

    // Method to find a branch by ID
    clsBranch* FindBranchByID(string BranchID)
    {
        for (int i = 0; i < _Branches.size(); i++)
        {
            if (_Branches[i]._BranchID == BranchID)
            {
                return &_Branches[i];
            }
        }
        return nullptr;
    }

    // Method to display all branches
    void DisplayAllBranches()
    {
        if (_Branches.size() == 0)
        {
            cout << "No branches available." << endl;
        }
        else
        {
            for (int i = 0; i < _Branches.size(); i++)
            {
                _Branches[i].DisplayBranchInfo();
                cout << "----------------------------" << endl;
            }
        }
    }
    void DisplayAllBranchesIDsAndNames()
    {
        if (_Branches.empty())
        {
            cout << "No branches available." << endl;
        }
        else
        {
            cout<<" [ ";
            for (int i = 0; i < _Branches.size(); i++)
            {
                cout<<_Branches[i]._BranchName<<":"<<_Branches[i]._BranchID<<" | ";
            }
            cout<<" ] ";

        }
    }

    // Method to display a branch by ID
    void DisplayBranchByID(string BranchID)
    {
        clsBranch* branch = FindBranchByID(BranchID);
        if (branch != nullptr)
        {
            branch->DisplayBranchInfo();
        }
        else
        {
            cout << "Branch with ID " << BranchID << " not found." << endl;
        }
    }
    void DisplayBranchesForChoseing()
    {

    }
};

#endif // CLSBRANCH_H_INCLUDED
