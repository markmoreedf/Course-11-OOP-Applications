#pragma once
#include "clsScreen.h"
#include "MyInputLibrary.h"
#include "clsUser.h"
class clsFindUserScreen : protected clsScreen
{
private:

    static void _PrintUserCard(clsUser& user)
    {
        string permissionsStr = to_string(user.Permissions);
        string passwordStr = user.Password;

        if (user.UserName == "admin")
        {
            permissionsStr = "Full Access";
            passwordStr =  "********";
        }

        _Print("\n");
        _Print("        User Card\n");
        _Print("=============================\n");
        _Print(" First Name  : " + user.FirstName + "\n");
        _Print(" Last Name   : " + user.LastName + "\n");
        _Print(" Email       : " + user.Email + "\n");
        _Print(" Phone       : " + user.Phone + "\n");
        _Print(" UserName.   : " + user.UserName + "\n");
        _Print(" Password    : " + passwordStr + "\n");
        _Print(" Permissions : " + permissionsStr + "\n");
        _Print("=============================\n\n");
    }

public:

    static void ShowFindUserScreen()
    {
        _PrintHeader("Find User Screen", 5);
        _Print(""); std::string username = MyInputLibrary::ReadLine("Enter Username: ");
        clsUser user = clsUser::FindUser(username);
        while (user.IsEmpty()) {
            _Print("User with Useruame " + username + " not found.\n");
            _Print("");
            username = MyInputLibrary::ReadLine("Enter a Valid Username: ");
            user = clsUser::FindUser(username);
        }

        _PrintUserCard(user);
    }

};
