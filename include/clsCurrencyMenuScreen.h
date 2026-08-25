#pragma once
#include "clsScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrenyScreen.h"
#include "clsConvertCurrency.h"
#include "clsUpdateRateScreen.h"

class clsCurrencyMenuScreen : protected clsScreen
{

private:
    enum enCurrencyMenueOption
    {
        eShowAllCurrencyRates = 1,
        eFindCurrency = 2,
        eUpdateRate = 3,
        eConvertCurrency = 4,
        eMainMenue = 5
    };

    static void _PerformCurrencyMenueOption(enCurrencyMenueOption choice)
    {
        switch (choice) {
            case eShowAllCurrencyRates:
                clsCurrenciesListScreen::ShowCurrenciesListScreen();
                break;
            case eFindCurrency:
                clsFindCurrenyScreen::ShowFindCurrencyScreen();
                break;
            case eUpdateRate:
                clsUpdateRateScreen::ShowUpdateRateScreen();
                break;
            case eConvertCurrency:
                clsConvertCurrency::ShowConvertCurrencyScreen();
                break;
            case eMainMenue:
                return;
            default:
                _Print("Invalid choice. Please try again.\n");
                break;
        }
        _Print("\n\n");
        _PauseScreen("Press any key to return to the Currency Menu...");
    }

public:
        static void ShowCurrencyMenue()
        {
            enCurrencyMenueOption choice = enCurrencyMenueOption::eShowAllCurrencyRates; // Initialize with a default value to enter the loop
            while (choice != enCurrencyMenueOption::eMainMenue)
            {
                system("cls");
                _PrintHeader("Currency Screen");
                _Print("=================================\n");
                _Print(" [1] Show All Currency Rates\n");
                _Print(" [2] Search Currency\n");
                _Print(" [3] Update Rate\n");
                _Print(" [4] Convert Currency\n");
                _Print(" [5] Back to Main Menu\n");
                _Print("=================================\n\n");
                _Print("\n");  _Print("");
                choice = static_cast<enCurrencyMenueOption>(MyInputLibrary::ReadNumberBetween(1, 5, "Choose what do you want to do? [1-5]: "));
                _PerformCurrencyMenueOption(choice);

            }

        }

};