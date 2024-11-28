#ifndef BANKMANGEMENTSYSTEM_H_INCLUDED
#define BANKMANGEMENTSYSTEM_H_INCLUDED
#include <iostream>
#include "clsHolderAccount.h"
#include <fstream>
#include <string>
#include "clsBranches.h"
using namespace std;

void AddHolder();
void RemoveHolder(const string &AccountID);

class clsBankMangementSystem
{
private:

    clsHolderAccount *Head;
    string DataFile;
    clsBranchesMangement Branches;
public:
//Constractor
void Menu()
{
    int choice=1;
    bool IsFirstTime=true;
    while(choice != 0)
    {

        if(!IsFirstTime)
        {
            cout<<"\n\nDo you want to make another operation (Y/N) : ";
            string c; cin>>c;
            if(c == "N" || c=="n"|| c=="No"||c=="NO"||c=="no"||c=="nO")
            {   IsFirstTime=true;
                return;
            }
        }
        cout<<"\n1-> Add New Holder";
        cout<<"\n2-> Remove Holder";
        cout<<"\n3-> Display Holder Data";
        cout<<"\n4-> Search For Holder";
        cout<<"\n5-> Update Holder Information";
        cout<<"\n6-> Branches Operations";
        cout<<"\n0-> Exit The Program\n\n";
        cin>>choice;
        switch(choice)
        {
            case 1:
                {
                    IsFirstTime=false;
                    AddHolder();


                }break;
            case 2:
                {
                    cout<<"\nEnter the ID of The Holder : ";
                    string ID; cin>>ID;
                    RemoveHolder(ID);
                    IsFirstTime=false;

                }break;
            case 3:
                {
                    cout<<"\nEnter the ID of The Holder : ";
                    string ID; cin>>ID;
                    DisplayHolderData(ID);
                    IsFirstTime=false;
                }break;

            case 4:
                {
                    cout<<"\n1-> Search by Name";
                    cout<<"\n2-> Search by ID";
                    cout<<"\n3-> Back forword\n";
                    cout<<"\n";

                    int answer; cin>>answer;
                    if(answer == 1)
                    {
                        cout<<"\nEnter The Name : ";
                        string Name; cin>>Name;
                        SerchHolderByName(Name);
                    }
                    else if(answer == 2)
                    {
                        cout<<"\nEnter The ID : ";
                        string ID; cin>>ID;
                        if(IsIdNumberIsUnique(ID))
                        {
                            cout<<"\nThe ID you searching for does not exist";
                            return;
                        }
                        clsHolderAccount * Current =FindAccount(ID);
                        SerchHolderByName(Current->_Name);
                        IsFirstTime=false;
                    }
                }break;
            case 5:
                {
                    cout<<"\nEnter the ID of The Holder : ";
                    string ID; cin>>ID;
                    UpdateHolderInfo(ID);
                    IsFirstTime=false;

                }break;
            case 6:
                {
                    cout<<"\n1-> Add Branch";
                    cout<<"\n2-> Remove Branch by ID";
                    cout<<"\n3-> Display Branch Data";
                    cout<<"\n4-> Search for Branch by ID\n";
                    cout<<"\n";
                    int answer; cin>>answer;
                    if(answer ==1)
                    {
                        string ID,Name,Location;
                        cout<<"\nEnter Branch Name : "; cin>>Name;
                        cout<<"\nEnter Branch ID : "; cin>>ID;
                        cout<<"\nEnter Branch Location : "; cin>>Location;
                        clsBranch NewBranch(ID,Name,Location);
                        Branches.AddBranch(NewBranch);
                        IsFirstTime=false;

                    }
                    else if(answer ==2)
                    {

                        string ID;
                        cout<<"\n Enter Branch ID : "; cin>>ID;

                        if(!Branches.FindBranchByID(ID))
                        {
                            cout<<"\nThere is no such Branch with this ID";
                            IsFirstTime=false;
                            return ;
                        }
                        Branches.RemoveBranchByID(ID);
                        cout<<"\nBranch Deleted Sucessfully !";
                        IsFirstTime=false;

                    }
                    else if (answer ==3)
                    {
                        string ID;
                        cout<<"\n Enter Branch ID--- : "; cin>>ID;
                        clsBranch* branch = Branches.FindBranchByID(ID);

                        if(branch != NULL)
                        {
                            branch->DisplayBranchInfo();
                            IsFirstTime=false;

                            cout << "Branch ID: " << branch->_BranchID
                                      << "\nBranch Name: " << branch->_BranchName
                                      << "\nBranch Location:"<<branch->_BranchLocation
                                      << "\nAccounts in Branch:\n";

                            if (branch->_AccountIDs.empty())
                            {
                                cout << "No accounts linked to this branch.\n";

                            }
                            else
                            {
                                for (const auto& AccountID : branch->_AccountIDs)
                                {

                                    DisplayHolderData(AccountID);
                                    cout<<"\n--------------------\n";
                                }

                            }


                        }
                        else
                        {
                            cout << "No branch found with ID: " << ID << endl;
                        }

                    }
                    else if (answer ==4)
                    {
                        string ID;
                        cout<<"\nEnter Branch ID : "; cin>>ID;
                        clsBranch* branch = Branches.FindBranchByID(ID);
                        if(branch)
                        {
                            cout<<"\nThe Branch is Exist !";
                            branch->DisplayBranchInfo();
                        }
                        else
                        {
                            cout<<"\nThere is no Branch with such ID";
                            //return; -> dont use it it will end the program

                        }

                    }

                    IsFirstTime=false;

                }break;
            case 0:
                {
                    return;
                }break;
         }

    }

}
 clsBankMangementSystem()
{
    Head=NULL;
    DataFile="DataAccounts.txt";
    clsBranch branch1("101", "Maadi", "Cairo");
    clsBranch branch2("102", "6October", "Giza");
    clsBranch branch3("103", "Benha", "Qaluobia");
    clsBranch branch4("104", "Tanta", "Garbia");


    Branches.AddBranch(branch1);
    Branches.AddBranch(branch2);
    Branches.AddBranch(branch3);
    Branches.AddBranch(branch4);

    Menu();



}
void SaveDataToFileText()
{
    ofstream outputFile(DataFile, ios::out);

    if (!outputFile) {
        cout << "Error: Could not open file for writing!" << endl;
        return;
    }

    clsHolderAccount *current = Head;

    // Write data for each account
    while (current != nullptr)
    {
        outputFile << current->_AccountID << ","
                   << current->_Name << ","
                   << current->_Address << ","
                   << current->_Email << ","
                   << current->_PhoneNumber << ","
                   << current->_AccountBalance << ","
                   << current->_PINCode << endl;
        current = current->Next;
    }

    outputFile.close();
    cout << "\nData saved to " << DataFile << " successfully!" << endl;
}


