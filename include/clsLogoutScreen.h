
#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "MyInputLibrary.h"
#include "Global.h"

class clsLogoutScreen : protected clsScreen
{

private:
    static void _PerformLogoutScreen()
    {
        clsScreen::Print("\n\n");
        clsScreen::Print("Are you sure you want to logout? [y/n]: ");
        bool choice = MyInputLibrary::ReadYesNo("");
        if (choice)
        {
            CurrentUser = clsUser::FindUser("", "");
            clsScreen::Print("\n\n");
            clsScreen::Print("<<< You have been logged out successfully. >>>\n\n");
            clsScreen::_PauseScreen();
        }
    }

public:
    static void Logout()
    {
        _PerformLogoutScreen();
    }
};
