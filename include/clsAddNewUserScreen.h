#pragma once
#include "clsScreen.h"
#include "clsUser.h"
class clsAddNewUserScreen :   protected clsScreen
{
private:
    static void _ReadUserPermissions(clsUser& user)
    {
        std::cout << "\n";     _Print("Set User Permissions:\n");         _Print("");

        if (MyInputLibrary::ReadYesNo("Do you want to give full access ? [y/n]\t"))
        {
            user.Permissions = clsUser::enUserPermissions::fullAccess;
        }
        else {
            _Print("");
            if (MyInputLibrary::ReadYesNo("Give access to View Clients? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::showClientList;
            else
                user.Permissions &= ~clsUser::enUserPermissions::showClientList;

            _Print("");
            if (MyInputLibrary::ReadYesNo("Give access to Find Clients? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::findClient;
            else
                user.Permissions &= ~clsUser::enUserPermissions::findClient;

            _Print("");
            if (MyInputLibrary::ReadYesNo("Give access to Add Clients? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::addClient;
            else
                user.Permissions &= ~clsUser::enUserPermissions::addClient;

            _Print("");
            if (MyInputLibrary::ReadYesNo("Give access to Update Clients? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::updateClient;
            else
                user.Permissions &= ~clsUser::enUserPermissions::updateClient;

            _Print("");
            if (MyInputLibrary::ReadYesNo("Give access to Delete Clients? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::deleteClient;
            else
                user.Permissions &= ~clsUser::enUserPermissions::deleteClient;

            _Print("");
            if (MyInputLibrary::ReadYesNo("Give access to Transactions? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::transactions;
            else
                user.Permissions &= ~clsUser::enUserPermissions::transactions;

            _Print("");
            if (MyInputLibrary::ReadYesNo("Give access to Manage Users? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::manageUsers;
            else
                user.Permissions &= ~clsUser::enUserPermissions::manageUsers;
            _Print("");
            if (MyInputLibrary::ReadYesNo("Give access to Show Login History? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::showLoginHistory;
            else
                user.Permissions &= ~clsUser::enUserPermissions::showLoginHistory;
        }
    }
    static void _ReadUserData(clsUser& user)
    {
        _Print("Please enter the following user data:\n");
        _Print("");  user.FirstName = MyInputLibrary::ReadLine("First Name: ");
        _Print("");  user.LastName = MyInputLibrary::ReadLine("Last Name: ");
        _Print("");  user.Email = MyInputLibrary::ReadLine("Email: ");
        _Print("");  user.Phone = MyInputLibrary::ReadLine("Phone: ");
        _Print("");  user.Password = MyInputLibrary::ReadLine("Password: ");
        _ReadUserPermissions(user);
    }

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
    static void ShowAddNewUserScreen()
    {
        _PrintHeader("Add New User Screen", 5);
    
        _Print("");
        string usename = MyInputLibrary::ReadLine("Enter New Username: ");
        while (clsUser::IsUserExist(usename))
        {
            _Print("Username already exists. Please enter a different one.\n");
            _Print("");
            usename = MyInputLibrary::ReadLine("Enter New Username: ");
        }
        clsUser newUser = clsUser::GetAddNewUserObject(usename);
        _ReadUserData(newUser);

        _PrintUserCard(newUser);
        _Print(""); // just to allign the msg of the next line
        if (!MyInputLibrary::ReadYesNo("Do you want to add this user? (Y/N): "))
        {
            _Print("Operation is cancelled. User is not added.\n");
            return;
        }

        clsUser::enSaveResults saveResult = newUser.Save();
        switch (saveResult)
        {
            case clsUser::svFailedEmptyObject:
                _Print("Error: Failed to save user. Empty user object.\n");
                break;
            case clsUser::svUserNameExists:
                _Print("Error: Username already exists. User not added.\n");
                break;
            case clsUser::svSucceeded:
                _Print("User added successfully.\n");
                break;
             default:
                _Print("An unknown error occurred while saving the user.\n");
                break;

        }
    }
    

};