    bool IsIdNumberIsUnique(const string &AccountID)
    {
        clsHolderAccount* Current = Head;

        if (Current == NULL)
        {
            return true;
        }

        while (Current != NULL)
        {
            if (Current->_AccountID == AccountID)
                return false;

            Current = Current->Next;
        }

        return true;

    }
    void AddHolder()
    {
        clsHolderAccount *NewAccount = new clsHolderAccount();

        cout<<"\nEnter Branch ID ";
        Branches.DisplayAllBranchesIDsAndNames();


        cin.ignore(1,'\n');
        cin>>NewAccount->_Branch._ID;
        clsBranch* branch = Branches.FindBranchByID(NewAccount->_Branch._ID);
        if(!branch)
        {
            cout<<"\nThere is no such Branch with this ID";
            delete NewAccount;
            return ;
        }

        cin.ignore(1,'\n');
        cout << "\nEnter Account ID : ";

        getline(cin,NewAccount->_AccountID);
        branch->AddAccount(NewAccount->_AccountID); // if its found branch
        NewAccount->Next = NULL;





        if (IsIdNumberIsUnique(NewAccount->_AccountID))
        {
            cout << "Account Name     : ";

            cin.ignore(1,'\n');
            getline(cin,NewAccount->_Name);
            cout << "Account Address  : ";

            //cin.ignore(1,'\n');
            getline(cin,NewAccount->_Address);


            cout << "Account Email    : ";
            getline(cin,NewAccount->_Email);


            cout << "Account Phone    : ";
            getline(cin,NewAccount->_PhoneNumber);


            cout << "Account Balance  : ";
            cin >> NewAccount->_AccountBalance;

            cout << "Account PIN Code : ";
            cin.ignore(1,'\n');
            getline(cin,NewAccount->_PINCode);

            if (Head == NULL)
            {
                Head = NewAccount;
            }
            else
            {
                clsHolderAccount *Current = Head;
                while (Current->Next != NULL)
                {
                    Current = Current->Next;
                }
                Current->Next = NewAccount;
            }
            cout<<"\n============================";
            cout << "\n Account Added Successfully!";
            cout<<"\n============================";
            SaveDataToFileText();

        }
        else
        {
            cout << "\nAccount Already Exists. Please try another ID.";
            delete NewAccount;
        }

    }
    void RemoveHolder(const string &AccountID)
    {
        if(!IsIdNumberIsUnique(AccountID))
        {


            clsHolderAccount *CurrentDelPtr=Head , * Previous =Head;
            //Empty
            if(Head ==NULL)
            {   cout<<"\nThere is no Holders in the Data Base";
                return;
            }
            //Delete First
            if(CurrentDelPtr->_AccountID ==AccountID)
            {
                Head=CurrentDelPtr->Next;
                delete CurrentDelPtr;
                cout << "\nAccount Removed Successfully!";
                return;
            }
            //Serch for Node we want to delete
            while(CurrentDelPtr != NULL && CurrentDelPtr->_AccountID!= AccountID)
            {
                Previous=CurrentDelPtr;
                CurrentDelPtr=CurrentDelPtr->Next;

            }

            if (CurrentDelPtr == NULL)
            {
                cout << "\nThis Account doesn't exist.";
                return;
            }

            //link prev by the next of the current we want to delete
            Previous->Next=CurrentDelPtr->Next;
            delete CurrentDelPtr;
            cout << "\nAccount Removed Successfully!";


        }else {cout<<"\nThis Account dosen't Exist ";}

    }
    clsHolderAccount* FindAccount(const string &AccountID)
    {
        clsHolderAccount * Current = Head;
        while(Current !=NULL)
        {
            if(Current->_AccountID == AccountID)
            {
                return Current;
            }
            Current=Current->Next;
        }
        return NULL;

    }
    void DisplayHolderData(const string &AccountID)
    {
        clsHolderAccount * Current = FindAccount(AccountID);
        if(Current == NULL)
        {
            cout<<"\nThis ID does not Exist";
        }else
        {
            cout<<"\nAccount Name      : "<<Current->_Name;
            cout<<"\nAccount ID        : "<<Current->_AccountID;
            cout<<"\nAccount Address   : "<<Current->_Address;
            cout<<"\nAccount Email     : "<<Current->_Email;
            cout<<"\nAccount Phone     : "<<Current->_PhoneNumber;
            cout<<"\nAccount Balance   : "<<Current->_AccountBalance;
            cout<<"\nAccount PIN Code  : "<<Current->_PINCode;

            //We have ID not Name so here is to find Name
            clsBranch * FoundBranch = Branches.FindBranchByID(Current->_Branch._ID);

            cout<<"\nAccount Branch    : "<<FoundBranch->_BranchName;
        }

    }
    void SerchHolderByName(const string &AccountName)
    {
            clsHolderAccount * Current = Head;

            while(Current != NULL)
            {
                if(Current->_Name == AccountName)
                {
                    cout<<"\nAccount of ID  "<<Current->_AccountID<<" is  found !!";
                    cout<<"\n\n--[Account Operations]-- " ;
                    cout<<"\n\n1- Display Data Account ";
                    cout<<"\n2- Remove Account";
                    cout<<"\n3- Set New PIN Code";
                    cout<<"\n4- Exit \n";

                    int Choice; cin>>Choice;
                    switch(Choice)
                    {
                        case 1:
                            {
                                DisplayHolderData(Current->_AccountID);
                                return ;
                            }break;
                        case 2:
                            {
                                RemoveHolder(Current->_AccountID);
                                return;
                            }break;
                        case 3:
                            {
                                string NewPinCode;
                                cout<<"\nEnter the new PIN Code : ";
                                cin>>NewPinCode;
                                Current->_PINCode=NewPinCode;
                                cout<<"\nPIN code has been sucessfully updated";
                                SaveDataToFileText();

                                return;
                            }break;

                        case 0:
                            return;
                            break;

                    }

                }
                Current=Current->Next;
            }
            cout<<"\nThere is no account with such name";


        }
    void UpdateHolderInfo(const string &AccountID)
    {
        clsHolderAccount* Current= FindAccount(AccountID);
        if(Current ==NULL)
        {
            cout<<"\nThis Holder Information does not exist";
            return;
        }

        int Choice=1;
        while(Choice != 0)
        {
            cout<<"\n\n1- Update Name";
            cout<<"\n2- Update Phone";
            cout<<"\n3- Update Email";
            cout<<"\n4- Update Address";
            cout<<"\n5- Update PIN Code ";
            cout<<"\n0- Exit \n";
            cin>>Choice;
            switch(Choice)
            {
                case 1:
                    {
                        string Name;
                        cout<<"\nEneter the new Name : ";
                        cin>>Name;
                        Current->_Name=Name;
                        cout<<"\nName has Updated";
                    }break;
                case 2:
                    {
                        string Phone;
                        cout<<"\nEneter the new Phone Number : ";
                        cin>>Phone;
                        Current->_PhoneNumber=Phone;
                        cout<<"\nPhone Number has been Updated";
                    }break;
                case 3:
                    {
                        string Email;
                        cout<<"\nEneter the new Email : ";
                        cin>>Email;
                        Current->_Email=Email;
                        cout<<"\nEmail has been Updated";
                    }break;

                case 4:
                    {
                        string Address;
                        cout<<"\nEneter the new Address : ";
                        cin>>Address;
                        Current->_Address=Address;
                        cout<<"\nAddress has been Updated";
                    }break;
                case 5:
                    {
                        string PinCode;
                        cout<<"\nEneter the new PIN Code : ";
                        cin>>PinCode;
                        Current->_PINCode=PinCode;
                        cout<<"\PIN Code has been Updated";

                    }break;
                case 0:
                    {
                        return;
                    }break;
             }

        }

    }

};

#endif // BANKMANGEMENTSYSTEM_H_INCLUDED




