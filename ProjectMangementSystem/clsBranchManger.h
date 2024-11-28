#ifndef CLSBRANCHMANGER_H_INCLUDED
#define CLSBRANCHMANGER_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
#include "clsBranches.h"
class clsBranchManager {
private:
    map<string, clsBranch> _Branches;

public:
    // Add a new branch
    void AddBranch(const string& BranchID, const string& BranchName)
    {
        if (_Branches.find(BranchID) == _Branches.end())
        {
            _Branches[BranchID] = clsBranch(BranchID, BranchName);
            cout << "Branch added successfully!" << endl;
        }
        else
        {
            cout << "Branch with ID " << BranchID << " already exists!" << endl;
        }
    }

    bool AddAccountToBranch(const string& BranchID, const string& AccountID)
    {
        auto it = _Branches.find(BranchID); //ietration
        if (it != _Branches.end())
        {
            it->second.AddAccount(AccountID);
            return true;
        }
        cout << "Branch ID " << BranchID << " not found!" << endl;
        return false;
    }

    bool RemoveAccountFromBranch(const string& BranchID, const string& AccountID)
    {
        auto it = _Branches.find(BranchID);

        if (it != _Branches.end())
        {
            if (it->second.RemoveHolder(AccountID))
            {
                cout << "Account removed successfully!" << endl;
                return true;
            } else {
                cout << "Account ID " << AccountID << " not found in branch " << BranchID << "!" << endl;
                return false;
            }
        }
        cout << "Branch ID " << BranchID << " not found!" << endl;
        return false;
    }

    // Display all branches
    void DisplayAllBranches() const
    {
        if (_Branches.empty())
        {
            cout << "No branches available!" << endl;
            return;
        }
        for (const auto& pair : _Branches)
        {
            pair.second.DisplayBranchInfo();
            cout << "--------------------" << endl;
        }
    }

    // Find a branch by its ID
    clsBranch* FindBranchByID(const string& BranchID)
    {
        auto it = _Branches.find(BranchID);
        if (it != _Branches.end())
        {
            return &it->second;
        }
        return nullptr;
    }
};



#endif // CLSBRANCHMANGER_H_INCLUDED
