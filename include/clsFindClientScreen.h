#pragma once
#include "clsScreen.h"
#include "MyInputLibrary.h"
#include "clsBankClient.h"
class clsFindClientScreen : protected clsScreen
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
    static void ShowFindClientScreen()
    {
        system("cls");
        _PrintHeader("Find Client Screen");
        _Print(""); std::string AccountNumber = MyInputLibrary::ReadLine("Enter Account Number: ");
        clsBankClient client = clsBankClient::FindClient(AccountNumber);
        while (client.IsEmpty()) {
            _Print("Client with Account Number " + AccountNumber + " not found.\n");
            _Print("\n"); _Print("Enter a Valid Account Number: ");
            AccountNumber = MyInputLibrary::ReadLine("");
            client = clsBankClient::FindClient(AccountNumber);
        }

        _PrintClientCard(client);
    }
};

