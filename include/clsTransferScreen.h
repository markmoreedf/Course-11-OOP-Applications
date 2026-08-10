#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "MyInputLibrary.h"
#include <string>
class clsTransferScreen :
    protected clsScreen
{
private:

    void _PrintClientCard(clsBankClient& client)
    {
        clsScreen::Print("\n");
        clsScreen::Print("        Client Card\n");
        clsScreen::Print("=============================\n");
        clsScreen::Print("Full Name   : " + client.FirstName + " " + client.LastName + "\n");
        clsScreen::Print("Account No.  : " + client.AccountNumber + "\n");
        clsScreen::Print("Balance      : " + to_string(client.Balance) + "\n");
        clsScreen::Print("=============================\n\n");
    }

    clsBankClient _PrepreSender()
    {
        clsBankClient senderClient = clsBankClient::FindClient(""); // Empty initialization
        bool confirmSender = false;

        while (!confirmSender)
        {
            clsScreen::Print("Enter Sender Account Number: ");
            string senderAccountNumber = MyInputLibrary::ReadLine("");
            senderClient = clsBankClient::FindClient(senderAccountNumber);

            while (senderClient.IsEmpty())
            {
                clsScreen::Print("\n");
                clsScreen::Print("<<< Sender Account Not Found. >>>\n");
                clsScreen::Print("Press any key to try again...\n\n");
                system("pause>0");

                clsScreen::Print("Enter Sender Account Number: ");
                senderAccountNumber = MyInputLibrary::ReadLine("");
                senderClient = clsBankClient::FindClient(senderAccountNumber);
            }

            _PrintClientCard(senderClient);

            clsScreen::Print("Are you sure you want to use this account as sender? (Y/N): ");
            confirmSender = MyInputLibrary::ReadYesNo("");

            clsScreen::Print("\n");
        }
        return senderClient;
    }

    clsBankClient _PrepareReciever(const string & senderAccountNumber)
    {
        clsBankClient receiverClient = clsBankClient::FindClient("");
        bool confirmReceiver = false;

        while (!confirmReceiver)
        {
            clsScreen::Print("Enter Receiver Account Number: ");
            string receiverAccountNumber = MyInputLibrary::ReadLine("");
            receiverClient = clsBankClient::FindClient(receiverAccountNumber);

            while (receiverClient.IsEmpty() || receiverAccountNumber == senderAccountNumber)
            {
                if (receiverClient.IsEmpty())
                {
                    clsScreen::Print("\n");
                    clsScreen::Print("<<< Receiver Account Not Found. >>>\n");
                }
                else
                {
                    clsScreen::Print("\n");
                    clsScreen::Print("<<< You cannot transfer to the same account! >>>\n");
                }

                clsScreen::Print("Press any key to try again...\n\n");
                system("pause>0");

                clsScreen::Print("Enter Receiver Account Number: ");
                receiverAccountNumber = MyInputLibrary::ReadLine("");
                receiverClient = clsBankClient::FindClient(receiverAccountNumber);
            }

            _PrintClientCard(receiverClient);

            clsScreen::Print("Are you sure you want to use this account as receiver? (Y/N): ");
            confirmReceiver = MyInputLibrary::ReadYesNo("");

            clsScreen::Print("\n");
        }

        return receiverClient;
    }


    void _PerformTransferScreen()
    {
        clsBankClient senderClient = _PrepreSender();
        clsBankClient receiverClient = _PrepareReciever(senderClient.AccountNumber);

        double amount = 0;

        while (true)
        {
            bool confirmAmount = false;
            while (!confirmAmount)
            {
                clsScreen::Print("\n");
                clsScreen::Print("Enter Amount to Transfer: ");
                amount = MyInputLibrary::ReadDouble("");
                clsScreen::Print("");
                confirmAmount = MyInputLibrary::ReadYesNo("Are you sure you want to transfer "
                    + to_string(amount) + "$ from " + senderClient.FullName() + " to "
                    + receiverClient.FullName() + "? (Y/N): ");
            }

            clsBankClient::enTransferResults transferResult = senderClient.Transfer(amount, receiverClient);

            if (transferResult == clsBankClient::enTransferResults::trSucceeded)
                break;

            else if (transferResult == clsBankClient::enTransferResults::trFailedInsufficientFunds)
                clsScreen::Print("\n<<< Insufficient Funds. >>>\n");
            
            else if (transferResult == clsBankClient::enTransferResults::trFailedDepositError)
                clsScreen::Print("\n<<< Deposit Error. >>>\n");

        }

        clsScreen::Print("\n");        clsScreen::Print("<<< Transfer Successful. >>>\n");
        _PrintClientCard(senderClient);
        _PrintClientCard(receiverClient);
    }


public:
    static void ShowTransferScreen()
    {
        clsScreen::_PrintHeader("Transfer Screen");
        clsTransferScreen transferScreen;
        transferScreen._PerformTransferScreen();
    }
};

