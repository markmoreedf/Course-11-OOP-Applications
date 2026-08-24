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
            _Print("Login Attempts: " + to_string(loginAttempts) + "\n"); 
            _Print("_____________________\n\n"); 
            _Print("Enter Username: ");  username = MyInputLibrary::ReadWord("");     _Print("\n");
            _Print("Enter Password: ");  password = MyInputLibrary::ReadWord("");     _Print("\n");
            _Print("_____________________\n");

            CurrentUser = clsUser::FindUser(username, password);
            loginFail = CurrentUser.IsEmpty();

            if (loginFail)
            {
                loginAttempts--;
                if (loginAttempts <= 0)
                {
                    _Print("\n");
                    _Print("<<< You have exceeded the maximum number of login attempts. Exiting the program. >>>\n\n");
                    return false;
                }
                _Print("\n");
                _Print("<<< Invalid username or password. Please try again. >>>\n\n");
            }

        } while (loginFail);

        CurrentUser.RegisterLogin();
        return true;
    }
public:
    static bool ShowLoginScreen()
    {
        _PrintHeader("Login Screen");
        bool loginResult = _PerformLoginScreen();
        return loginResult;
    }
};
