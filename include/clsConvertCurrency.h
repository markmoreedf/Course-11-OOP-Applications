#pragma once
#include "clsScreen.h"

class clsConvertCurrency : protected clsScreen
{
private:
    static void _PrintCurrencyCard(clsCurrency currency)
    {
        _Print("\n");
        _Print("===================================");
        _Print("Country Name  : " + currency.countryName);
        _Print("Currency Code : " + currency.crCode);
        _Print("Currency Name : " + currency.crName);
        _Print("Rate (1$)     : " + to_string(currency.rate));
        _Print("===================================");
    }

    static void _PerformeConvertCurrencyScreen()
    {
        _Print("\n");
        _Print("Enter Currency Code To Convert From: ");
        clsCurrency fromCurrency = clsCurrency::FindCurrencyByCode(MyInputLibrary::ReadWord(""));
        while(fromCurrency.IsEmpty())
        {
            _Print("\n");
            _Print("No currency found with this code\n");
            _Print("Enter Currency Code To Convert From: ");
            fromCurrency = clsCurrency::FindCurrencyByCode(MyInputLibrary::ReadWord(""));
        }

        _Print("\n");
        _Print("Amount: ");
        double amount = MyInputLibrary::ReadPositiveDouble("");
        _Print("\n");

        _Print("Enter Currency Code To Convert To: ");
        clsCurrency toCurrency = clsCurrency::FindCurrencyByCode(MyInputLibrary::ReadWord(""));
        while(toCurrency.IsEmpty())
        {
            _Print("\n");
            _Print("No currency found with this code\n");
            _Print("Enter Currency Code To Convert To: ");
            toCurrency = clsCurrency::FindCurrencyByCode(MyInputLibrary::ReadWord(""));
        }

        _Print("\n");
        _Print(to_string(amount) + " " + fromCurrency.crCode + " = " + to_string(amount * toCurrency.rate / fromCurrency.rate) + " " + toCurrency.crCode);
    }

public:
    static void ShowConvertCurrencyScreen()
    {
        do 
        {
            system("cls");
            _PrintHeader("Convert Currency Screen");
            _PerformeConvertCurrencyScreen();
            _Print("\n\n");
            _Print("");
        }
        while (MyInputLibrary::ReadYesNo("Do you want to convert another currency? [y/n]: "));
    }
};

