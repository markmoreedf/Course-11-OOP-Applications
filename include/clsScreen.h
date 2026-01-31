#pragma once
#include <iostream>
class clsScreen
{
protected:
    inline static const std::string spaces = "                                ";

    static void Print(const string & message)
    {
        std::cout << spaces << message;
    }
    static void _PrintHeader(const std::string & title)
    {
        std::cout << "\n\n";
        std::cout << spaces;    clsUtility::PrintDeviderLine(title.length() + 12);
        std::cout << spaces     << "| === " + title + " === |\n";
        std::cout << spaces;    clsUtility::PrintDeviderLine(title.length() + 12);
        std::cout << "\n\n";


    }
    static void _PauseScreen()
    {
        std::cout << "\n" << spaces << "Press Enter to continue...";
        std::cin.ignore();
    }
};