#pragma once
#include "clsScreen.h"
class clsDeleteUserScreen :protected clsScreen
{
private:
    static void _Print(clsUser& user)
    {
        string permissionsStr = to_string(user.Permissions);
        string passwordStr = user.Password;

        if (user.Username == "admin")
        {
            permissionsStr = "Full Access";
            passwordStr = "********";
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

    static void ShowDeleteUserScreen()
    {
        clsScreen::_PrintHeader("Delete User Screen", 5);
        clsScreen::Print("");   // shifting line for better output format
        std::string username = MyInputLibrary::ReadLine("Enter Username to Delete: ");
        clsUser user = clsUser::FindUser(username);

        while (user.IsEmpty())
        {
            clsScreen::Print("The Username: " + username + " was NOT found.\n");
            clsScreen::Print("");      username = MyInputLibrary::ReadLine("Enter Username to Delete: ");
            user = clsUser::FindUser(username);
        }

        _Print(user);

        clsScreen::Print("");
        if (!MyInputLibrary::ReadYesNo("Are you sure you want to delete this user? (Y/N): "))
            return;

        switch (user.Delete())
        {
            case clsUser::enDeleteResults::dlAdminDeleteAttempt:
                clsScreen::Print("Deleting admin user is not allowed.\n");
                break;
            case clsUser::enDeleteResults::dlCancelledByUser:
                clsScreen::Print("User deletion cancelled by user.\n");
                break;
            case clsUser::enDeleteResults::dlNotFound:
                clsScreen::Print("User not found. Deletion failed.\n");
                break;
            case clsUser::enDeleteResults::dlSucceeded:
                 clsScreen::Print("User Deleted Successfully.\n");
                 break;
            default:
                clsScreen::Print("An unexpected error occurred during deletion.\n");
                break;
        }

    }



};

