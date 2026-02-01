#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "MyInputLibrary.h"

class clsUpdateClientScreen :
    public clsScreen
{
private:
    static void _Print(clsBankClient & client) 
    {
        clsScreen::Print("\n");
       clsScreen::Print( "        Client Card\n");
       clsScreen::Print( "=============================\n");
       clsScreen::Print("First Name   : " + client.FirstName + "\n");
       clsScreen::Print("Last Name    : " + client.LastName + "\n");
       clsScreen::Print("Email        : " + client.Email + "\n");
       clsScreen::Print("Phone        : " + client.Phone + "\n");
       clsScreen::Print("Account No.  : " + client.AccountNumber + "\n");
       clsScreen::Print("Pincode      : " + client.Pincode + "\n");
       clsScreen::Print("Balance      : " + to_string(client.Balance) + "\n");
       clsScreen::Print("=============================\n\n");
    }

private:
    static void _ReadClientData(clsBankClient& client)
    {
        clsScreen::Print("Please enter the following client data:\n");
        clsScreen::Print("");  client.FirstName = MyInputLibrary::ReadLine("First Name: ");
        clsScreen::Print("");  client.LastName = MyInputLibrary::ReadLine("Last Name: ");
        clsScreen::Print("");  client.Email = MyInputLibrary::ReadLine("Email: ");
        clsScreen::Print("");  client.Phone = MyInputLibrary::ReadLine("Phone: ");
        clsScreen::Print("");  client.Pincode = MyInputLibrary::ReadLine("Pin Code: ");
        clsScreen::Print("");  client.Balance = MyInputLibrary::ReadPositiveDouble("Balance: ");

    }


public:
    static void UpdateClientScreen()
    {
        system("cls");
        clsScreen::_PrintHeader("Update Client Data Screen");
        clsScreen::Print("");
        string AccountNumber = MyInputLibrary::ReadLine("Enter Account number of the client to update: ");
        clsBankClient client = clsBankClient::FindClient(AccountNumber);
        
        while (client.IsEmpty()) {
            clsScreen::Print("Client with Account Number " + AccountNumber + " not found.\n");
            clsScreen::Print("");
            AccountNumber = MyInputLibrary::ReadLine("Enter Account number of the client to update: ");
            client = clsBankClient::FindClient(AccountNumber);
        }
        clsScreen::Print("\nCurrent Client Data:\n");
         // 
        _Print(client);
        
        clsScreen::Print("Please enter new data for the client:\n");
        _ReadClientData(client);
        
        clsBankClient::enSaveResults saveResult = client.Save();
        if (saveResult == clsBankClient::svSucceeded)
        {
            clsScreen::Print("\nClient data updated successfully.\n");
           _Print(client);
        }
        else
        {
            clsScreen::Print("\nFailed to update client data.\n");
        }
    }


};

