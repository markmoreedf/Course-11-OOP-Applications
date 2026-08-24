#pragma once
#include "clsScreen.h"
class clsDeleteUserScreen :protected clsScreen
{
private:
    static void _PrintUserCard(clsUser& user)
    {
        string permissionsStr = to_string(user.Permissions);
        string passwordStr = user.Password;

        if (user.UserName == "admin")
        {
            permissionsStr = "Full Access";
            passwordStr = "********";
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

    static void ShowDeleteUserScreen()
    {
        _PrintHeader("Delete User Screen", 5);
        _Print("");   // shifting line for better output format
        std::string username = MyInputLibrary::ReadLine("Enter Username to Delete: ");
        clsUser user = clsUser::FindUser(username);

        while (user.IsEmpty())
        {
            _Print("The Username: " + username + " was NOT found.\n");
            _Print("");      username = MyInputLibrary::ReadLine("Enter Username to Delete: ");
            user = clsUser::FindUser(username);
        }

        _PrintUserCard(user);

        _Print("");
        if (!MyInputLibrary::ReadYesNo("Are you sure you want to delete this user? (Y/N): "))
        {
            _Print("User deletion cancelled by user.\n");
            return;
        }

        switch (user.Delete())
        {
            case clsUser::enDeleteResults::dlAdminDeleteAttempt:
                _Print("Deleting admin user is not allowed.\n");
                break;
            case clsUser::enDeleteResults::dlNotFound:
                _Print("User not found. Deletion failed.\n");
                break;
            case clsUser::enDeleteResults::dlSucceeded:
                 _Print("User Deleted Successfully.\n");
                 break;
            default:
                _Print("An unexpected error occurred during deletion.\n");
                break;
        }

    }



};

