#pragma once
#include "clsScreen.h"
#include "clsUser.h"
class clsAddNewUserScreen :   protected clsScreen
{
private:
    static void _ReadUserPermissions(clsUser& user)
    {
        std::cout << "\n";     Print("Set User Permissions:\n");         Print("");

        if (MyInputLibrary::ReadYesNo("Do you want to give full access ? [y/n]\t"))
        {
            user.Permissions = clsUser::enUserPermissions::fullAccess;
        }
        else {
            Print("");
            if (MyInputLibrary::ReadYesNo("Give access to View Clients? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::showClientList;
            else
                user.Permissions &= ~clsUser::enUserPermissions::showClientList;

            Print("");
            if (MyInputLibrary::ReadYesNo("Give access to Find Clients? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::findClient;
            else
                user.Permissions &= ~clsUser::enUserPermissions::findClient;

            Print("");
            if (MyInputLibrary::ReadYesNo("Give access to Add Clients? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::addClient;
            else
                user.Permissions &= ~clsUser::enUserPermissions::addClient;

            Print("");
            if (MyInputLibrary::ReadYesNo("Give access to Update Clients? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::updateClient;
            else
                user.Permissions &= ~clsUser::enUserPermissions::updateClient;

            Print("");
            if (MyInputLibrary::ReadYesNo("Give access to Delete Clients? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::deleteClient;
            else
                user.Permissions &= ~clsUser::enUserPermissions::deleteClient;

            Print("");
            if (MyInputLibrary::ReadYesNo("Give access to Transactions? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::transactions;
            else
                user.Permissions &= ~clsUser::enUserPermissions::transactions;

            Print("");
            if (MyInputLibrary::ReadYesNo("Give access to Manage Users? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::manageUsers;
            else
                user.Permissions &= ~clsUser::enUserPermissions::manageUsers;
            Print("");
            if (MyInputLibrary::ReadYesNo("Give access to Show Login History? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::showLoginHistory;
            else
                user.Permissions &= ~clsUser::enUserPermissions::showLoginHistory;
        }
    }
    static void _ReadUserData(clsUser& user)
    {
        Print("Please enter the following user data:\n");
        Print("");  user.FirstName = MyInputLibrary::ReadLine("First Name: ");
        Print("");  user.LastName = MyInputLibrary::ReadLine("Last Name: ");
        Print("");  user.Email = MyInputLibrary::ReadLine("Email: ");
        Print("");  user.Phone = MyInputLibrary::ReadLine("Phone: ");
        Print("");  user.Password = MyInputLibrary::ReadLine("Password: ");
        _ReadUserPermissions(user);
    }

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
    static void ShowAddNewUserScreen()
    {
        _PrintHeader("Add New User Screen", 5);
    
        Print("");
        string usename = MyInputLibrary::ReadLine("Enter New Username: ");
        while (clsUser::IsUserExist(usename))
        {
            Print("Username already exists. Please enter a different one.\n");
            Print("");
            usename = MyInputLibrary::ReadLine("Enter New Username: ");
        }
        clsUser newUser = clsUser::GetAddNewUserObject(usename);
        _ReadUserData(newUser);

        _Print(newUser);
        Print(""); // just to allign the msg of the next line
        if (!MyInputLibrary::ReadYesNo("Do you want to add this user? (Y/N): "))
        {
            Print("Operation is cancelled. User is not added.\n");
            return;
        }

        clsUser::enSaveResults saveResult = newUser.Save();
        switch (saveResult)
        {
            case clsUser::svFailedEmptyObject:
                Print("Error: Failed to save user. Empty user object.\n");
                break;
            case clsUser::svUserNameExists:
                Print("Error: Username already exists. User not added.\n");
                break;
            case clsUser::svSucceeded:
                Print("User added successfully.\n");
                break;
             default:
                Print("An unknown error occurred while saving the user.\n");
                break;

        }
    }
    

};

