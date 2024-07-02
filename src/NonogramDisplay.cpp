#include "NonogramDisplay.h"
#include <iostream>
#include <iomanip>
#include <vector>

void NonogramDisplay::displayField(const std::vector<std::vector<char>> &field, const std::vector<std::vector<int>> &rowHints, const std::vector<std::vector<int>> &colHints)
{
    int size = field.size();

    // Calculate the maximum width needed for the row hints
    int maxRowHintWidth = 0;
    for (const auto &rowHint : rowHints)
    {
        int rowHintWidth = 0;
        for (int hint : rowHint)
        {
            rowHintWidth += (hint >= 10 ? 3 : 2); // 2 spaces for single digit, 3 for double digit (hint + space)
        }
        if (rowHintWidth > maxRowHintWidth)
        {
            maxRowHintWidth = rowHintWidth;
        }
    }

    // Calculate the maximum height needed for the column hints
    int maxColHintHeight = 0;
    for (const auto &colHint : colHints)
    {
        if (colHint.size() > maxColHintHeight)
        {
            maxColHintHeight = colHint.size();
        }
    }

    // Display the column hints
    for (int hintRow = 0; hintRow < maxColHintHeight; ++hintRow)
    {
        std::cout << std::setw(maxRowHintWidth + 1) << " "; // Adjust column hints alignment
        for (int col = 0; col < size; ++col)
        {
            if (hintRow < colHints[col].size())
            {
                std::cout << colHints[col][hintRow] << " ";
            }
            else
            {
                std::cout << "  "; // Space for alignment
            }

            // Print vertical line between columns
            if (col < size - 1)
            {
                std::cout << "| ";
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::setw(maxRowHintWidth + 1) << " ";
    for (int i = 0; i < size - 1; ++i)
    {
        std::cout << "----";
    }
    std::cout << "--" << std::endl;

    // Display the grid with row hints and horizontal/vertical lines
    for (int i = 0; i < size; ++i)
    {
        for (int hint : rowHints[i])
        {
            std::cout << hint << " ";
        }
        std::cout << std::setw(maxRowHintWidth - (rowHints[i].size() * 2) + 1) << " "; // Adjust row hints alignment
        for (int j = 0; j < size; ++j)
        {
            std::cout << field[i][j] << " ";

            // Print vertical line between columns
            if (j < size - 1)
            {
                std::cout << "| ";
            }
        }
        std::cout << std::endl;

        // Print horizontal line between rows
        if (i < size - 1)
        {
            std::cout << std::setw(maxRowHintWidth + 1) << " "; // Align horizontal line with the grid

            for (int j = 0; j < size; ++j)
            {
                std::cout << "--";
                if (j < size - 1)
                {
                    std::cout << "+-";
                }
            }
            std::cout << std::endl;
        }
    }
}
