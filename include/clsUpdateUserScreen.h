#pragma once
#include "clsScreen.h"
class clsUpdateUserScreen :protected clsScreen
{
private:




public:
    static void ShowUpdateUserScreen()
    {
        _PrintHeader("Update User Screen", 5);
        clsScreen::Print("Here will be update user data screen\n");
    }
};

