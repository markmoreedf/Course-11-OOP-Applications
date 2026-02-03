#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtility.h"

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
        const vector<short> widths = { 20, 30, 25 };

        for (clsBankClient& cl : clients) {
            data.push_back({ cl.AccountNumber, cl.FullName(), to_string(cl.Balance) });
        }

        clsTable::PrintTable(coloumsNames, widths, data, "\n\n\t\t\t\tNo Clients Available In the System!\n\n", 18, clsTable::Colors::Yellow);
        // hard coded for simplicity.. 
        clsTable::PrintTableFooter({ { "Total Balances" }, {  }, {  to_string(totalBalances)} }, widths, 79, 18);

    }

};

