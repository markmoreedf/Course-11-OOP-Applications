#pragma once
#include "clsScreen.h"
#include "MyInputLibrary.h"
#include "clsBankClient.h"
class clsDepositScreen : protected clsScreen
{
private:


public:
    static void ShowDepositScreen()
    {
        _PrintHeader("Deposit Screen");
        _Print("Enter Account Number: ");
        string AccountNumber = MyInputLibrary::ReadWord("");

        clsBankClient client = clsBankClient::FindClient(AccountNumber);

        while (client.IsEmpty())
        {
            _Print("\n");
            _Print("Account Number not found, please enter a valid one: ");
            AccountNumber = MyInputLibrary::ReadWord("");
        }

        _Print("\n");
        _Print("Enter amount to deposit : ");
        double amount = MyInputLibrary::ReadPositiveDouble("");

        _Print("");
        if(MyInputLibrary::ReadYesNo("Are you sure you want to deposit " + to_string(amount) + " to account " + AccountNumber + " ? (Y/N): ") == false)
        {
            _Print("\n");
            _Print("Operation cancelled by user.\n");
            return;
        }

        if (client.Deposit(amount))
        {
            _Print("\n");
            _Print("Amount deposited successfully.\n");
            _Print("New Balance is: " + to_string(client.Balance) + "\n");
        }
        else
        {
            _Print("\n");
            _Print("Error: Amount deposit failed.\n");
        }

    }



};

