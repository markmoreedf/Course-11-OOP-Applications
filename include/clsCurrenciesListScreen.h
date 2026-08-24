#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"

class clsCurrenciesListScreen : protected clsScreen
{
public:

    static void ShowCurrenciesListScreen()
    {
        vector <clsCurrency> currencies = clsCurrency::GetCurrenciesList();
        vector<vector<string>> data;

        _PrintHeader("Currencies List. [" + to_string(currencies.size()) + "] found", 10);


        vector<string> coloumsNames = { "Country", "Currency Code", "Currency Name", "Rate (1 " + clsTable::Colors::Green + "$" + clsTable::Colors::Reset + ")" };
        const vector<int> widths = { 30, 15, 42, 20 };


        for (clsCurrency& c : currencies) {

            // 1. Format the number to a plain string first "1250.00"
            std::stringstream numStream;
            numStream << fixed << setprecision(5) << c.rate;
            string formattedNum = numStream.str();

            // 2. Add leading spaces to the number so they all have the same length
            // For example, if your biggest balance is 7 digits, pad to 10 characters
            while (formattedNum.length() < 10) {
                formattedNum = " " + formattedNum;
                }

                string finalDisplay =  formattedNum + clsTable::Colors::Green + " $";


            data.push_back({ c.countryName, c.crCode, c.crName, finalDisplay });
        }

        clsTable::PrintTable(coloumsNames, widths, data, "\t\t\t\tNo Currencies Available In the System!", 5, clsTable::Colors::BrightCyan);

    }

};

