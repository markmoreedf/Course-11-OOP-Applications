#pragma once
#include "clsScreen.h"
#include "MyInputLibrary.h"
#include "clsBankClient.h"
class clsFindClientScreen : protected clsScreen
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
    static void ShowFindClientScreen()
    {
        _PrintHeader("Find Client Screen");
        Print(""); std::string AccountNumber = MyInputLibrary::ReadLine("Enter Account Number: ");
        clsBankClient client = clsBankClient::FindClient(AccountNumber);
        while (client.IsEmpty()) {
            Print("Client with Account Number " + AccountNumber + " not found.\n");
            Print("\n"); Print("Enter a Valid Account Number: ");
            AccountNumber = MyInputLibrary::ReadLine("");
            client = clsBankClient::FindClient(AccountNumber);
        }

        _Print(client);
    }
};

