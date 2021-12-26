#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

#include "lib/FileInput.h"
#include "lib/Util.h"

using std::array;

class BingoBoard
{
    array<array<int, 5>, 5> board;
    array<int, 5> markedRows{0}, markedCols{0};

    int unmarkedSum, lastMarkedNum, numbersAttempted;
    bool solved;

public:
    BingoBoard() : unmarkedSum(0), numbersAttempted(0), solved(false) {}

    BingoBoard(array<array<int, 5>, 5> board) : BingoBoard()
    {
        this->board = board;
        for (array<int, 5> &row : board)
        {
            for (int &num : row)
            {
                unmarkedSum += num;
            }
        }
    }

    int GetNumbersAttemped() { return numbersAttempted; }

    int GetResult()
    {
        if (solved)
        {
            return unmarkedSum * lastMarkedNum;
        }
        else
        {
            return -1;
        }
    }

    void MarkNumber(int number)
    {
        numbersAttempted++;

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (board[i][j] == number)
                {
                    unmarkedSum -= number;
                    lastMarkedNum = number;
                    markedRows[i]++;
                    markedCols[j]++;
                }
            }
        }

        for (int i = 0; i < 5; i++)
        {
            if (markedRows[i] == 5 || markedCols[i] == 5)
            {
                solved = true;
            }
        }
    }

    bool SolveBoard(std::vector<int> &numbers)
    {
        for (int number : numbers)
        {
            MarkNumber(number);

            if (solved)
            {
                break;
            }
        }

        return solved;
    }
};

// 65325
void part1(std::vector<BingoBoard> &inputBoards)
{
    std::cout << "Part 1: "
              << inputBoards[0].GetResult() << std::endl;
}

// 4624
void part2(std::vector<BingoBoard> &inputBoards)
{
    std::cout << "Part 2: "
              << inputBoards[inputBoards.size() - 1].GetResult() << std::endl;
}

int main()
{
    FileInput f("inputs/4.txt");
    std::vector<int> inputDrawnNumbers;
    std::vector<BingoBoard> inputBoards;

    inputDrawnNumbers = Util::Split(f.nextString(), ',', 10);

    while (f.hasNext())
    {
        array<array<int, 5>, 5> board;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                board[i][j] = f.nextInt();
            }
        }

        BingoBoard bingoBoard = BingoBoard(board);
        bool solved = bingoBoard.SolveBoard(inputDrawnNumbers);

        if (solved)
        {
            inputBoards.push_back(bingoBoard);
        }
    }

    std::sort(
        inputBoards.begin(), inputBoards.end(),
        [](BingoBoard &left, BingoBoard &right)
        {
            return left.GetNumbersAttemped() < right.GetNumbersAttemped();
        });

    std::cout << "Day 4" << std::endl;
    part1(inputBoards);
    part2(inputBoards);
    return 0;
}