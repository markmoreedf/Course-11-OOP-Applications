#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "MyInputLibrary.h"

class clsUpdateClientScreen :
    protected clsScreen
{
private:
    static void _ReadClientData(clsBankClient& client)
    {
        _Print("Please enter the following client data:\n\n");
        _Print("");  client.FirstName = MyInputLibrary::ReadLine("First Name: ");
        _Print("");  client.LastName = MyInputLibrary::ReadLine("Last Name: ");
        _Print("");  client.Email = MyInputLibrary::ReadLine("Email: ");
        _Print("");  client.Phone = MyInputLibrary::ReadLine("Phone: ");
        _Print("");  client.Pincode = MyInputLibrary::ReadLine("Pin Code: ");
        _Print("");  client.Balance = MyInputLibrary::ReadPositiveDouble("Balance: ");

    }
    static void _PrintClientCard(clsBankClient & client) 
    {
       _Print("\n");
       _Print( "        Client Card\n");
       _Print( "=============================\n");
       _Print("First Name   : " + client.FirstName + "\n");
       _Print("Last Name    : " + client.LastName + "\n");
       _Print("Email        : " + client.Email + "\n");
       _Print("Phone        : " + client.Phone + "\n");
       _Print("Account No.  : " + client.AccountNumber + "\n");
       _Print("Pincode      : " + client.Pincode + "\n");
       _Print("Balance      : " + to_string(client.Balance) + "\n");
       _Print("=============================\n\n");
    }
    static void _PrintOldVsNewClientData(const clsBankClient& OldClient, const clsBankClient& NewClient)
    {
        short labelWidth = 12;         // Align the colons :
        short firstCardWidth = 40;     // Space between the start of card 1 and card 2

        std::cout << spaces << "\n";
        std::cout << spaces << setw(firstCardWidth) << left << "      Old Client Data" << "      New Client Data" << endl;
        std::cout << spaces << setw(firstCardWidth) << left << "==============================" << "==============================" << endl;

        // Helper Lambda function to print a row
        auto printRow = [&](string label, string val1, string val2) {

            std::cout << spaces;
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

        std::cout << spaces << setw(firstCardWidth) << left << "==============================" << "==============================" << endl;
    }

public:
    static void UpdateClientScreen()
    {
        _PrintHeader("Update Client Data Screen");
        _Print("");
        string AccountNumber = MyInputLibrary::ReadLine("Enter Account number of the client to update: ");
        clsBankClient client = clsBankClient::FindClient(AccountNumber);
        
        while (client.IsEmpty()) {
            _Print("Client with Account Number " + AccountNumber + " not found.\n");
            _Print("\n");
            _Print("");
            AccountNumber = MyInputLibrary::ReadLine("Enter Account number of the client to update: ");
            client = clsBankClient::FindClient(AccountNumber);
        }
        _Print("\n");
        _Print("Current Client Data:\n");
         
        _PrintClientCard(client);
        clsBankClient newClientData = client; // to hold old data before updating
        _Print("Please enter new data for the client:\n");
        _ReadClientData(newClientData);
        
        _PrintOldVsNewClientData(client, newClientData);

        _Print(""); // just to allign the msg of the next line
        if( ! MyInputLibrary::ReadYesNo("Do you want to update this client? (Y/N): "))
        {
            _Print("\n");
            _Print("");
            _Print("Update cancelled by user.\n");
            return;
        }

        clsBankClient::enSaveResults saveResult = newClientData.Save();
        if (saveResult == clsBankClient::svSucceeded)
        {
            _Print("\n");
            _Print("Client data updated successfully.\n");
        }
        else
        {
            _Print("\n");
            _Print("Failed to update client data.\n");
        }
    }


};

