#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "MyInputLibrary.h"

class clsAddNewClientScreen :protected clsScreen
{
private:
    static void _ReadClientData(clsBankClient& client)
    { 
    _Print("Please enter the following client data:\n\n") ;
    _Print("");  client.FirstName = MyInputLibrary::ReadLine("First Name: ");
    _Print("");  client.LastName = MyInputLibrary::ReadLine("Last Name: ");
    _Print("");  client.Email = MyInputLibrary::ReadLine("Email: ");
    _Print("");  client.Phone = MyInputLibrary::ReadLine("Phone: ");
    _Print("");  client.Pincode = MyInputLibrary::ReadLine("Pin Code: ");
    _Print("");  client.Balance = MyInputLibrary::ReadPositiveDouble("Balance: ");
    }

    static void _PrintClientCard(clsBankClient& client)
    {
        _Print("\n");
        _Print("        Client Card\n");
        _Print("=============================\n");
        _Print("First Name   : " + client.FirstName + "\n");
        _Print("Last Name    : " + client.LastName + "\n");
        _Print("Email        : " + client.Email + "\n");
        _Print("Phone        : " + client.Phone + "\n");
        _Print("Account No.  : " + client.AccountNumber + "\n");
        _Print("Pincode      : " + client.Pincode + "\n");
        _Print("Balance      : " + to_string(client.Balance) + "\n");
        _Print("=============================\n\n");
    }

public: 
    static void AddNewClientScreen()
    {
        _PrintHeader("Add New Client Screen");
        _Print("");
        string AccountNumber = MyInputLibrary::ReadLine("Enter New Account Number: ");
        while (clsBankClient::IsClientExist(AccountNumber))
        {
            _Print("Account Number already exists. Please enter a different one.\n");
            _Print("");
            AccountNumber = MyInputLibrary::ReadLine("Enter New Account Number: ");
        }
        clsBankClient newClient = clsBankClient::GetAddNewClientObject(AccountNumber);
        _ReadClientData(newClient);

        _PrintClientCard(newClient);
        _Print(""); // just to allign the msg of the next line
        if (! MyInputLibrary::ReadYesNo("Do you want to add this client? (Y/N): "))
        {
            _Print("Operation cancelled. Client not added.\n");
            return;
        }

        clsBankClient::enSaveResults saveResult = newClient.Save();
        switch (saveResult)
        {
        case clsBankClient::svFailedEmptyObject:
            _Print("Failed to add new client. Empty object.\n");
            break;
        case clsBankClient::svSucceeded:
            _Print("New client added successfully.\n");
            break;
        case clsBankClient::svAccountNumberExists:
            _Print("Account Number already exists. Cannot add new client.\n");
            break;
        }
     
    }
};

