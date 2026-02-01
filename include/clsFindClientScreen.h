#pragma once
#include "clsScreen.h"
#include "MyInputLibrary.h"
#include "clsBankClient.h"
class clsFindClientScreen : protected clsScreen
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
    static void ShowFindClientScreen()
    {
        clsScreen::_PrintHeader("Find Client Screen");
        clsScreen::Print(""); std::string AccountNumber = MyInputLibrary::ReadLine("Enter Account Number: ");
        clsBankClient client = clsBankClient::FindClient(AccountNumber);
        while (client.IsEmpty()) {
            clsScreen::Print("Client with Account Number " + AccountNumber + " not found.\n");
            clsScreen::Print("");
            AccountNumber = MyInputLibrary::ReadLine("Enter a Valid Account Number: ");
            client = clsBankClient::FindClient(AccountNumber);
        }

        _Print(client);
    }
};

