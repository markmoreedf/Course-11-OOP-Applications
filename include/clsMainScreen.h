#pragma once

#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "MyInputLibrary.h"
#include "clsClientListScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionScreen.h" 

class clsMainScreen : protected clsScreen
{
private:
    enum enMainMenueOption
    {
        eShowClientsList = 1,
        eFindClient = 2,
        eAddNewClient = 3,
        eUpdateClientData = 4,
        eDeleteClient = 5,
        eTransactionsMenue = 6,
        eManageUsersMenue = 7,
        eLogout = 8
    };

    static enMainMenueOption _ReadMainMenueOption()
    {
        clsScreen::Print("");
        return (enMainMenueOption)MyInputLibrary::ReadNumberBetween(1, 9, "Choose what do you want to do? [1-9]: ");
    }
    static void _ReturnToMainMenue()
    {
        clsScreen::Print("\n\n");
        clsScreen::_PauseScreen();
        ShowMainMenue();
    } 
    static void _ClientsListScreen()
    {
        system("cls");
        clsClientListScreen::ShowClientsListScreen();
    }
    static void _FindCliendScreen()
    {
        system("cls");
        clsFindClientScreen::ShowFindClientScreen();
    }
    static void _AddNewClientScreen()
    {
        system("cls");
        clsAddNewClientScreen::AddNewClientScreen();
    }
    static void _UpdateClientScreen()
    {
        system("cls");
        clsUpdateClientScreen::UpdateClientScreen();
    } 
    static void _DeleteClientScreen()
    {
        system("cls");
        clsDeleteClientScreen::DeleteClienScreen();
    }
    static void _TransactionsScreen()
    {
        system("cls");
        clsTransactionScreen::ShowTransactionMenue();   
    }

    static void _ManageUsersScreen()
    {
        system("cls");
        clsScreen::Print("Here will be show users screen\n");
    }
    static void _LoginScreen()
    {
        system("cls");
        clsScreen::Print("Here will be login screen\n");
    }

    static void _PerformMainMenueChoice(enMainMenueOption choice)
    {
        switch (choice)
        {
        case eShowClientsList:
            _ClientsListScreen();
            break;
        case eFindClient:
            _FindCliendScreen();
            break;
        case eAddNewClient:
            _AddNewClientScreen();
            break;
        case eUpdateClientData:
            _UpdateClientScreen();
            break;
        case eDeleteClient:
            _DeleteClientScreen();
            break;
        case eTransactionsMenue:
            _TransactionsScreen();
            break;
        case eManageUsersMenue:
            _ManageUsersScreen();           
            break;
        case eLogout:
            _LoginScreen();

            return;
        default:
            std::cout << clsScreen::spaces << "Invalid choice. Please try again.\n";
            break;
        }
        
        _ReturnToMainMenue();

    }

public:
    static void ShowMainMenue()
    {
        system("cls");
        _PrintHeader("Main Screen", 5);
        clsScreen::Print("=================================\n");
        clsScreen::Print(" [1] Show Clients List.\n");
        clsScreen::Print(" [2] Find Client.\n");
        clsScreen::Print(" [3] Add New Client.\n");
        clsScreen::Print(" [4] Update Client Data.\n");
        clsScreen::Print(" [5] Delete Client.\n");
        clsScreen::Print(" [6] Transactions Menue.\n");
        clsScreen::Print(" [7] Manage Useres Menue\n");
        clsScreen::Print(" [8] Logout.\n");
        clsScreen::Print("=================================\n\n");
        
        enMainMenueOption choice =  _ReadMainMenueOption();
        _PerformMainMenueChoice(choice);
    }
};