#pragma once
#include "clsScreen.h"
#include "MyInputLibrary.h"
#include "clsTotalBalancesScreen.h"

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
        system("cls");
        clsScreen::Print("Here will be deposit screen\n");
    }
    static void _WithdrawScreen()
    {
        system("cls");
        clsScreen::Print("Here will be withdraw screen\n");
    }
    static void _AllBalancesScreen()
    {
        system("cls");
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
            _DepositScreen();            
            break;
        case eWithdraw:
            _WithdrawScreen();           
            break;                  
        case eAllBalances:
            _AllBalancesScreen();           
            break;
        case eMainMenue:
            // clsMainScreen::ShowMainMenue();
            // break;
            return; // Exit to main menue but without calling more functions. recursion avoidance
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
        clsScreen::_PrintHeader("Transactions Menue");
        clsScreen::Print("=================================\n");
        clsScreen::Print(" [1] Deposit.\n");
        clsScreen::Print(" [2] Withdraw.\n");
        clsScreen::Print(" [3] Show All Balances.\n");
        clsScreen::Print(" [4] Return to Main Menue.\n");
        clsScreen::Print("=================================\n");
        _PerformTransactionMenueChoice(_ReadTransactionMenueOption());
    }

};

