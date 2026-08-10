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

    static void _ReturnToTransactionMenue()
    {
        clsScreen::Print("\n\n");
        clsScreen::_PauseScreen();
        clsTransactionScreen::ShowTransactionMenue();
    }

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
        clsScreen::Print("\n"); clsScreen::Print("");
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
            clsScreen::Print("Invalid choice. Please try again.\n");
            break;
        }
        _ReturnToTransactionMenue();
    }

public:
    static void ShowTransactionMenue()
    {
        system("cls");
        clsScreen::_PrintHeader("Transactions Menue",2);
        clsScreen::Print("===============================\n");
        clsScreen::Print(" [1] Deposit.\n");
        clsScreen::Print(" [2] Withdraw.\n");
        clsScreen::Print(" [3] Show All Balances.\n");
        clsScreen::Print(" [4] Transfer.\n");
        clsScreen::Print(" [5] Return to Main Menue.\n");
        clsScreen::Print("===============================\n");
        _PerformTransactionMenueChoice(_ReadTransactionMenueOption());
    }

};

