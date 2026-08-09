#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "Global.h"

class clsLoginScreen :  protected clsScreen
{
private:

    static bool _PerformLoginScreen()
    {
        string username = "";
        string password = "";
        short loginAttempts = 3;
        bool loginFail = true;

        do
        {   
            clsScreen::Print("Login Attempts: " + to_string(loginAttempts) + "\n"); 
            clsScreen::Print("_____________________\n\n"); 
            clsScreen::Print("Enter Username: ");  username = MyInputLibrary::ReadWord("");     clsScreen::Print("\n");
            clsScreen::Print("Enter Password: ");  password = MyInputLibrary::ReadWord("");     clsScreen::Print("\n");
            clsScreen::Print("_____________________\n");

            CurrentUser = clsUser::FindUser(username, password);
            loginFail = CurrentUser.IsEmpty();

            if (loginFail)
            {
                loginAttempts--;
                if (loginAttempts <= 0)
                {
                    clsScreen::Print("\n");
                    clsScreen::Print("<<< You have exceeded the maximum number of login attempts. Exiting the program. >>>\n\n");
                    return false;
                }
                clsScreen::Print("\n");
                clsScreen::Print("<<< Invalid username or password. Please try again. >>>\n\n");
            }

        } while (loginFail);

        CurrentUser.RegisterLogin();
        return true;
    }
public:
    static bool ShowLoginScreen()
    {
        clsScreen::_PrintHeader("Login Screen");
        bool loginResult = _PerformLoginScreen();
        clsScreen::_PauseScreen();
        return loginResult;
    }
};
