#pragma once
#include <iostream>
#include "clsTable.h"

class clsScreen
{
protected:
    inline static const std::string spaces = "                                ";

    static void Print(const string & message)
    {
        std::cout << spaces << message;
    }
    static void _PrintHeader(const std::string & title, const short & shiftRight = 0)
    {
        std::cout << "\n\n";
        std::cout << spaces;    clsTable::PrintDividerLine(title.length() + 12, shiftRight);
        for (short i = 0; i < shiftRight; i++)
        {
            std::cout << " ";
        }
        std::cout << spaces     << "| === " + title + " === |\n";
        std::cout << spaces;    clsTable::PrintDividerLine(title.length() + 12, shiftRight);
        std::cout << "\n\n";


    }
    static void _PauseScreen()
    {
        std::cout << "\n" << spaces << "Press Enter to continue...";
        std::cin.ignore();
    }
};