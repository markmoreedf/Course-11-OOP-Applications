#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtility.h"
class clsClientListScreen :
    protected clsScreen
{
    public:
        static void ShowClientsListScreen()
        {
            vector <clsBankClient> clients = clsBankClient::GetClientsList();
            vector<vector<string>> data;
            clsScreen::_PrintHeader("Clients List. ["+ to_string(clients.size()) + "] found", 15);

            vector<string> coloumsNames = { "Account No.", "Full Name", "Phone Number", "E-mail", "Pin Code", "Balance" };
            const vector<short> widths = { 20, 30, 18, 30, 15, 25 };

            for (clsBankClient& cl : clients) {
                data.push_back({ cl.AccountNumber, cl.FullName(),  cl.Phone, cl.Email, cl.Pincode, to_string(cl.Balance) });
            }

            clsUtility::PrintTable(coloumsNames, widths, data, "\n\n\t\t\t\tNo Clients Available In the System!\n\n",5);
        }

};

