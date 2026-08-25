#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "MyInputLibrary.h"
class clsFindCurrenyScreen : protected clsScreen
{
protected:

    static void _PrintCurrencyRecord(clsCurrency currency)
    {
        _Print("\n");
        _Print("===================================\n");
        _Print("Country Name  : " + currency.countryName + "\n");
        _Print("Currency Code : " + currency.crCode + "\n");
        _Print("Currency Name : " + currency.crName + "\n");
        _Print("Rate (1$)     : " + to_string(currency.rate) + "\n");
        _Print("===================================\n");
    }

    static clsCurrency _PerformFindCurrency(string choice)
    {
        clsCurrency currency = clsCurrency::FindCurrencyByCountry(choice);
        if (!currency.IsEmpty())
        { return currency; }

        currency = clsCurrency::FindCurrencyByName(choice);
        if (!currency.IsEmpty())
        { return currency; }

        currency = clsCurrency::FindByCode(choice);

        return currency; 
        
    }

public:

    static void ShowFindCurrencyScreen()
    {
        while(true)
        {
            system("cls");
            _PrintHeader("Find Currency Screen");
            _Print("___________________________________\n\n");

            _Print("Search By Country Name, Currency Name or Currency Code\t[Enter 0 to go Back]\n");
            _Print("-->  ");
            string choice = MyInputLibrary::ReadLine("");
            _Print("___________________________________\n\n");

            if(choice == "0")
                return;
            
            if(!_PerformFindCurrency(choice).IsEmpty())
            {
                _PrintCurrencyRecord(_PerformFindCurrency(choice));
            }
            else
            {
                _Print("No currency found with the given input: " + choice + "\n");
            }

            _PauseScreen();
        }       

    }


};

