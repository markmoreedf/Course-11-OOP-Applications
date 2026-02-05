#pragma once
#include "clsScreen.h"
#include "MyInputLibrary.h"

class clsManageUsersScreen : private clsScreen
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
                clsScreen::Print("Here will be show users list screen\n");
                break;
            case eFindUser: 
                system("cls");
                clsScreen::Print("Here will be find user screen\n");
                break;
            case eAddNewUser:
                system("cls");
                clsScreen::Print("Here will be add new user screen\n");
                break;
            case eUpdateUserData:
                system("cls");
                clsScreen::Print("Here will be update user data screen\n");
                break;
            case eDeleteUser:
                system("cls");
                clsScreen::Print("Here will be delete user screen\n");
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

