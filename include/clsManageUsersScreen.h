#pragma once
#include "clsScreen.h"
#include "MyInputLibrary.h"
#include "clsUserListScreen.h"
#include "clsFindUserScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "Global.h"

class clsManageUsersScreen : protected clsScreen
{
private:
    enum enMngUsersMenueOption
    {
        eShowUsersList = 1,
        eFindUser = 2,
        eAddNewUser = 3,
        eUpdateUserData = 4,
        eDeleteUser = 5,
        eMainMenue = 6
    };

    static void _PerformManageUsersMenueOption(enMngUsersMenueOption choice)
    {
        switch (choice) {
            case eShowUsersList:
                system("cls");
                clsUserListScreen::ShowUsersListScreen();
                break;
            case eFindUser: 
                system("cls");
                clsFindUserScreen::ShowFindUserScreen();
                break;
            case eAddNewUser:
                system("cls");
                clsAddNewUserScreen::ShowAddNewUserScreen();
                break;
            case eUpdateUserData:
                system("cls");
                clsUpdateUserScreen::ShowUpdateUserScreen();
                break;
            case eDeleteUser:
                system("cls");
                clsDeleteUserScreen::ShowDeleteUserScreen();
                break;
            case eMainMenue:
                return;
             default:
                _Print("Invalid choice. Please try again.\n");
                break;
        }
        _Print("\n\n");
        _PauseScreen("Press any key to return to the Manage Users Menu...");
    }

public:
    static void ShowManageUsersScreen()
    {
        enMngUsersMenueOption choice = enMngUsersMenueOption::eAddNewUser; // Initialize with a default value to enter the loop
        while (choice != eMainMenue)
        {
            system("cls");
            _PrintHeader("Manage Users Screen", 5);
            _Print("=================================\n");
            _Print(" [1] Show Users List.\n");
            _Print(" [2] Find User.\n");
            _Print(" [3] Add New User.\n");
            _Print(" [4] Update User Data.\n");
            _Print(" [5] Delete User.\n");
            _Print(" [6] Main Menue.\n");
            _Print("=================================\n");
            _Print("\n"); _Print("");
            choice = (enMngUsersMenueOption)MyInputLibrary::ReadNumberBetween(1, 6, "Choose what do you want to do? [1-6]: ");
            _PerformManageUsersMenueOption(choice);
        }

    }

};

