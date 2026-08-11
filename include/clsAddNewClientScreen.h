#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "MyInputLibrary.h"

class clsAddNewClientScreen :protected clsScreen
{
private:
    static void _ReadClientData(clsBankClient& client)
    { 
    Print("Please enter the following client data:\n\n") ;
    Print("");  client.FirstName = MyInputLibrary::ReadLine("First Name: ");
    Print("");  client.LastName = MyInputLibrary::ReadLine("Last Name: ");
    Print("");  client.Email = MyInputLibrary::ReadLine("Email: ");
    Print("");  client.Phone = MyInputLibrary::ReadLine("Phone: ");
    Print("");  client.Pincode = MyInputLibrary::ReadLine("Pin Code: ");
    Print("");  client.Balance = MyInputLibrary::ReadPositiveDouble("Balance: ");
    }

    static void _Print(clsBankClient& client)
    {
        Print("\n");
        Print("        Client Card\n");
        Print("=============================\n");
        Print("First Name   : " + client.FirstName + "\n");
        Print("Last Name    : " + client.LastName + "\n");
        Print("Email        : " + client.Email + "\n");
        Print("Phone        : " + client.Phone + "\n");
        Print("Account No.  : " + client.AccountNumber + "\n");
        Print("Pincode      : " + client.Pincode + "\n");
        Print("Balance      : " + to_string(client.Balance) + "\n");
        Print("=============================\n\n");
    }

public: 
    static void AddNewClientScreen()
    {
        _PrintHeader("Add New Client Screen");
        Print("");
        string AccountNumber = MyInputLibrary::ReadLine("Enter New Account Number: ");
        while (clsBankClient::IsClientExist(AccountNumber))
        {
            Print("Account Number already exists. Please enter a different one.\n");
            Print("");
            AccountNumber = MyInputLibrary::ReadLine("Enter New Account Number: ");
        }
        clsBankClient newClient = clsBankClient::GetAddNewClientObject(AccountNumber);
        _ReadClientData(newClient);

        _Print(newClient);
        Print(""); // just to allign the msg of the next line
        if (! MyInputLibrary::ReadYesNo("Do you want to add this client? (Y/N): "))
        {
            Print("Operation cancelled. Client not added.\n");
            return;
        }

        clsBankClient::enSaveResults saveResult = newClient.Save();
        switch (saveResult)
        {
        case clsBankClient::svFailedEmptyObject:
            Print("Failed to add new client. Empty object.\n");
            break;
        case clsBankClient::svSucceeded:
            Print("New client added successfully.\n");
            break;
        case clsBankClient::svAccountNumberExists:
            Print("Account Number already exists. Cannot add new client.\n");
            break;
        }
     
    }
};

