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
        Print("Enter amount to withdraw : ");
        double amount = MyInputLibrary::ReadPositiveDouble("");

        Print("");
        if (MyInputLibrary::ReadYesNo("Are you sure you want to withdraw " + to_string(amount) + " from account " + AccountNumber + " ? (Y/N): ") == false)
        {
            Print("\n");
            Print("Operation cancelled by user.\n");
            return;
        }

        if (client.Withdraw(amount))
        {
            Print("\n");
            Print("Amount withdrawed successfully.\n");
            Print("New Balance is: " + to_string(client.Balance) + "\n");
        }
        else
        {
            Print("\n");
            Print("Error: Amount withdraw failed.\n");
        }
    }

};

