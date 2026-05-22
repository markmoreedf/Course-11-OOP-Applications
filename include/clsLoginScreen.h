#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "MyInputLibrary.h"

class clsLoginScreen :
    protected clsScreen
{
public:
    // Make UserPermissions static so it can be set from static methods
    inline static clsUser::enUserPermissions CurrentUserPermissions;
private:
    static void _PerformLoginScreen(string & username, string & password)
    {
        clsUser currentUser = clsUser::FindUser(username, password);
        while (currentUser.IsEmpty())
        {
            clsScreen::Print("\n");
            clsScreen::Print("<<< Invalid username or password. Please try again. >>>\n\n");
            clsScreen::Print("_____________________\n\n"); 
            clsScreen::Print("Enter Username: ");  username = MyInputLibrary::ReadWord();     clsScreen::Print("\n");
            clsScreen::Print("Enter Password: ");  password = MyInputLibrary::ReadWord();     clsScreen::Print("\n");
            clsScreen::Print("_____________________\n"); 
            currentUser = clsUser::FindUser(username, password);
        }
        // Assign permissions from the logged-in user
        CurrentUserPermissions = static_cast<clsUser::enUserPermissions>(currentUser.Permissions);
    }
public:
    static void ShowLoginScreen()
    {
        clsScreen::_PrintHeader("Login Screen");
        clsScreen::Print("_____________________\n\n"); 
        clsScreen::Print("Enter Username: ");  std::string username = MyInputLibrary::ReadWord();     clsScreen::Print("\n");
        clsScreen::Print("Enter Password: ");  std::string password = MyInputLibrary::ReadWord();     clsScreen::Print("\n");
        clsScreen::Print("_____________________\n");
        _PerformLoginScreen(username, password);
        clsScreen::_PauseScreen();
    }
};
