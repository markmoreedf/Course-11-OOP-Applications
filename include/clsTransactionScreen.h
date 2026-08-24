#pragma once
#include "clsScreen.h"
#include "MyInputLibrary.h"
#include "clsTotalBalancesScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTransferScreen.h"
class clsTransactionScreen : protected clsScreen
{
private:
    enum enTransactionMenueOption
    {
        eDeposit = 1,
        eWithdraw = 2,
        eAllBalances = 3,
        eTransfer = 4,
        eMainMenue = 5
    };

    static void _DepositScreen()
    {
        system("cls");
        clsDepositScreen::ShowDepositScreen();
    }
    static void _WithdrawScreen()
    {
        system("cls");
        clsWithdrawScreen::ShowWithdrawScreen();
    }
    static void _AllBalancesScreen()
    {
        system("cls");
        clsTotalBalancesScreen::ShowTotalBalancesScreen();
    }
    static void _TransferScreen()
    {
        system("cls");
        clsTransferScreen::ShowTransferScreen();
    }

    static enTransactionMenueOption _ReadTransactionMenueOption()
    {
        _Print("\n"); _Print("");
        return (enTransactionMenueOption)MyInputLibrary::ReadNumberBetween(1, 5, "Choose what do you want to do? [1-5]: ");
    }

    static void _PerformTransactionMenueChoice(enTransactionMenueOption choice)
    {
        switch (choice)
        {
        case eDeposit:
            _DepositScreen();            
            break;
        case eWithdraw:
            _WithdrawScreen();           
            break;                  
        case eAllBalances:
            _AllBalancesScreen();           
            break;
        case eTransfer:
            _TransferScreen();
            break;
        case eMainMenue:
            return; // Exit to main menue, without calling clsMainScreen::ShowMainMenue(). recursion avoidance
        default:
            _Print("Invalid choice. Please try again.\n");
            _PauseScreen();
            break;
        }
        _Print("\n\n");
        _PauseScreen("Press any key to go back");
    }

public:
    static void ShowTransactionMenue()
    {
        enTransactionMenueOption transactionMenueChoice = enTransactionMenueOption::eDeposit; // Initialize with a default value to enter the loop
        while (transactionMenueChoice != eMainMenue)
        {
            system("cls");
            _PrintHeader("Transactions Menue",2);
            _Print("===============================\n");
            _Print(" [1] Deposit.\n");
            _Print(" [2] Withdraw.\n");
            _Print(" [3] Show All Balances.\n");
            _Print(" [4] Transfer.\n");
            _Print(" [5] Return to Main Menue.\n");
            _Print("===============================\n");
            transactionMenueChoice = _ReadTransactionMenueOption();
            _PerformTransactionMenueChoice(transactionMenueChoice);

        }

    }

};

