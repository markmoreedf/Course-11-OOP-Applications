#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class clsTable
{
private:
    static void _PrintMargin(short margin)
    {
        cout << setw(margin) << left << "";
    }
    static void _PrintTableCell(const string& word, const short& width)
    {
        cout << "|";
        short padLeft = (width - word.length()) / 2;
        short padRight = width - word.length() - padLeft;
        cout << setw(padLeft) << "" << word << setw(padRight) << "";
    }

public:

    static void PrintTableRow(const vector<string>& rowData, const vector<short>& widths, short margin)
    {
        _PrintMargin(margin);
        for (short i = 0; i < rowData.size(); i++)
        {
            _PrintTableCell(rowData[i], widths[i]);
        }
        cout << "|\n";
    }
    static void PrintDividerLine(const short& tableWidth, short shiftRight, char dividerChar = '-')
    {
        _PrintMargin(shiftRight);
        for (short i = 0; i < tableWidth; i++)
            cout << dividerChar;
        cout << "\n";
    }

    static void PrintTable(const vector<string>& coloumsNames,
        const vector<short>& widths,
        const vector<vector<string>>& data,
        short shiftRight = 0,
        char dividerChar = '-',
        const string& emptyDataMsg = "\nNo data Available!\n")
    {
        if (data.empty())
        {
            _PrintMargin(shiftRight);
            cout << emptyDataMsg;
            return;
        }

        short tableWidth = widths.size() + 1;
        for (const short& w : widths)
            tableWidth += w;

        // 1. Header
        PrintDividerLine(tableWidth, shiftRight, dividerChar);
        PrintTableRow(coloumsNames, widths, shiftRight);
        PrintDividerLine(tableWidth, shiftRight, dividerChar);

        // 2. Data Rows
        for (const vector<string>& dataRecord : data)
        {
            PrintTableRow(dataRecord, widths, shiftRight);
        }

        // 3. Footer Line
        PrintDividerLine(tableWidth, shiftRight, dividerChar);
    }
};