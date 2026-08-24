#pragma once
#include "clsScreen.h"
#include "MyInputLibrary.h"
#include "clsBankClient.h"

class clsWithdrawScreen :protected clsScreen
{
public:
    static void ShowWithdrawScreen()
    {
        _PrintHeader("Withdraw Screen");
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
        _Print("Enter amount to withdraw : ");
        double amount = MyInputLibrary::ReadPositiveDouble("");

        _Print("");
        if (MyInputLibrary::ReadYesNo("Are you sure you want to withdraw " + to_string(amount) + " from account " + AccountNumber + " ? (Y/N): ") == false)
        {
            _Print("\n");
            _Print("Operation cancelled by user.\n");
            return;
        }

        if (client.Withdraw(amount))
        {
            _Print("\n");
            _Print("Amount withdrawed successfully.\n");
            _Print("New Balance is: " + to_string(client.Balance) + "\n");
        }
        else
        {
            _Print("\n");
            _Print("Error: Amount withdraw failed.\n");
        }
    }

};

