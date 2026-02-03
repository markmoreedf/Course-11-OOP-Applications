#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class clsTable
{
    //public so we can access it like clsTable::Colors::Red in the private methods
public:
    const struct Colors
    {
        inline static const std::string Red = "\033[31m";
        inline static const std::string Green = "\033[32m";
        inline static const std::string Yellow = "\033[33m";
        inline static const std::string Blue = "\033[34m";
        inline static const std::string Magenta = "\033[35m";
        inline static const std::string BoldRed = "\033[1;31m";
        inline static const std::string BoldGreen = "\033[1;32m";
        inline static const std::string BoldYellow = "\033[1;33m";
        inline static const std::string BoldBlue = "\033[1;34m";
        inline static const std::string BoldMagenta = "\033[1;35m";
        inline static const std::string Reset = "\033[0m";

    };

private:

    static void _PrintMargin(short margin)
    {
        cout << setw(margin) << left << "";
    }
    static void _PrintTableCell(const string& word, const short& width, const string& borderColor = clsTable::Colors::Reset)
    {
        // print left border with requested color
        cout << borderColor << "|";
        // reset color for cell content
        short padLeft = (width - word.length()) / 2;
        short padRight = width - word.length() - padLeft;
        cout << Colors::Reset << setw(padLeft) << "" << word << setw(padRight) << "";
    }

public:
    static void PrintTableRow(const vector<string>& rowData, const vector<short>& widths, short margin, const string & borderColor = Colors::Reset)
    {
        _PrintMargin(margin);
        for (short i = 0; i < rowData.size(); i++)
        {
            _PrintTableCell(rowData[i], widths[i], borderColor);
        }
        cout << borderColor << "|\n";
        
    }
    static void PrintDividerLine(const short& tableWidth, short shiftRight, char dividerChar = '-', const string & borderColor = Colors::Reset)
    {
        _PrintMargin(shiftRight);
        for (short i = 0; i < tableWidth; i++)
            cout << borderColor << dividerChar;
        cout << Colors::Reset << "\n";
    }
    static void PrintTableFooter(const vector<string>& footerData,
        const vector<short>& widths,
        const short& tableWidth,
        short shiftRight = 0,
        char dividerSymbol = '-',
        const string& borderColor = Colors::Yellow)
    {
        clsTable::PrintTableRow(footerData, widths, shiftRight, borderColor);
        clsTable::PrintDividerLine(tableWidth, shiftRight, dividerSymbol, borderColor);

    }

    static void PrintTable(const vector<string>& coloumsNames,
        const vector<short>& widths,
        const vector<vector<string>>& data,
        const string& emptyMessage,
        short shiftRight = 0,
        const string& borderColor = Colors::Reset)
    {
        // calculate table width
        short tableWidth = 1; 
        for (const short& w : widths)
            tableWidth += w + 1; 

        // print header
        PrintDividerLine(tableWidth, shiftRight, '-', borderColor);
        PrintTableRow(coloumsNames, widths, shiftRight, borderColor);
        PrintDividerLine(tableWidth, shiftRight, '-', borderColor);

        // print data rows or empty message
        if (data.size() == 0)
        {
            _PrintMargin(shiftRight);
            cout << borderColor << "|" << Colors::Reset;
            short totalDataWidth = tableWidth - 2; // -2 for the borders
            short padLeft = (totalDataWidth - emptyMessage.length()) / 2;
            short padRight = totalDataWidth - emptyMessage.length() - padLeft;
            cout << setw(padLeft) << "" << emptyMessage << setw(padRight) << "";
            cout << borderColor << "|\n" << Colors::Reset;
        }
        else
        {
            for (const vector<string>& row : data)
            {
                PrintTableRow(row, widths, shiftRight, borderColor);
            }
        }
        // print footer line
        PrintDividerLine(tableWidth, shiftRight, '-', borderColor);
    }
};