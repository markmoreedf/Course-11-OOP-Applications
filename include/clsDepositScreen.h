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
        clsScreen::_PrintHeader("Deposit Screen");
        clsScreen::Print("Enter Account Number: ");
        string AccountNumber = MyInputLibrary::ReadWord("");

        clsBankClient client = clsBankClient::FindClient(AccountNumber);

        while (client.IsEmpty())
        {
            clsScreen::Print("Account Number not found, please enter a valid one: ");
            AccountNumber = MyInputLibrary::ReadWord("");
        }
        clsScreen::Print("Enter amount to deposit : ");
        double amount = MyInputLibrary::ReadPositiveDouble("");

        clsScreen::Print("");
        if(MyInputLibrary::ReadYesNo("Are you sure you want to deposit " + to_string(amount) + " to account " + AccountNumber + " ? (Y/N): ") == false)
        {
            clsScreen::Print("\n");
            clsScreen::Print("Operation cancelled by user.\n");
            return;
        }

        if (client.Deposite(amount))
        {
            clsScreen::Print("\n");
            clsScreen::Print("Amount deposited successfully.\n");
            clsScreen::Print("New Balance is: " + to_string(client.Balance) + "\n");
        }
        else
        {
            clsScreen::Print("\n");
            clsScreen::Print("Error: Amount deposit failed.\n");
        }

    }



};

