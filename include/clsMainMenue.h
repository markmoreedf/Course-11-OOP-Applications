#pragma once

#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "MyInputLibrary.h"

class clsMainMenue : protected clsScreen
{
private:
    enum enMainMenueOptions
    {
        eShowClientsList = 1,
        eGetTotalBalances = 2,
        eFindClient = 3,
        eAddNewClient = 4,
        eUpdateClientData = 5,
        eDeleteClient = 6,
        eTransactionsMenue = 7,
        eManageUsersMenue = 8,
        eLogout = 9
    };

    static void _PrintClientsList()
    {
        system("cls");
        clsScreen::Print("Here will be the clients list\n");
    }
    static void _PrintTotalBalances()
    {
        system("cls");
        clsScreen::Print("Here will be balances list\n");
    }
    static void _FindAndShowClient()
    {
        system("cls");
        clsScreen::Print("Here will be find client screen\n");
    }
    static void _AddNewClient()
    {
        system("cls");
        clsScreen::Print("Here will be add new client screen\n");
    }
    static void _UpdateClientData()
    {
        system("cls");
        clsScreen::Print("here will be update client screen\n");
    }
    static void _DeleteClient()
    {
        system("cls");
        clsScreen::Print("Here will be delete client menue\n");
    }
    static void _ShowTransactionsMenue()
    {
        system("cls");
        clsScreen::Print("Here will be transactions menue\n");
    }
    static void _ShowUsersMenue()
    {
        system("cls");
        clsScreen::Print("Here will be show users screen\n");
    }

    static void _PerformMainMenueChoice(enMainMenueOptions choice)
    {
        switch (choice)
        {
        case eShowClientsList:
            _PrintClientsList();
            break;
        case eGetTotalBalances:
            _PrintTotalBalances();
            break;
        case eFindClient:
            _FindAndShowClient();
            break;
        case eAddNewClient:
            _AddNewClient();
            break;
        case eUpdateClientData:
            _UpdateClientData();
            break;
        case eDeleteClient:
            _DeleteClient();
            break;
        case eTransactionsMenue:
            _ShowTransactionsMenue();
            break;
        case eManageUsersMenue:
            _ShowUsersMenue();
            break;
        case eLogout:
            return;
        default:
            std::cout << spaces << "Invalid choice. Please try again.\n";
            break;
        }
        clsScreen::_PauseScreen();
        ShowMainMenue();
    }


public:
    static void ShowMainMenue()
    {
        system("cls");
        _PrintHeader("Main Screen");
        std::cout << clsScreen::spaces << "[1] Show Clients List.\n";
        std::cout << clsScreen::spaces << "[2] Get Total Balances.\n";
        std::cout << clsScreen::spaces << "[3] Find Client.\n";
        std::cout << clsScreen::spaces << "[4] Add New Client.\n";
        std::cout << clsScreen::spaces << "[5] Update Client Data.\n";
        std::cout << clsScreen::spaces << "[6] Delete Client.\n";
        std::cout << clsScreen::spaces << "[7] Transactions Menue.\n";
        std::cout << clsScreen::spaces << "[8] Manage Useres Menue\n";
        std::cout << clsScreen::spaces << "[9] Logout.\n\n";
        std::cout << clsScreen::spaces << "=============================================\n\n";
        
        enMainMenueOptions choice = (enMainMenueOptions)MyInputLibrary::ReadNumberBetween(1, 9, spaces + "Choose what do you want to do? [1-9]: ");

        _PerformMainMenueChoice(choice);
    }
};