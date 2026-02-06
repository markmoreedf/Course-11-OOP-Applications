#pragma once
#include "clsScreen.h"
class clsFindUserScreen : protected clsScreen
{
private:
    static void _ReturnToFindUserScreen()
    {
        clsScreen::Print("\n\n");
        clsScreen::_PauseScreen();
        ShowFindUserScreen();
    }

public:
    static void ShowFindUserScreen()
    {
        _PrintHeader("Find User Screen", 5);
        clsScreen::Print("Here will be find user screen\n");
    }
};

