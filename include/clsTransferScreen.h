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
        Print("\n"); Print("");
        return (enTransferMenueOption)MyInputLibrary::ReadNumberBetween(1, 4, "Choose what do you want to do? [1-4]: ");
    }

    static void _PrintClientCard(clsBankClient& client) 
    {
        Print("\n");
        Print("        Client Card\n");
        Print("=============================\n");
        Print("Full Name   : " + client.FirstName + " " + client.LastName + "\n");
        Print("Account No.  : " + client.AccountNumber + "\n");
        Print("Balance      : " + to_string(client.Balance) + "\n");
        Print("=============================\n\n");
    }

    static  clsBankClient _PrepreSender()
    {
        clsBankClient senderClient = clsBankClient::FindClient(""); // Empty initialization
        bool confirmSender = false;

        while (!confirmSender)
        {
            Print("Enter Sender Account Number: ");
            string senderAccountNumber = MyInputLibrary::ReadLine("");
            senderClient = clsBankClient::FindClient(senderAccountNumber);

            while (senderClient.IsEmpty())
            {
                Print("\n");
                Print("<<< Sender Account Not Found. >>>\n");
                Print("Press any key to try again...\n\n");
                system("pause>0");

                Print("Enter Sender Account Number: ");
                senderAccountNumber = MyInputLibrary::ReadLine("");
                senderClient = clsBankClient::FindClient(senderAccountNumber);
            }

            _PrintClientCard(senderClient);

            Print("Are you sure you want to use this account as sender? (Y/N): ");
            confirmSender = MyInputLibrary::ReadYesNo("");

            Print("\n");
        }
        return senderClient;
    }

    static clsBankClient _PrepareReciever(const string & senderAccountNumber)
    {
        clsBankClient receiverClient = clsBankClient::FindClient("");
        bool confirmReceiver = false;

        while (!confirmReceiver)
        {
            Print("Enter Receiver Account Number: ");
            string receiverAccountNumber = MyInputLibrary::ReadLine("");
            receiverClient = clsBankClient::FindClient(receiverAccountNumber);

            while (receiverClient.IsEmpty() || receiverAccountNumber == senderAccountNumber)
            {
                if (receiverClient.IsEmpty())
                {
                    Print("\n");
                    Print("<<< Receiver Account Not Found. >>>\n");
                }
                else
                {
                    Print("\n");
                    Print("<<< You cannot transfer to the same account! >>>\n");
                }

                Print("Press any key to try again...\n\n");
                system("pause>0");

                Print("Enter Receiver Account Number: ");
                receiverAccountNumber = MyInputLibrary::ReadLine("");
                receiverClient = clsBankClient::FindClient(receiverAccountNumber);
            }

            _PrintClientCard(receiverClient);

            Print("Are you sure you want to use this account as receiver? (Y/N): ");
            confirmReceiver = MyInputLibrary::ReadYesNo("");

            Print("\n");
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
                Print("\n");
                Print("Enter Amount to Transfer: ");
                amount = MyInputLibrary::ReadDouble("");
                Print("");
                confirmAmount = MyInputLibrary::ReadYesNo("Are you sure you want to transfer "
                    + to_string(amount) + "$ from " + senderClient.FullName() + " to "
                    + receiverClient.FullName() + "? (Y/N): ");
            }

            clsBankClient::enTransferResults transferResult = senderClient.Transfer(amount, receiverClient);

            if (transferResult == clsBankClient::enTransferResults::trSucceeded)
            {
                senderClient.RegisterTransfer(receiverClient.AccountNumber, amount);
                break;
            }

            else if (transferResult == clsBankClient::enTransferResults::trFailedInsufficientFunds)
                Print("\n<<< Insufficient Funds. >>>\n");

            else if (transferResult == clsBankClient::enTransferResults::trFailedDepositError)
                Print("\n<<< Deposit Error. >>>\n");

        }

        Print("\n");        Print("<<< Transfer Successful. >>>\n");
        _PrintClientCard(senderClient);
        _PrintClientCard(receiverClient);
    }

    static void _ShowClientTransferRegistery()
    {
        Print("\n");
        Print("Enter Client Account Number: ");

        string accountNumber = MyInputLibrary::ReadWord("");
        clsBankClient client = clsBankClient::FindClient(accountNumber);

        while (client.IsEmpty())
        {
            Print("\n");
            Print("<<< Client Account Not Found. >>>");
            _PauseScreen("Press any key to try again...\n\n");
            Print("Enter Client Account Number: ");
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
            Print("\n"); Print("Invalid choice. Please try again.\n");
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
            Print("===============================\n");
            Print(" [1] Transfer Money.\n");
            Print(" [2] ShowClient Transfers.\n");
            Print(" [3] Show All Transfers.\n");
            Print(" [4] Return To Main Menue.\n");
            Print("===============================\n");
            choice = _ReadTransferMenueOption();
            _PerformTransferScreen(choice);


        }
    }
};

