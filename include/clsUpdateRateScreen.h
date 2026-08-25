#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "MyInputLibrary.h"
#include "clsFindCurrenyScreen.h"

class clsUpdateRateScreen :
    protected clsScreen, private clsFindCurrenyScreen
{
private:

    static bool _PerformUpdateRate()
    {
        _Print("Enter the currency you wish to update: [code, name or country]\n");
        _Print("-->  ");
        clsCurrency currency = _PerformFindCurrency(MyInputLibrary::ReadLine(""));

        if(!currency.IsEmpty())
        {
            _Print("\n");
            _Print("Old rate for " + currency.crName + " : " + to_string(currency.rate) + "\n");
            _Print("New rate for " + currency.crName + " : ");
            double newRate = MyInputLibrary::ReadPositiveDouble("");
            _Print("\n");
            
            if(currency.SetRate(newRate))
            {
                _Print("The rate has been updated successfully.\n");
                return true;
            }
            else
            {
                _Print("Failed to update the rate.\n");
                _PauseScreen("[Press any key to try again.]\n");
                
            }
        }
        else
        {
            _Print("No currency found with the given input.\n");
            _PauseScreen("[Press any key to try again.]\n");         
        }
        return false;

    }

public:
    static void ShowUpdateRateScreen()
    {
        while (true)
        {
            system("cls");
            _PrintHeader("Update Rate Screen");
            if (_PerformUpdateRate())
                break;
            
        }

    }

};

