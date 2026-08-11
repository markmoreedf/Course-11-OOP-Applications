#pragma once
#include "clsScreen.h"
#include "clsTable.h"
#include "clsUser.h"
class clsLoginRegisterScreen :
    protected clsScreen
{

public:
    static void ShowLoginRegisterScreen()
    {
        _PrintHeader("Login/Register Screen");
        vector <vector<string>> loginRegistery = clsUser::GetLoginRegistery();
        vector<vector<string>> data;
        _PrintHeader("Login Registery List. [" + to_string(loginRegistery.size()) + "] found", 15);

        vector<string> coloumsNames = { "Login Time",  "UserName", "Password", "Permissions" };
        const vector<int> widths = { 25,25, 25, 25 };


        for (vector<string>& record : loginRegistery) {

            string displayPassword = (record[1] == "admin") ? clsTable::Colors::Red + "********" + clsTable::Colors::Reset : record[2];
            string displayPermissions = ((stoi(record[3])) == clsUser::enUserPermissions::fullAccess) ? clsTable::Colors::Green + "Full Access" + clsTable::Colors::Reset : record[3];

            data.push_back({ record[0], record[1], displayPassword, displayPermissions });
        }

        clsTable::PrintTable(coloumsNames, widths, data, "\n\n\t\t\t\tNo Users Available In the System!", 5, clsTable::Colors::BrightCyan);



    }
};
