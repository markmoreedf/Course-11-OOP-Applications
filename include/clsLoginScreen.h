#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "Global.h"

class clsLoginScreen :  protected clsScreen
{
private:
    static void _PerformLoginScreen()
    {
        string username = "";
        string password = "";
        bool loginFail = true;

        do
        {   
            clsScreen::Print("_____________________\n\n"); 
            clsScreen::Print("Enter Username: ");  username = MyInputLibrary::ReadWord("");     clsScreen::Print("\n");
            clsScreen::Print("Enter Password: ");  password = MyInputLibrary::ReadWord("");     clsScreen::Print("\n");
            clsScreen::Print("_____________________\n");

            CurrentUser = clsUser::FindUser(username, password);
            loginFail = CurrentUser.IsEmpty();

            if (loginFail)
            {
                clsScreen::Print("\n");
                clsScreen::Print("<<< Invalid username or password. Please try again. >>>\n\n");
            }

        } while (loginFail);

    }
public:
    static void ShowLoginScreen()
    {
        clsScreen::_PrintHeader("Login Screen");
        _PerformLoginScreen();
        clsScreen::_PauseScreen();
    }
};
