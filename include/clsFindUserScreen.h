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

        if (user.UserName == "admin")
        {
            permissionsStr = "Full Access";
            passwordStr =  "********";
        }

        Print("\n");
        Print("        User Card\n");
        Print("=============================\n");
        Print(" First Name  : " + user.FirstName + "\n");
        Print(" Last Name   : " + user.LastName + "\n");
        Print(" Email       : " + user.Email + "\n");
        Print(" Phone       : " + user.Phone + "\n");
        Print(" UserName.   : " + user.UserName + "\n");
        Print(" Password    : " + passwordStr + "\n");
        Print(" Permissions : " + permissionsStr + "\n");
        Print("=============================\n\n");
    }

public:

    static void ShowFindUserScreen()
    {
        _PrintHeader("Find User Screen", 5);
        Print(""); std::string username = MyInputLibrary::ReadLine("Enter Username: ");
        clsUser user = clsUser::FindUser(username);
        while (user.IsEmpty()) {
            Print("User with Useruame " + username + " not found.\n");
            Print("");
            username = MyInputLibrary::ReadLine("Enter a Valid Username: ");
            user = clsUser::FindUser(username);
        }

        _Print(user);
    }

};
