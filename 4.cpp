#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <tuple>

#include "FileInput.h"
#include "Util.h"

using std::array;

// Marks a number on all the boards and returns the board that got a complete row or column first and the final number to be marked
std::tuple<int, int> MarkInBoard(const std::vector<array<array<int, 5>, 5>> &inputBoards, int number, std::vector<array<int, 5>> &markedInRows, std::vector<array<int, 5>> &markedInColumns, std::vector<int> &markedSums, std::vector<int> &completedBoards, bool returnFirstCompleteBoard = true)
{
    std::tuple<int, int> returnNumberAndIndex;
    bool found = false;

    for (int i = 0; i < inputBoards.size(); i++)
    {
        if (Util::In(completedBoards, i))
        {
            continue;
        }

        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                if (inputBoards[i][j][k] == number)
                {
                    markedInRows[i][j]++;
                    markedInColumns[i][k]++;
                    markedSums[i] += inputBoards[i][j][k];

                    if ((returnFirstCompleteBoard == false || found == false) && (markedInRows[i][j] == 5 || markedInColumns[i][k] == 5))
                    {
                        found = true;
                        completedBoards.push_back(i);
                        returnNumberAndIndex = std::tuple<int, int>(i, number);
                    }
                }
            }
        }
    }

    if (found)
    {
        return returnNumberAndIndex;
    }
    else
    {
        return std::tuple<int, int>(-1, -1);
    }
}

void part1(std::vector<int> &inputDrawnNumbers,
           std::vector<array<array<int, 5>, 5>> &inputBoards)
{
    std::vector<array<int, 5>> markedInRows(inputBoards.size(), {0}), markedInColumns(inputBoards.size(), {0});
    std::vector<int> markedSums(inputBoards.size(), 0), completedBoards;
    int answer, completingNumber = -1, completedIndex = -1;

    for (int number : inputDrawnNumbers)
    {
        int finalNumber, boardIndex;
        std::tie(boardIndex, finalNumber) = MarkInBoard(inputBoards, number, markedInRows, markedInColumns, markedSums, completedBoards);
        if (finalNumber != -1)
        {
            completingNumber = finalNumber;
            completedIndex = boardIndex;
            break;
        }
    }

    int totalSum = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            totalSum += inputBoards[completedIndex][i][j];
        }
    }
    answer = completingNumber * (totalSum - markedSums[completedIndex]);

    std::cout << "Part 1: "
              << answer << std::endl;
}

void part2(std::vector<int> &inputDrawnNumbers,
           std::vector<array<array<int, 5>, 5>> &inputBoards)
{
    std::vector<array<int, 5>> markedInRows(inputBoards.size(), {0}), markedInColumns(inputBoards.size(), {0});
    std::vector<int> markedSums(inputBoards.size(), 0), completedBoards;
    int answer, lastCompletedIndex = -1, lastCompletingNumber = -1;

    for (int number : inputDrawnNumbers)
    {
        int finalNumber, boardIndex;
        std::tie(boardIndex, finalNumber) = MarkInBoard(inputBoards, number, markedInRows, markedInColumns, markedSums, completedBoards, false);
        if (finalNumber != -1)
        {
            lastCompletedIndex = boardIndex;
            lastCompletingNumber = finalNumber;
        }
    }

    int totalSum = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            totalSum += inputBoards[lastCompletedIndex][i][j];
        }
    }
    answer = lastCompletingNumber * (totalSum - markedSums[lastCompletedIndex]);

    std::cout << "Part 2: "
              << answer << std::endl;
}

int main()
{
    FileInput f("inputs/4.txt");
    std::vector<int> inputDrawnNumbers;
    std::vector<array<array<int, 5>, 5>> inputBoards;

    std::string inputDrawnNumbersString = f.nextString();
    inputDrawnNumbers = Util::Split(inputDrawnNumbersString, ',', 10);

    while (f.hasNext())
    {
        array<array<int, 5>, 5> board = {0};
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                board[i][j] = f.nextInt();
            }
        }
        inputBoards.push_back(board);
    }

    std::cout << "Day 4" << std::endl;
    part1(inputDrawnNumbers, inputBoards);
    part2(inputDrawnNumbers, inputBoards);
    return 0;
}