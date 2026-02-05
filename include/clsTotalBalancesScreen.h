#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtility.h"
#include <sstream>

class clsTotalBalancesScreen :
    protected clsScreen
{
public:
    static void ShowTotalBalancesScreen()
    {
        float totalBalances = clsBankClient::GetTotalBalances();
        vector <clsBankClient> clients = clsBankClient::GetClientsList();
        vector<vector<string>> data;
        clsScreen::_PrintHeader("Total Balances Screen. [" + to_string(clients.size()) + "] clients found");

        vector<string> coloumsNames = { "Account No.", "Full Name", "Balance" };
        const vector<int>widths = { 20, 30, 25 };

        for (clsBankClient& cl : clients) {
            std::stringstream sstream;
            sstream << fixed << setprecision(2) << cl.Balance;
            
            data.push_back({ cl.AccountNumber, cl.FullName(),  clsTable::Colors::Green + "$ " + clsTable::Colors::Reset + sstream.str() });
        }

        clsTable::PrintTable(coloumsNames,
            widths,
            data,
            "\n\n\t\t\t\tNo Clients Available In the System!\n\n",
            18, clsTable::Colors::BrightCyan);

        std::stringstream ssTotal;
        ssTotal << fixed << setprecision(2) << totalBalances;


        // hard coded for simplicity.. 
        clsTable::PrintTableFooter({
            { "Total Balances" },
            { },
            { clsTable::Colors::Green + "$ " + clsTable::Colors::Reset + ssTotal.str() } 
            }, widths, 79, 18, '-',clsTable::Colors::BrightCyan);

    }

};

