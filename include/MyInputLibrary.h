#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "clsUtility.h"

namespace MyInputLibrary
{

    static int ReadInt(const string & msg = "Please Enter an integer number: ")
    {
        int number;
        bool IsValid = false;
        do  {
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

    static float ReadFloat(const string & msg = "Please Enter an float number: ")
    {
        float number;
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

    static double ReadDouble(const string & msg = "Please Enter an double number: ")
    {
        double number;
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

    static int ReadChar(const string& msg = "Enter a character: ")
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

    static bool ReadYesNo(const string & msg = "Enter Y/N")
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

    static string ReadWord(const string & msg = "Enter a word [No spaces] : ")
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

    static string ReadLine(const string & msg = "Enter a line of string : ")
    {
        string line = "";
        cout << msg;
        getline(cin >> ws, line);
        return line;
    }

///////
    static int ReadPositiveInt(const string & msg = "Please Enter a Positive Integer: ")
    {
        int n;
        do {
            n = MyInputLibrary::ReadInt(msg);
            if(n <= 0)
                cout << "Please enter a <<<Positive>>> Integer Only.\n";
        } while (n <= 0);

        return n;
    }
    static int ReadNegativeInt(const string & msg = "Please Enter a Negative Integer: ")
    {
        int n;
        do {
            n = MyInputLibrary::ReadInt(msg);
            if(n >= 0)
                cout << "Please enter a <<<Negative>>> Integer Only.\n";
        } while (n >= 0);

        return n;
    }

    static float ReadPositiveFloat(const string & msg = "Please Enter a Positive Float: ")
    {
        float n;
        do {
            n = MyInputLibrary::ReadFloat(msg);
            if(n <= 0)
                cout << "Please enter a <<<Positive>>> Float Only.\n";
        } while (n <= 0);

        return n;
    }
    static float ReadNegativeFloat(const string & msg = "Please Enter a Negative Float: ")
    {
        float n;
        do {
            n = MyInputLibrary::ReadFloat(msg);
            if(n >= 0)
                cout << "Please enter a <<<Negative>>> Float Only.\n";
        } while (n <= 0);

        return n;
    }

    static double ReadPositiveDouble(const string & msg = "Please Enter a Positive Double: ")
    {
        double n;
        do {
            n = MyInputLibrary::ReadDouble(msg);
            if(n <= 0)
                cout << "Please enter a <<<Positive>>> Double Only.\n";
        } while (n <= 0);

        return n;
    }
    static double ReadNegativeDouble(const string & msg = "Please Enter a Negative Double: ")
    {
        double n;
        do {
            n = MyInputLibrary::ReadDouble(msg);
            if(n >= 0)
                cout << "Please enter a <<<Negative>>> Double Only.\n";
        } while (n >= 0);

        return n;
    }

///////
    static int ReadNumberBetween(const int & from, const int & to, const string & msg = "")
    {
        int number;
        bool IsValid = false;
        do {
            number = MyInputLibrary::ReadInt(msg.empty() ? ("Enter a number between " + to_string(from) + " and " + to_string(to) + " : ") : msg);

            if (!clsUtility::IsNumberBetween(number, from, to))
                cout << "Invalid input. Please enter a number between " << from << " and " << to << "." << endl;
            else
                IsValid = true;

        } while (!IsValid);

        return number;
    }
    static float ReadNumberBetween(const float & from, const float & to, const string & msg = "")
    {
        float number;
        bool IsValid = false;
        do {
            number = MyInputLibrary::ReadFloat(msg.empty() ? ("Enter a number between " + to_string(from) + " and " + to_string(to) + " : ") : msg);

            if (!clsUtility::IsNumberBetween(number, from, to))
                cout << "Invalid input. Please enter a number between " << from << " and " << to << "." << endl;
            else
                IsValid = true;

        } while (!IsValid);

        return number;
    } 
    static double ReadNumberBetween(const double & from, const double & to, const string & msg = "")
    {
        double number;
        bool IsValid = false;
        do {
            number = MyInputLibrary::ReadDouble(
                msg.empty() ? ("Enter a number between " + to_string(from) + " and " + to_string(to) + " : ") : msg);

            if (!clsUtility::IsNumberBetween(number, from, to))
                cout << "Invalid input. Please enter a number between " << from << " and " << to << "." << endl;
            else
                IsValid = true;

        } while (!IsValid);

        return number;
    }

};