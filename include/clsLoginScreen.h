#pragma once
#include "clsScreen.h"

class clsLoginScreen :
    protected clsScreen
{
private:

public:
    static void ShowLoginScreen()
    {
        clsScreen::_PrintHeader("Login Screen");
        clsScreen::Print("_____________________\n"); 
        clsScreen::Print("\n");
        clsScreen::Print("Enter Username: ");
        clsScreen::Print("\n");
        clsScreen::Print("Enter Password: ");
        clsScreen::Print("\n");
        clsScreen::Print("_____________________\n");
        clsScreen::_PauseScreen();
    }
};

