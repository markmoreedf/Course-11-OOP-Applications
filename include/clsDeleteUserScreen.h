#pragma once
#include "clsScreen.h"
class clsDeleteUserScreen :protected clsScreen
{
private:
    static void _Print(clsUser& user)
    {
        string permissionsStr = to_string(user.Permissions);
        string passwordStr = user.Password;

        if (user.UserName == "admin")
        {
            permissionsStr = "Full Access";
            passwordStr = "********";
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

    static void ShowDeleteUserScreen()
    {
        _PrintHeader("Delete User Screen", 5);
        Print("");   // shifting line for better output format
        std::string username = MyInputLibrary::ReadLine("Enter Username to Delete: ");
        clsUser user = clsUser::FindUser(username);

        while (user.IsEmpty())
        {
            Print("The Username: " + username + " was NOT found.\n");
            Print("");      username = MyInputLibrary::ReadLine("Enter Username to Delete: ");
            user = clsUser::FindUser(username);
        }

        _Print(user);

        Print("");
        if (!MyInputLibrary::ReadYesNo("Are you sure you want to delete this user? (Y/N): "))
        {
            Print("User deletion cancelled by user.\n");
            return;
        }

        switch (user.Delete())
        {
            case clsUser::enDeleteResults::dlAdminDeleteAttempt:
                Print("Deleting admin user is not allowed.\n");
                break;
            case clsUser::enDeleteResults::dlNotFound:
                Print("User not found. Deletion failed.\n");
                break;
            case clsUser::enDeleteResults::dlSucceeded:
                 Print("User Deleted Successfully.\n");
                 break;
            default:
                Print("An unexpected error occurred during deletion.\n");
                break;
        }

    }



};

