#pragma once
#include "clsScreen.h"
#include "clsUser.h"

class clsUserListScreen :   protected clsScreen
{
public:
    static void ShowUsersListScreen()
    {
        vector <clsUser> users = clsUser::GetUsersList();
        vector<vector<string>> data;
        clsScreen::_PrintHeader("Users List. [" + to_string(users.size()) + "] found", 15);

        vector<string> coloumsNames = { "UserName", "Password", "Full Name", "E-mail", "Phone No", "Permissions" };
        const vector<int> widths = { 20, 15, 25, 25, 15, 15 };


        for (clsUser& user : users) {

            string displayPassword = (user.Username == "admin") ? clsTable::Colors::Red + "********" + clsTable::Colors::Reset : user.Password;
            string displayPermissions = (user.Permissions == 127) ? clsTable::Colors::Green + "Full Access" + clsTable::Colors::Reset : to_string(user.Permissions);
           
            data.push_back({ user.Username, displayPassword, user.FullName(), user.Email, user.Phone, displayPermissions});
        }

        clsTable::PrintTable(coloumsNames, widths, data, "\n\n\t\t\t\tNo Users Available In the System!\n\n", 5, clsTable::Colors::BrightCyan);
    }
};

