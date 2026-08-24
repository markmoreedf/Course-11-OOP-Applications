#pragma once
#include <iostream>
#include "clsScreen.h"
#include "MyInputLibrary.h"
#include "clsBankClient.h"

class clsDeleteClientScreen :protected clsScreen
{
private:
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
    static void ShowDeleteClienScreen()
    {
        _PrintHeader("Delete Client Screen");
        _Print("");   // shifting line for better output format
        std::string AccountNumber = MyInputLibrary::ReadLine("Enter Account Number of the client to delete: ");
        clsBankClient client = clsBankClient::FindClient(AccountNumber);

        while(client.IsEmpty())
        {
            _Print("Client with Account Number " + AccountNumber + " not found.\n\n");
            _Print("");      AccountNumber = MyInputLibrary::ReadLine("Enter Account Number of the client to delete: ");
            client = clsBankClient::FindClient(AccountNumber);
        }
        
        _PrintClientCard(client);

        _Print("");
        if (! MyInputLibrary::ReadYesNo("Are you sure you want to delete this client? (Y/N): "))
            return;
        
        if (client.Delete())
            _Print("Client deleted successfully.\n");
        else 
            _Print("Failed to delete client.\n");
    }



};

