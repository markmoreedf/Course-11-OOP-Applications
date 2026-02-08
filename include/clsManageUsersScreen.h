#pragma once
#include "clsScreen.h"
#include "MyInputLibrary.h"
#include "clsUserListScreen.h"
#include "clsFindUserScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsDeleteUserScreen.h"

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

    static void _ReturnToManageUsersMenue()
    {
        clsScreen::Print("\n\n");
        clsScreen::_PauseScreen();
        ShowManageUsersScreen();
    }
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
                clsScreen::Print("Invalid choice. Please try again.\n");
                break;
        }
        _ReturnToManageUsersMenue();
    }

public:
    static void ShowManageUsersScreen()
    {
        system("cls");
        _PrintHeader("Manage Users Screen", 5);
        clsScreen::Print("=================================\n");
        clsScreen::Print(" [1] Show Users List.\n");
        clsScreen::Print(" [2] Find User.\n");
        clsScreen::Print(" [3] Add New User.\n");
        clsScreen::Print(" [4] Update User Data.\n");
        clsScreen::Print(" [5] Delete User.\n");
        clsScreen::Print(" [6] Main Menue.\n");
        clsScreen::Print("=================================\n");
        clsScreen::Print("\n"); clsScreen::Print("");
        _PerformManageUsersMenueOption ((enMngUsersMenueOption)MyInputLibrary::ReadNumberBetween(1, 6, "Choose what do you want to do? [1-6]: "));

    }

};

