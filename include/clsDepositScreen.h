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
        Print("Enter Account Number: ");
        string AccountNumber = MyInputLibrary::ReadWord("");

        clsBankClient client = clsBankClient::FindClient(AccountNumber);

        while (client.IsEmpty())
        {
            Print("\n");
            Print("Account Number not found, please enter a valid one: ");
            AccountNumber = MyInputLibrary::ReadWord("");
        }

        Print("\n");
        Print("Enter amount to deposit : ");
        double amount = MyInputLibrary::ReadPositiveDouble("");

        Print("");
        if(MyInputLibrary::ReadYesNo("Are you sure you want to deposit " + to_string(amount) + " to account " + AccountNumber + " ? (Y/N): ") == false)
        {
            Print("\n");
            Print("Operation cancelled by user.\n");
            return;
        }

        if (client.Deposit(amount))
        {
            Print("\n");
            Print("Amount deposited successfully.\n");
            Print("New Balance is: " + to_string(client.Balance) + "\n");
        }
        else
        {
            Print("\n");
            Print("Error: Amount deposit failed.\n");
        }

    }



};

