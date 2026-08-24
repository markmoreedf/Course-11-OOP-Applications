#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "MyInputLibrary.h"
#include <string>
class clsTransferScreen :
    protected clsScreen
{
private:

    enum enTransferMenueOption
    {
        eTransferMoney = 1,
        eShowClientTransferRegistery = 2,
        eShowAllTransferRegistery = 3,
        eGoBack = 4
    };

    static enTransferMenueOption _ReadTransferMenueOption()
    {
        _Print("\n"); _Print("");
        return (enTransferMenueOption)MyInputLibrary::ReadNumberBetween(1, 4, "Choose what do you want to do? [1-4]: ");
    }

    static void _PrintClientCard(clsBankClient& client) 
    {
        _Print("\n");
        _Print("        Client Card\n");
        _Print("=============================\n");
        _Print("Full Name   : " + client.FirstName + " " + client.LastName + "\n");
        _Print("Account No.  : " + client.AccountNumber + "\n");
        _Print("Balance      : " + to_string(client.Balance) + "\n");
        _Print("=============================\n\n");
    }

    static  clsBankClient _PrepreSender()
    {
        clsBankClient senderClient = clsBankClient::FindClient(""); // Empty initialization
        bool confirmSender = false;

        while (!confirmSender)
        {
            _Print("Enter Sender Account Number: ");
            string senderAccountNumber = MyInputLibrary::ReadLine("");
            senderClient = clsBankClient::FindClient(senderAccountNumber);

            while (senderClient.IsEmpty())
            {
                _Print("\n");
                _Print("<<< Sender Account Not Found. >>>\n");
                _Print("Press any key to try again...\n\n");
                system("pause>0");

                _Print("Enter Sender Account Number: ");
                senderAccountNumber = MyInputLibrary::ReadLine("");
                senderClient = clsBankClient::FindClient(senderAccountNumber);
            }

            _PrintClientCard(senderClient);

            _Print("Are you sure you want to use this account as sender? (Y/N): ");
            confirmSender = MyInputLibrary::ReadYesNo("");

            _Print("\n");
        }
        return senderClient;
    }

    static clsBankClient _PrepareReciever(const string & senderAccountNumber)
    {
        clsBankClient receiverClient = clsBankClient::FindClient("");
        bool confirmReceiver = false;

        while (!confirmReceiver)
        {
            _Print("Enter Receiver Account Number: ");
            string receiverAccountNumber = MyInputLibrary::ReadLine("");
            receiverClient = clsBankClient::FindClient(receiverAccountNumber);

            while (receiverClient.IsEmpty() || receiverAccountNumber == senderAccountNumber)
            {
                if (receiverClient.IsEmpty())
                {
                    _Print("\n");
                    _Print("<<< Receiver Account Not Found. >>>\n");
                }
                else
                {
                    _Print("\n");
                    _Print("<<< You cannot transfer to the same account! >>>\n");
                }

                _Print("Press any key to try again...\n\n");
                system("pause>0");

                _Print("Enter Receiver Account Number: ");
                receiverAccountNumber = MyInputLibrary::ReadLine("");
                receiverClient = clsBankClient::FindClient(receiverAccountNumber);
            }

            _PrintClientCard(receiverClient);

            _Print("Are you sure you want to use this account as receiver? (Y/N): ");
            confirmReceiver = MyInputLibrary::ReadYesNo("");

            _Print("\n");
        }

        return receiverClient;
    }

    static void _TransferMoney()
    {
        clsBankClient senderClient = _PrepreSender();
        clsBankClient receiverClient = _PrepareReciever(senderClient.AccountNumber);

        double amount = 0;

        while (true)
        {
            bool confirmAmount = false;
            while (!confirmAmount)
            {
                _Print("\n");
                _Print("Enter Amount to Transfer: ");
                amount = MyInputLibrary::ReadDouble("");
                _Print("");
                confirmAmount = MyInputLibrary::ReadYesNo("Are you sure you want to transfer "
                    + to_string(amount) + "$ from " + senderClient.FullName() + " to "
                    + receiverClient.FullName() + "? (Y/N): ");
            }

            clsBankClient::enTransferResults transferResult = senderClient.Transfer(amount, receiverClient);

            if (transferResult == clsBankClient::enTransferResults::trSucceeded)
            {
                _Print("\n");        _Print("<<< Transfer Successful. >>>\n");
                _PrintClientCard(senderClient);
                _PrintClientCard(receiverClient);
                break;
            }

            else if (transferResult == clsBankClient::enTransferResults::trFailedInsufficientFunds)
            {
                _Print("\n");
                _Print("<<< Insufficient Funds. >>>\n");
                _Print("Do you want to try a different amount? (Y/N): ");
                if (!MyInputLibrary::ReadYesNo(""))
                {
                    _Print("\n");
                    _Print("Transfer Cancelled.\n");
                    break;
                }
            }
           
            else if (transferResult == clsBankClient::enTransferResults::trFailedDepositError)
            {
                _Print("\n");
                _Print("<<< Deposit Error. >>>\n");
                _Print("Do you want to try again? (Y/N): ");
                if (!MyInputLibrary::ReadYesNo(""))
                {
                    _Print("\n");
                    _Print("Transfer Cancelled.\n");
                    break;
                }
            }

        }

    }

    static void _ShowClientTransferRegistery()
    {
        _Print("\n");
        _Print("Enter Client Account Number: ");

        string accountNumber = MyInputLibrary::ReadWord("");
        clsBankClient client = clsBankClient::FindClient(accountNumber);

        while (client.IsEmpty())
        {
            _Print("\n");
            _Print("<<< Client Account Not Found. >>>");
            _PauseScreen("Press any key to try again...\n\n");
            _Print("Enter Client Account Number: ");
            accountNumber = MyInputLibrary::ReadWord("");
        }

        vector<vector<string>> transferRegistery = client.GetClientTransferRegistery();
        _PrintHeader("Transfer Registery List. [" + to_string(transferRegistery.size()) + "] found");
        clsTable::PrintTable({ "Date & Time", "Sender AccNo", "Reciever AccNo", "Amount", "Sender Balance After", "Receiver Balance After", "User" },
            { 25, 20, 25, 20, 25, 25, 15 }, transferRegistery, "No Transfers Available For This Client In the System!", 5, clsTable::Colors::BrightCyan);
    }

    static void _ShowAllTransferRegistery()
    {
        vector<vector<string>> transferRegistery = clsBankClient::GetAllTransferRegistery();
        _PrintHeader("Transfer Registery List. [" + to_string(transferRegistery.size()) + "] found", 15);
        clsTable::PrintTable({ "Date & Time", "Sender AccNo", "Reciever AccNo", "Amount", "Sender Balance After", "Receiver Balance After", "User" },
            { 25, 20, 25, 20, 25, 25, 15 }, transferRegistery, "No Transfers Available For This Client In the System!", 5, clsTable::Colors::BrightCyan);
    }

    static void _PerformTransferScreen(enTransferMenueOption option)
    {
        switch (option)
        {
        case clsTransferScreen::eTransferMoney:
            system("cls");
            _PrintHeader("Transfer Money Screen  $ <===> $");
            _TransferMoney();
            break;
        case clsTransferScreen::eShowClientTransferRegistery:
            system("cls");
            _ShowClientTransferRegistery();
            break;
        case clsTransferScreen::eShowAllTransferRegistery:
            system("cls");
            _ShowAllTransferRegistery();
            break;
        case clsTransferScreen::eGoBack:
            return;
        default:
            _Print("\n"); _Print("Invalid choice. Please try again.\n");
            _PauseScreen();
            return;
        }
         _PauseScreen("Press any key to go back to Transactions Menue.");
    }


public:
    static void ShowTransferScreen()
    {
        enTransferMenueOption choice = enTransferMenueOption::eTransferMoney; // Initialize with a default value to enter the loop
        while (choice != enTransferMenueOption::eGoBack)
        {
            system("cls");
            _PrintHeader("Transfer Screen");
            _Print("===============================\n");
            _Print(" [1] Transfer Money.\n");
            _Print(" [2] ShowClient Transfers.\n");
            _Print(" [3] Show All Transfers.\n");
            _Print(" [4] Return To Main Menue.\n");
            _Print("===============================\n");
            choice = _ReadTransferMenueOption();
            _PerformTransferScreen(choice);


        }
    }
};

