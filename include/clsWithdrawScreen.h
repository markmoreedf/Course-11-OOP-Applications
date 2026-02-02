#pragma once
#include "clsScreen.h"
#include "MyInputLibrary.h"
#include "clsBankClient.h"

class clsWithdrawScreen :protected clsScreen
{
public:
    static void ShowWithdrawScreen()
    {
        clsScreen::_PrintHeader("Withdraw Screen");
        clsScreen::Print("Enter Account Number: ");
        string AccountNumber = MyInputLibrary::ReadWord("");

        clsBankClient client = clsBankClient::FindClient(AccountNumber);

        while (client.IsEmpty())
        {
            clsScreen::Print("Account Number not found, please enter a valid one: ");
            AccountNumber = MyInputLibrary::ReadWord("");
        }
        clsScreen::Print("Enter amount to withdraw : ");
        double amount = MyInputLibrary::ReadPositiveDouble("");

        clsScreen::Print("");
        if (MyInputLibrary::ReadYesNo("Are you sure you want to withdraw " + to_string(amount) + " from account " + AccountNumber + " ? (Y/N): ") == false)
        {
            clsScreen::Print("\n");
            clsScreen::Print("Operation cancelled by user.\n");
            return;
        }

        if (client.Withdraw(amount))
        {
            clsScreen::Print("\n");
            clsScreen::Print("Amount withdrawed successfully.\n");
            clsScreen::Print("New Balance is: " + to_string(client.Balance) + "\n");
        }
        else
        {
            clsScreen::Print("\n");
            clsScreen::Print("Error: Amount withdraw failed.\n");
        }
    }

};

