#pragma once
#include "clsScreen.h"
#include "MyInputLibrary.h"
#include "clsTotalBalancesScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"

class clsTransactionScreen : protected clsScreen
{
private:
    enum enTransactionMenueOption
    {
        eDeposit = 1,
        eWithdraw = 2,
        eAllBalances = 3,
        eMainMenue = 4
    };

    static void _ReturnToTransactionMenue()
    {
        clsScreen::Print("\n\n");
        clsScreen::_PauseScreen();
        clsTransactionScreen::ShowTransactionMenue();
    }

    static void _DepositScreen()
    {
        clsDepositScreen::ShowDepositScreen();
    }
    static void _WithdrawScreen()
    {
        clsWithdrawScreen::ShowWithdrawScreen();
    }
    static void _AllBalancesScreen()
    {
        clsTotalBalancesScreen::ShowTotalBalancesScreen();
    }

    static enTransactionMenueOption _ReadTransactionMenueOption()
    {
        clsScreen::Print("\n"); clsScreen::Print("");
        return (enTransactionMenueOption)MyInputLibrary::ReadNumberBetween(1, 4, "Choose what do you want to do? [1-4]: ");
    }

    static void _PerformTransactionMenueChoice(enTransactionMenueOption choice)
    {
        switch (choice)
        {
        case eDeposit:
            system("cls");
            _DepositScreen();            
            break;
        case eWithdraw:
            system("cls");
            _WithdrawScreen();           
            break;                  
        case eAllBalances:
            system("cls");
            _AllBalancesScreen();           
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
        clsScreen::Print(" [4] Return to Main Menue.\n");
        clsScreen::Print("===============================\n");
        _PerformTransactionMenueChoice(_ReadTransactionMenueOption());
    }

};

