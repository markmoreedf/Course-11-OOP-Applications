#pragma once
#include "clsScreen.h"
#include "clsUser.h"
class clsAddNewUserScreen :   protected clsScreen
{
private:
    static void _ReadUserData(clsUser& user)
    {
        clsScreen::Print("Please enter the following user data:\n");
        clsScreen::Print("");  user.FirstName = MyInputLibrary::ReadLine("First Name: ");
        clsScreen::Print("");  user.LastName = MyInputLibrary::ReadLine("Last Name: ");
        clsScreen::Print("");  user.Email = MyInputLibrary::ReadLine("Email: ");
        clsScreen::Print("");  user.Phone = MyInputLibrary::ReadLine("Phone: ");
        clsScreen::Print("");  user.Password = MyInputLibrary::ReadLine("Password: ");
        clsScreen::Print("");  user.Permissions = MyInputLibrary::ReadPositiveDouble("permission: ");
    }

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
    static void ShowAddNewUserScreen()
    {
        clsScreen::_PrintHeader("Add New User Screen", 5);
    
        clsScreen::Print("");
        string usename = MyInputLibrary::ReadLine("Enter New Username: ");
        while (clsUser::IsUserExist(usename))
        {
            clsScreen::Print("Username already exists. Please enter a different one.\n");
            clsScreen::Print("");
            usename = MyInputLibrary::ReadLine("Enter New Username: ");
        }
        clsUser newUser = clsUser::GetAddNewUserObject(usename);
        _ReadUserData(newUser);

        _Print(newUser);
        clsScreen::Print(""); // just to allign the msg of the next line
        if (!MyInputLibrary::ReadYesNo("Do you want to add this user? (Y/N): "))
        {
            clsScreen::Print("Operation cancelled. User not added.\n");
            return;
        }

        clsUser::enSaveResults saveResult = newUser.Save();
        switch (saveResult)
        {
            case clsUser::svFailedEmptyObject:
                clsScreen::Print("Error: Failed to save user. Empty user object.\n");
                break;
            case clsUser::svUserNameExists:
                clsScreen::Print("Error: Username already exists. User not added.\n");
                break;
            case clsUser::svSucceeded:
                clsScreen::Print("User added successfully.\n");
                break;
             default:
                clsScreen::Print("An unknown error occurred while saving the user.\n");
                break;

        }
    }
    

};

