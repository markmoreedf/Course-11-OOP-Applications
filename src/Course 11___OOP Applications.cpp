#include <iostream>
#include "clsUtility.h"
#include "clsBankClient.h"
#include "MyInputLibrary.h"
#include "clsMainScreen.h"
#include "clsLoginScreen.h"
using namespace std;



int main()
{
    while (true)
    {
        clsLoginScreen::ShowLoginScreen();
        clsMainScreen::ShowMainMenue();
    }
    return 0;
}