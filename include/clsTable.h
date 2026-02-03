#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

class clsTable
{
public:
    struct Colors
    {
        inline static constexpr const char* Red = "\033[31m";
        inline static constexpr const char* Green = "\033[32m";
        inline static constexpr const char* Yellow = "\033[33m";
        inline static constexpr const char* Blue = "\033[34m";
        inline static constexpr const char* Magenta = "\033[35m";
        inline static constexpr const char* BoldRed = "\033[1;31m";
        inline static constexpr const char* BoldGreen = "\033[1;32m";
        inline static constexpr const char* BoldYellow = "\033[1;33m";
        inline static constexpr const char* BoldBlue = "\033[1;34m";
        inline static constexpr const char* BoldMagenta = "\033[1;35m";
        inline static constexpr const char* Reset = "\033[0m";
    };

private:
    static void _PrintMargin(int margin)
    {
        std::cout << std::setw(margin) << std::left << "";
    }

    // Print a single table cell: prints left border (colored), cell content (centered, truncated if needed)
    static void _PrintTableCell(const std::string& word, int width, const char* borderColor = Colors::Reset)
    {
        if (width < 0) width = 0;
        std::cout << borderColor << "|" << Colors::Reset;

        std::string display = word;
        if (static_cast<int>(display.length()) > width)
            display = display.substr(0, width);

        int padLeft = (width - static_cast<int>(display.length())) / 2;
        if (padLeft < 0) padLeft = 0;
        int padRight = width - static_cast<int>(display.length()) - padLeft;
        if (padRight < 0) padRight = 0;

        std::cout << std::setw(padLeft) << "" << display << std::setw(padRight) << "";
    }

public:
    // Print a row. `margin` is how many spaces to shift right.
    static void PrintTableRow(const std::vector<std::string>& rowData, const std::vector<int>& widths, int margin, const char* borderColor = Colors::Reset)
    {
        _PrintMargin(margin);

        std::size_t cols = rowData.size();
        for (std::size_t i = 0; i < cols; ++i)
        {
            int w = 10; // fallback width
            if (i < widths.size()) w = widths[i];
            _PrintTableCell(rowData[i], w, borderColor);
        }

        // final right border (colored) then reset
        std::cout << borderColor << "|" << Colors::Reset << "\n";
    }

    static void PrintDividerLine(int tableWidth, int shiftRight, char dividerChar = '-', const char* borderColor = Colors::Reset)
    {
        if (tableWidth < 0) tableWidth = 0;
        _PrintMargin(shiftRight);
        std::cout << borderColor;
        for (int i = 0; i < tableWidth; ++i)
            std::cout << dividerChar;
        std::cout << Colors::Reset << "\n";
    }

    static void PrintTableFooter(const std::vector<std::string>& footerData,
        const std::vector<int>& widths,
        int tableWidth,
        int shiftRight = 0,
        char dividerSymbol = '-',
        const char* borderColor = Colors::Yellow)
    {
        clsTable::PrintTableRow(footerData, widths, shiftRight, borderColor);
        clsTable::PrintDividerLine(tableWidth, shiftRight, dividerSymbol, borderColor);
    }

    // columnsNames: header labels
    // widths: per-column widths (same order as columnsNames)
    // data: rows
    // emptyMessage: printed centered across data area if data is empty
    static void PrintTable(const std::vector<std::string>& columnsNames,
        const std::vector<int>& widths,
        const std::vector<std::vector<std::string>>& data,
        const std::string& emptyMessage,
        int shiftRight = 0,
        const char* borderColor = Colors::Reset)
    {
        // validate inputs
        std::size_t cols = widths.size();
        if (cols == 0) return;

        // calculate table width = sum(widths) + (cols + 1) for borders
        int tableWidth = 1;
        for (int w : widths) tableWidth += w + 1;

        // header
        PrintDividerLine(tableWidth, shiftRight, '-', borderColor);
        PrintTableRow(columnsNames, widths, shiftRight, borderColor);
        PrintDividerLine(tableWidth, shiftRight, '-', borderColor);

        if (data.empty())
        {
            _PrintMargin(shiftRight);
            // print one colored left border
            std::cout << borderColor << "|" << Colors::Reset;
            int totalDataWidth = tableWidth - 2; // exclude the two side borders
            std::string display = emptyMessage;
            if (static_cast<int>(display.length()) > totalDataWidth)
                display = display.substr(0, totalDataWidth);

            int padLeft = (totalDataWidth - static_cast<int>(display.length())) / 2;
            if (padLeft < 0) padLeft = 0;
            int padRight = totalDataWidth - static_cast<int>(display.length()) - padLeft;
            if (padRight < 0) padRight = 0;

            std::cout << std::setw(padLeft) << "" << display << std::setw(padRight) << "";

            // final border + reset
            std::cout << borderColor << "|" << Colors::Reset << "\n";
        }
        else
        {
            for (const auto& row : data)
            {
                PrintTableRow(row, widths, shiftRight, borderColor);
            }
        }

        // footer divider
        PrintDividerLine(tableWidth, shiftRight, '-', borderColor);
    }
};