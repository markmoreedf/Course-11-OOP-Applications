#pragma once
#include "clsScreen.h"
class clsUpdateUserScreen :protected clsScreen
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
    static void _PrintOldVsNewUserData(const clsUser& OldUser, const clsUser& NewUser)
    {
        short labelWidth = 12;         // Align the colons :
        short firstCardWidth = 40;     // Space between the start of card 1 and card 2

        std::cout << spaces << "\n";
        std::cout << spaces << setw(firstCardWidth) << left << "      Old User Data" << "      New User Data" << endl;
        std::cout << spaces << setw(firstCardWidth) << left << "==============================" << "==============================" << endl;

        // Helper Lambda function to print a row
        auto printRow = [&](string label, string val1, string val2) {

            std::cout << spaces;
            string firstCardPart = "";

            // static cast to std::streamsize to avoid narrowing conversion warning
            std::cout << left << setw(labelWidth) << label << ": " << setw(static_cast<std::streamsize>(firstCardWidth) - static_cast<std::streamsize>(labelWidth) - 2) << val1; 
            std::cout << left << setw(labelWidth) << label << ": " << val2 << endl;
            };

        printRow("First Name", OldUser.FirstName, NewUser.FirstName);
        printRow("Last Name", OldUser.LastName, NewUser.LastName);
        printRow("Email", OldUser.Email, NewUser.Email);
        printRow("Phone", OldUser.Phone, NewUser.Phone);
        printRow("Password", OldUser.Password, NewUser.Password);
        printRow("Permissions", to_string(OldUser.Permissions), to_string(NewUser.Permissions));

        std::cout << clsScreen::spaces << setw(firstCardWidth) << left << "==============================" << "==============================" << endl;
    }

public:
    static void ShowUpdateUserScreen()
    {
        _PrintHeader("Update User Screen", 5);
        _Print("");
        string username = MyInputLibrary::ReadLine("Enter Username to update: ");
        clsUser user = clsUser::FindUser(username);

        while (user.IsEmpty()) {
            _Print("The Username: " + username + " not found.\n");
            _Print("");
            username = MyInputLibrary::ReadLine("Enter Username to Update: ");
            user = clsUser::FindUser(username);
        }
        _Print("\nCurrent User Data:\n");

        _PrintUserCard(user);
        clsUser newUserData = user; // to hold old data before updating
        _Print("Please enter new data for the user:\n");
        _ReadUserData(newUserData);

        _PrintOldVsNewUserData(user, newUserData);

        std::cout << "\t";     _Print(""); // just to allign the msg of the next line
        if (!MyInputLibrary::ReadYesNo("Do you want to update this user? (Y/N): "))
        {
            std::cout << "\n";
            _Print("Update cancelled by user.\n");
            return;
        }

        clsUser::enSaveResults saveResult = newUserData.Save();
        if (saveResult == clsUser::svSucceeded)
        {
            _Print("\n");
            _Print("Client data updated successfully.\n");
        }
        else
        {
            _Print("\n");
            _Print("Failed to update client data.\n");
        }
    
    }
};

