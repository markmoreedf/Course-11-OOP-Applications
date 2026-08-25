#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "clsUtility.h"

namespace MyInputLibrary
{
    using namespace std;

    // ===================================
    // 1. Core Generic Template Functions
    // ===================================

    template <typename T>
    static T ReadNumber(const string& msg = "Please Enter a number: ")
    {
        T number;
        bool IsValid = false;
        do {
            cout << msg;
            cin >> number;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Number, Enter Again !\n";
            }
            else
                IsValid = true;

        } while (!IsValid);

        // ignore the rest of the line after the number. "300 abc" --> ignore "abc"
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        return number;
    }

    template <typename T>
    static T ReadPositiveNumber(const string& msg = "Please Enter a Positive Number: ")
    {
        T n;
        do {
            n = MyInputLibrary::ReadNumber<T>(msg);
            if (n <= 0)
                cout << "Please enter a <<<Positive>>> Number Only.\n";
        } while (n <= 0);

        return n;
    }

    template <typename T>
    static T ReadNegativeNumber(const string& msg = "Please Enter a Negative Number: ")
    {
        T n;
        do {
            n = MyInputLibrary::ReadNumber<T>(msg);
            if (n >= 0)
                cout << "Please enter a <<<Negative>>> Number Only.\n";
        } while (n >= 0);

        return n;
    }

    template <typename T>
    static T ReadNumberBetween(const T& from, const T& to, const string& msg = "")
    {
        T number;
        bool IsValid = false;
        do {
            number = MyInputLibrary::ReadNumber<T>(msg.empty() ? ("Enter a number between " + to_string(from) + " and " + to_string(to) + " : ") : msg);

            if (!clsUtility::IsNumberBetween(number, from, to))
                cout << "Invalid input. Please enter a number between " << from << " and " << to << "." << endl;
            else
                IsValid = true;

        } while (!IsValid);

        return number;
    }


    // ==============================================
    // 2. Legacy Wrappers for Backward Compatibility
    // ==============================================

    // Basic Number Readers
    static int ReadInt(const string& msg = "Please Enter an integer number: ")
    {
        return ReadNumber<int>(msg);
    }

    static float ReadFloat(const string& msg = "Please Enter an float number: ")
    {
        return ReadNumber<float>(msg);
    }

    static double ReadDouble(const string& msg = "Please Enter an double number: ")
    {
        return ReadNumber<double>(msg);
    }

    // Positive Readers
    static int ReadPositiveInt(const string& msg = "Please Enter a Positive Integer: ")
    {
        return ReadPositiveNumber<int>(msg);
    }

    static float ReadPositiveFloat(const string& msg = "Please Enter a Positive Float: ")
    {
        return ReadPositiveNumber<float>(msg);
    }

    static double ReadPositiveDouble(const string& msg = "Please Enter a Positive Double: ")
    {
        return ReadPositiveNumber<double>(msg);
    }

    // Negative Readers
    static int ReadNegativeInt(const string& msg = "Please Enter a Negative Integer: ")
    {
        return ReadNegativeNumber<int>(msg);
    }

    static float ReadNegativeFloat(const string& msg = "Please Enter a Negative Float: ")
    {
        return ReadNegativeNumber<float>(msg);
    }

    static double ReadNegativeDouble(const string& msg = "Please Enter a Negative Double: ")
    {
        return ReadNegativeNumber<double>(msg);
    }


    // ==============================
    // 3. String & Utility Functions
    // ==============================

    static char ReadChar(const string& msg = "Enter a character: ")
    {
        char c;
        bool validInput = false;

        do {
            cout << msg;
            cin >> c;

            if (cin.fail()) {
                cin.clear(); // Clear the fail state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input. Please enter a single character." << endl;
            }
            else {
                validInput = true; // Valid input received
            }
        } while (!validInput);

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return c;
    }

    static bool ReadYesNo(const string& msg = "Enter Y/N")
    {
        char yesOrNo;
        // check if the input character is not Y or N
        bool check = false;
        do {
            yesOrNo = toupper(MyInputLibrary::ReadChar(msg));
            // updateing check value
            check = (yesOrNo != 'Y' && yesOrNo != 'N');

            if (check)
                cout << "Please enter Y or N only\n";

        } while (check);

        // return true if Y , false if N
        return yesOrNo == 'Y';
    }

    static string ReadWord(const string& msg = "Enter a word [No spaces] : ")
    {
        string word = "";
        do {
            cout << msg;
            cin >> word;

            if (word.find(' ') != string::npos) {
                cout << "Invalid input. Please enter a single word without spaces." << endl;
                word = ""; // Reset word to prompt again
            }
        } while (word.empty());
        return word;
    }

    static string ReadLine(const string& msg = "Enter a line of string : ")
    {
        string line = "";
        cout << msg;
        getline(cin >> ws, line);
        return line;
    }

};