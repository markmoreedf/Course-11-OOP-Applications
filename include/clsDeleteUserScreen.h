#pragma once
#include "clsScreen.h"
class clsDeleteUserScreen :protected clsScreen
{
private:

public:
    static void ShowDeleteUserScreen()
    {
        _PrintHeader("Delete User Screen", 5);
        clsScreen::Print("Here will be delete user screen\n");
    }

};

