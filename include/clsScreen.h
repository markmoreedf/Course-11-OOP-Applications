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
    static void _PrintHeader(const std::string& title)
    {
        std::cout << spaces << "=====================================\n";
        std::cout << spaces << "\t" << title << "\n";
        std::cout << spaces << "=====================================\n\n";
    }
    static void _PauseScreen()
    {
        std::cout << "\n" << spaces << "Press Enter to continue...";
        std::cin.ignore();
    }
};