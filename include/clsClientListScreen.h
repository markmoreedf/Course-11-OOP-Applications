#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtility.h"
#include <sstream>

class clsClientListScreen : protected clsScreen
{
public:
        static void ShowClientsListScreen()
        {
            vector <clsBankClient> clients = clsBankClient::GetClientsList();
            vector<vector<string>> data;
            clsScreen::_PrintHeader("Clients List. ["+ to_string(clients.size()) + "] found", 15);

            vector<string> coloumsNames = { "Account No.", "Full Name", "Phone Number", "E-mail", "Pin Code", "Balance" };
            const vector<int> widths = { 20, 30, 18, 30, 15, 25 };


            for (clsBankClient& cl : clients) {
                // 1. Format the number to a plain string first "1250.00"
                std::stringstream numStream;
                numStream << fixed << setprecision(2) << cl.Balance;
                string formattedNum = numStream.str();

                // 2. Add leading spaces to the number so they all have the same length
                // For example, if your biggest balance is 7 digits, pad to 10 characters
                while (formattedNum.length() < 10) {
                    formattedNum = " " + formattedNum;
                }

                string finalDisplay = clsTable::Colors::Green + "$ " + clsTable::Colors::Reset + formattedNum;

                data.push_back({ cl.AccountNumber, cl.FullName(), cl.Phone, cl.Email, cl.Pincode, finalDisplay });
            }

            clsTable::PrintTable(coloumsNames, widths, data, "\n\n\t\t\t\tNo Clients Available In the System!\n\n",5, clsTable::Colors::BrightCyan);
        }

};
