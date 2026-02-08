#pragma once
#include "clsScreen.h"
#include "MyInputLibrary.h"
#include "clsUser.h"
class clsFindUserScreen : protected clsScreen
{
private:

    static void _Print(clsUser& user)
    {
        string permissionsStr = to_string(user.Permissions);
        string passwordStr = user.Password;

        if (user.Username == "admin")
        {
            permissionsStr = "Full Access";
            passwordStr =  "********";
        }

        clsScreen::Print("\n");
        clsScreen::Print("        User Card\n");
        clsScreen::Print("=============================\n");
        clsScreen::Print(" First Name  : " + user.FirstName + "\n");
        clsScreen::Print(" Last Name   : " + user.LastName + "\n");
        clsScreen::Print(" Email       : " + user.Email + "\n");
        clsScreen::Print(" Phone       : " + user.Phone + "\n");
        clsScreen::Print(" UserName.   : " + user.Username + "\n");
        clsScreen::Print(" Password    : " + passwordStr + "\n");
        clsScreen::Print(" Permissions : " + permissionsStr + "\n");
        clsScreen::Print("=============================\n\n");
    }

public:

    static void ShowFindUserScreen()
    {
        clsScreen::_PrintHeader("Find User Screen", 5);
        clsScreen::Print(""); std::string username = MyInputLibrary::ReadLine("Enter Username: ");
        clsUser user = clsUser::FindUser(username);
        while (user.IsEmpty()) {
            clsScreen::Print("User with Useruame " + username + " not found.\n");
            clsScreen::Print("");
            username = MyInputLibrary::ReadLine("Enter a Valid Username: ");
            user = clsUser::FindUser(username);
        }

        _Print(user);
    }

};
