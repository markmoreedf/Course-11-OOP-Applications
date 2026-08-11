#pragma once
#include <iostream>
#include "clsScreen.h"
#include "MyInputLibrary.h"
#include "clsBankClient.h"

class clsDeleteClientScreen :protected clsScreen
{
private:
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
    static void ShowDeleteClienScreen()
    {
        _PrintHeader("Delete Client Screen");
        Print("");   // shifting line for better output format
        std::string AccountNumber = MyInputLibrary::ReadLine("Enter Account Number of the client to delete: ");
        clsBankClient client = clsBankClient::FindClient(AccountNumber);

        while(client.IsEmpty())
        {
            Print("Client with Account Number " + AccountNumber + " not found.\n\n");
            Print("");      AccountNumber = MyInputLibrary::ReadLine("Enter Account Number of the client to delete: ");
            client = clsBankClient::FindClient(AccountNumber);
        }
        
        _Print(client);

        Print("");
        if (! MyInputLibrary::ReadYesNo("Are you sure you want to delete this client? (Y/N): "))
            return;
        
        if (client.Delete())
            Print("Client deleted successfully.\n");
        else 
            Print("Failed to delete client.\n");
    }



};

