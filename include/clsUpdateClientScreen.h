#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "MyInputLibrary.h"

class clsUpdateClientScreen :
    public clsScreen
{
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
    static void _PrintOldVsNewClientData(const clsBankClient& OldClient, const clsBankClient& NewClient)
    {
        short labelWidth = 12;         // Align the colons :
        short firstCardWidth = 40;     // Space between the start of card 1 and card 2

        std::cout << clsScreen::spaces << "\n";
        std::cout << clsScreen::spaces << setw(firstCardWidth) << left << "      Old Client Data" << "      New Client Data" << endl;
        std::cout << clsScreen::spaces << setw(firstCardWidth) << left << "==============================" << "==============================" << endl;

        // Helper Lambda function to print a row
        auto printRow = [&](string label, string val1, string val2) {

            std::cout << clsScreen::spaces;
            string firstCardPart = "";
        
            std::cout << left << setw(labelWidth) << label << ": " << setw(firstCardWidth - labelWidth - 2) << val1;
            std::cout << left << setw(labelWidth) << label << ": " << val2 << endl;
            };

        printRow("First Name", OldClient.FirstName, NewClient.FirstName);
        printRow("Last Name", OldClient.LastName, NewClient.LastName);
        printRow("Email", OldClient.Email, NewClient.Email);
        printRow("Phone", OldClient.Phone, NewClient.Phone);
        printRow("Acc. No", OldClient.AccountNumber, NewClient.AccountNumber);
        printRow("Balance", to_string(OldClient.Balance), to_string(NewClient.Balance));

        std::cout << clsScreen::spaces << setw(firstCardWidth) << left << "==============================" << "==============================" << endl;
    }

public:
    static void UpdateClientScreen()
    {
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
         
        _Print(client);
        clsBankClient newClientData = client; // to hold old data before updating
        clsScreen::Print("Please enter new data for the client:\n");
        _ReadClientData(newClientData);
        
        _PrintOldVsNewClientData(client, newClientData);

        clsScreen::Print(""); // just to allign the msg of the next line
        if( ! MyInputLibrary::ReadYesNo("Do you want to update this client? (Y/N): "))
        {
            clsScreen::Print("\nUpdate cancelled by user.\n");
            return;
        }

        clsBankClient::enSaveResults saveResult = newClientData.Save();
        if (saveResult == clsBankClient::svSucceeded)
        {
            clsScreen::Print("\n");
            clsScreen::Print("Client data updated successfully.\n");
        }
        else
        {
            clsScreen::Print("\n");
            clsScreen::Print("Failed to update client data.\n");
        }
    }


};

