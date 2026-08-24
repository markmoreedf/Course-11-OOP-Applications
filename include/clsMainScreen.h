#pragma once

#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "MyInputLibrary.h"
#include "clsClientListScreen.h"
#include "clsFindClientScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsTransactionScreen.h" 
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsLoginScreen.h"
#include "clsUser.h"
#include "clsLogoutScreen.h"
#include "clsCurrencyMenuScreen.h"
#include "Global.h"

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
        eShowLoginHistory = 8,
        eCurrencyMenue = 9,
        eLogout = 10
    };

    static enMainMenueOption _ReadMainMenueOption()
    {
        clsScreen::_Print("");
        return (enMainMenueOption)MyInputLibrary::ReadNumberBetween(1, 10, "Choose what do you want to do? [1-10]: ");
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
        clsDeleteClientScreen::ShowDeleteClienScreen();
    }
    static void _TransactionsScreen()
    {
        system("cls");
        clsTransactionScreen::ShowTransactionMenue();   
    }
    static void _ManageUsersScreen()
    {
        system("cls");
        clsManageUsersScreen::ShowManageUsersScreen();
    }
    static void _ShowLoginHistoryScreen()
    {
        system("cls");
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }
    static void _LoginScreen()
    {
        system("cls");
        clsLoginScreen::ShowLoginScreen();
    }
    static void _LogoutScreen()
    {
        clsLogoutScreen::Logout();
    }
    static void _CurrencyMenueScreen()
    {
        system("cls");
        clsCurrencyMenuScreen::ShowCurrencyMenue();
    }

    static void _PerformMainMenueChoice(enMainMenueOption & choice)
    {
        switch (choice)
        {
        case eShowClientsList:
            if (! CurrentUser.HasPermission(clsUser::enUserPermissions::showClientList))
            {
                _Print("\n");
                _Print("<<< You Don't Have Permission To Do That. >>>");
                break;
            }
            _ClientsListScreen();
            break;

        case eFindClient:
            if (! CurrentUser.HasPermission(clsUser::enUserPermissions::findClient))
            {
                _Print("\n");
                _Print("<<< You Don't Have Permission To Do That. >>>");
                break;
            }
            _FindCliendScreen();
            break;

        case eAddNewClient:
            if (! CurrentUser.HasPermission(clsUser::enUserPermissions::addClient))
            {
                _Print("\n");
                _Print("<<< You Don't Have Permission To Do That. >>>");
                break;
            }
            _AddNewClientScreen();
            break;

        case eUpdateClientData:
            if (! CurrentUser.HasPermission(clsUser::enUserPermissions::updateClient))
            {
                _Print("\n");
                _Print("<<< You Don't Have Permission To Do That. >>>");
                break;
            }
            _UpdateClientScreen();
            break;

        case eDeleteClient:
            if (! CurrentUser.HasPermission(clsUser::enUserPermissions::deleteClient))
            {
                _Print("\n");
                _Print("<<< You Don't Have Permission To Do That. >>>");
                break;
            }
            _DeleteClientScreen();
            break;

        case eTransactionsMenue:
            if (! CurrentUser.HasPermission(clsUser::enUserPermissions::transactions))
            {
                _Print("\n");
                _Print("<<< You Don't Have Permission To Do That. >>>");
                break;
            }
            _TransactionsScreen();
            break;

        case eManageUsersMenue:
            if (! CurrentUser.HasPermission(clsUser::enUserPermissions::manageUsers))
            {
                _Print("\n");
                _Print("<<< You Don't Have Permission To Do That. >>>");
                break;
            }
            _ManageUsersScreen();           
            break;
        case eShowLoginHistory:
            if (! CurrentUser.HasPermission(clsUser::enUserPermissions::showLoginHistory))
            {
                _Print("\n");
                _Print("<<< You Don't Have Permission To Do That. >>>");
                break;
            }
            _ShowLoginHistoryScreen();
            break;
        case eCurrencyMenue:
            if(!CurrentUser.HasPermission(clsUser::enUserPermissions::currencyScreen))
            {
                _Print("\n");
                _Print("<<< You Don't Have Permission To Do That. >>>");
                break;
            }
            _CurrencyMenueScreen();
            break;
        case eLogout:
            if (clsLogoutScreen::Logout())
                return;
            else
                choice = enMainMenueOption::eAddNewClient; // Reset choice to continue the loop if logout is canceled
                break;
        default:
            _Print("\n\n");
            _PauseScreen("Invalid choice. Please try again.\n");
            break;
        }
        _Print("\n\n");
        _PauseScreen("Press any key to return to the Main Menu...");
    }

public:
    static void ShowMainMenue()
    {
        enMainMenueOption choice = enMainMenueOption::eAddNewClient; // Initialize with a default value to enter the loop
        while (choice != enMainMenueOption::eLogout)
        {
            system("cls");
            _PrintHeader("Main Screen", 5);
            _Print("=================================\n");
            _Print(" [1] Show Clients List.\n");
            _Print(" [2] Find Client.\n");
            _Print(" [3] Add New Client.\n");
            _Print(" [4] Update Client Data.\n");
            _Print(" [5] Delete Client.\n");
            _Print(" [6] Transactions Menue.\n");
            _Print(" [7] Manage Useres Menue\n");
            _Print(" [8] Show Login History\n");
            _Print(" [9] Currency Menue\n");
            _Print(" [10] Logout.\n");
            _Print("=================================\n\n");
            choice = _ReadMainMenueOption();
            _PerformMainMenueChoice(choice);
        }

    }

};