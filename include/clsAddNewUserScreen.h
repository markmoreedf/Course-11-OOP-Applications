#pragma once
#include "clsScreen.h"
class clsAddNewUserScreen :   protected clsScreen
{
private:

public:
    static void ShowAddNewUserScreen()
    {
        _PrintHeader("Add New User Screen", 5);
        clsScreen::Print("Here will be add new user screen\n");
    }

};

