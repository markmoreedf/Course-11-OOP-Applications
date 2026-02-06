#pragma once
#include "clsScreen.h"
class clsUserListScreen :   protected clsScreen
{
private:



public:
    static void ShowUserListScreen()
    {
        _PrintHeader("Users List Screen", 5);
        clsScreen::Print("Here will be show users list screen\n");
    }
};

