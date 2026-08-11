
#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "MyInputLibrary.h"
#include "Global.h"

class clsLogoutScreen : protected clsScreen
{
public:
    static bool Logout()
    {
        Print("\n\n");
        Print("Are you sure you want to logout? [y/n]: ");
        bool choice = MyInputLibrary::ReadYesNo("");
        if (choice)
        {
            CurrentUser = clsUser::FindUser("", "");
            Print("\n\n");
            _PauseScreen("<<< You have been logged out successfully. >>>\n\n");
            return true;
        }
        return false;
    }
};
