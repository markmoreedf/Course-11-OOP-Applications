#pragma once
#include "clsScreen.h"
class clsUpdateUserScreen :protected clsScreen
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
    static void _ReadUserPermissions(clsUser& user)
    {
        std::cout << "\n";     clsScreen::Print("Set User Permissions:\n");         clsScreen::Print("");

        if (MyInputLibrary::ReadYesNo("Do you want to give full access ? [y/n]\t"))
        {
            user.Permissions = 127;
        }
        else {
            clsScreen::Print("");
            if (MyInputLibrary::ReadYesNo("Give access to View Clients? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::showClientList;
            else
                user.Permissions &= ~clsUser::enUserPermissions::showClientList;

            clsScreen::Print("");
            if (MyInputLibrary::ReadYesNo("Give access to Find Clients? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::findClient;
            else
                user.Permissions &= ~clsUser::enUserPermissions::findClient;

            clsScreen::Print("");
            if (MyInputLibrary::ReadYesNo("Give access to Add Clients? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::addClient;
            else
                user.Permissions &= ~clsUser::enUserPermissions::addClient;

            clsScreen::Print("");
            if (MyInputLibrary::ReadYesNo("Give access to Update Clients? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::updateClient;
            else
                user.Permissions &= ~clsUser::enUserPermissions::updateClient;

            clsScreen::Print("");
            if (MyInputLibrary::ReadYesNo("Give access to Delete Clients? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::deleteClient;
            else
                user.Permissions &= ~clsUser::enUserPermissions::deleteClient;

            clsScreen::Print("");
            if (MyInputLibrary::ReadYesNo("Give access to Transactions? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::transactions;
            else
                user.Permissions &= ~clsUser::enUserPermissions::transactions;

            clsScreen::Print("");
            if (MyInputLibrary::ReadYesNo("Give access to Manage Users? [y/n]\t"))
                user.Permissions |= clsUser::enUserPermissions::manageUsers;
            else
                user.Permissions &= ~clsUser::enUserPermissions::manageUsers;
        }
    }
    static void _ReadUserData(clsUser& user)
    {
        clsScreen::Print("Please enter the following user data:\n");
        clsScreen::Print("");  user.FirstName = MyInputLibrary::ReadLine("First Name: ");
        clsScreen::Print("");  user.LastName = MyInputLibrary::ReadLine("Last Name: ");
        clsScreen::Print("");  user.Email = MyInputLibrary::ReadLine("Email: ");
        clsScreen::Print("");  user.Phone = MyInputLibrary::ReadLine("Phone: ");
        clsScreen::Print("");  user.Password = MyInputLibrary::ReadLine("Password: ");
        _ReadUserPermissions(user);
    }
    static void _PrintOldVsNewUserData(const clsUser& OldUser, const clsUser& NewUser)
    {
        short labelWidth = 12;         // Align the colons :
        short firstCardWidth = 40;     // Space between the start of card 1 and card 2

        std::cout << clsScreen::spaces << "\n";
        std::cout << clsScreen::spaces << setw(firstCardWidth) << left << "      Old User Data" << "      New User Data" << endl;
        std::cout << clsScreen::spaces << setw(firstCardWidth) << left << "==============================" << "==============================" << endl;

        // Helper Lambda function to print a row
        auto printRow = [&](string label, string val1, string val2) {

            std::cout << clsScreen::spaces;
            string firstCardPart = "";

            std::cout << left << setw(labelWidth) << label << ": " << setw(firstCardWidth - labelWidth - 2) << val1;
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
        clsScreen::Print("");
        string username = MyInputLibrary::ReadLine("Enter Username to update: ");
        clsUser user = clsUser::FindUser(username);

        while (user.IsEmpty()) {
            clsScreen::Print("The Username: " + username + " not found.\n");
            clsScreen::Print("");
            username = MyInputLibrary::ReadLine("Enter Username to Update: ");
            user = clsUser::FindUser(username);
        }
        clsScreen::Print("\nCurrent User Data:\n");

        _Print(user);
        clsUser newUserData = user; // to hold old data before updating
        clsScreen::Print("Please enter new data for the user:\n");
        _ReadUserData(newUserData);

        _PrintOldVsNewUserData(user, newUserData);

        std::cout << "\t";     clsScreen::Print(""); // just to allign the msg of the next line
        if (!MyInputLibrary::ReadYesNo("Do you want to update this user? (Y/N): "))
        {
            std::cout << "\n";
            clsScreen::Print("Update cancelled by user.\n");
            return;
        }

        clsUser::enSaveResults saveResult = newUserData.Save();
        if (saveResult == clsUser::svSucceeded)
        {
            clsScreen::Print("\n");
            clsScreen::Print("Client data updated successfully.\n");
        }
        else
        {
            clsScreen::Print("\n");
            clsScreen::Print("Failed to update client data.\n");
        }
    
    }
};

