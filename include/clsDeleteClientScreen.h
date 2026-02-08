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
        clsScreen::Print("\n");
        clsScreen::Print("        Client Card\n");
        clsScreen::Print("=============================\n");
        clsScreen::Print("First Name   : " + client.FirstName + "\n");
        clsScreen::Print("Last Name    : " + client.LastName + "\n");
        clsScreen::Print("Email        : " + client.Email + "\n");
        clsScreen::Print("Phone        : " + client.Phone + "\n");
        clsScreen::Print("Account No.  : " + client.AccountNumber + "\n");
        clsScreen::Print("Pincode      : " + client.Pincode + "\n");
        clsScreen::Print("Balance      : " + to_string(client.Balance) + "\n");
        clsScreen::Print("=============================\n\n");
    }

public:
    static void ShowDeleteClienScreen()
    {
        clsScreen::_PrintHeader("Delete Client Screen");
        clsScreen::Print("");   // shifting line for better output format
        std::string AccountNumber = MyInputLibrary::ReadLine("Enter Account Number of the client to delete: ");
        clsBankClient client = clsBankClient::FindClient(AccountNumber);

        while(client.IsEmpty())
        {
            clsScreen::Print("Client with Account Number " + AccountNumber + " not found.\n");
            clsScreen::Print("");      AccountNumber = MyInputLibrary::ReadLine("Enter Account Number of the client to delete: ");
            client = clsBankClient::FindClient(AccountNumber);
        }
        
        _Print(client);

        clsScreen::Print("");
        if (! MyInputLibrary::ReadYesNo("Are you sure you want to delete this client? (Y/N): "))
            return;
        
        if (client.Delete())
            clsScreen::Print("Client deleted successfully.\n");
        else 
            clsScreen::Print("Failed to delete client.\n");
    }



};

