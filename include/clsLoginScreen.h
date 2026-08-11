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
            Print("Login Attempts: " + to_string(loginAttempts) + "\n"); 
            Print("_____________________\n\n"); 
            Print("Enter Username: ");  username = MyInputLibrary::ReadWord("");     Print("\n");
            Print("Enter Password: ");  password = MyInputLibrary::ReadWord("");     Print("\n");
            Print("_____________________\n");

            CurrentUser = clsUser::FindUser(username, password);
            loginFail = CurrentUser.IsEmpty();

            if (loginFail)
            {
                loginAttempts--;
                if (loginAttempts <= 0)
                {
                    Print("\n");
                    Print("<<< You have exceeded the maximum number of login attempts. Exiting the program. >>>\n\n");
                    return false;
                }
                Print("\n");
                Print("<<< Invalid username or password. Please try again. >>>\n\n");
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
