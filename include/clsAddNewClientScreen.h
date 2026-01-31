#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "MyInputLibrary.h"

class clsAddNewClientScreen :protected clsScreen
{
private:
    static void _ReadClientData(clsBankClient& client)
    { 
    clsScreen::Print("Please enter the following client data:\n") ;
    clsScreen::Print("");  client.FirstName = MyInputLibrary::ReadLine("First Name: ");
    clsScreen::Print("");  client.LastName = MyInputLibrary::ReadLine("Last Name: ");
    clsScreen::Print("");  client.Email = MyInputLibrary::ReadLine("Email: ");
    clsScreen::Print("");  client.Phone = MyInputLibrary::ReadLine("Phone: ");
    clsScreen::Print("");  client.Pincode = MyInputLibrary::ReadLine("Pin Code: ");
    clsScreen::Print("");  client.Balance = MyInputLibrary::ReadPositiveDouble("Balance: ");

    }
public: 
    static void AddNewClientScreen()
    {
        system("cls");
        clsScreen::_PrintHeader("Add New Client Screen");
        clsScreen::Print("");
        string AccountNumber = MyInputLibrary::ReadLine("Enter New Account Number: ");
        while (clsBankClient::IsClientExist(AccountNumber))
        {
            clsScreen::Print("Account Number already exists. Please enter a different one.\n");
            clsScreen::Print("");
            AccountNumber = MyInputLibrary::ReadLine("Enter New Account Number: ");
        }
        clsBankClient newClient = clsBankClient::GetAddNewClientObject(AccountNumber);
        _ReadClientData(newClient);

        clsBankClient::enSaveResults saveResult = newClient.Save();
        switch (saveResult)
        {
        case clsBankClient::svFailedEmptyObject:
            clsScreen::Print("Failed to add new client. Empty object.\n");
            break;
        case clsBankClient::svSucceeded:
            clsScreen::Print("New client added successfully.\n");
            break;
        case clsBankClient::svAccountNumberExists:
            clsScreen::Print("Account Number already exists. Cannot add new client.\n");
            break;
        }
    }
};

