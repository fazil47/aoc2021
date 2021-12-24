#include <iostream>
#include <array>

#include "lib/FileInput.h"
#include "lib/Util.h"

using std::array;

bool IsVertOrHoriz(array<array<int, 2>, 2> lineSegment)
{
    return lineSegment[0][0] == lineSegment[1][0] ||
           lineSegment[0][1] == lineSegment[1][1];
}

void MarkLineSegInGrid(const array<array<int, 2>, 2> &lineSegment, std::vector<array<int, 1000>> &grid)
{
    int x1 = lineSegment[0][0];
    int y1 = lineSegment[0][1];
    int x2 = lineSegment[1][0];
    int y2 = lineSegment[1][1];

    int x = x1;
    int y = y1;
    int x_steps = x2 > x1 ? x2 - x1 : x1 - x2;
    int y_steps = y2 > y1 ? y2 - y1 : y1 - y2;
    int x_increment = x_steps == 0 ? 0 : (x2 - x1) / x_steps;
    int y_increment = y_steps == 0 ? 0 : (y2 - y1) / y_steps;

    int steps = x_steps > y_steps ? x_steps : y_steps;

    grid[x][y] += 1;
    for (int i = 0; i < steps; i++)
    {
        x += x_increment;
        y += y_increment;
        grid[x][y] += 1;
    }
}

void Part1(std::vector<array<array<int, 2>, 2>> lineSegments)
{
    std::vector<array<int, 1000>> grid(1000, array<int, 1000>({0}));

    for (array<array<int, 2>, 2> lineSegment : lineSegments)
    {
        if (IsVertOrHoriz(lineSegment))
        {
            MarkLineSegInGrid(lineSegment, grid);
        }
    }

    int count = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            if (grid[i][j] >= 2)
            {
                count++;
            }
        }
    }

    std::cout << "Part 1: "
              << count << std::endl;
}

void Part2(std::vector<array<array<int, 2>, 2>> lineSegments)
{
    std::vector<array<int, 1000>> grid(1000, array<int, 1000>({0}));

    for (array<array<int, 2>, 2> lineSegment : lineSegments)
    {
        MarkLineSegInGrid(lineSegment, grid);
    }

    int count = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            if (grid[i][j] >= 2)
            {
                count++;
            }
        }
    }

    std::cout << "Part 2: "
              << count << std::endl;
}

std::array<int, 2> StringToPoint(const std::string &str)
{
    std::array<int, 2> point;
    std::vector<std::string> digitStrings = Util::Split(str, ',');
    point[0] = std::stoi(digitStrings[0]);
    point[1] = std::stoi(digitStrings[1]);
    return point;
}

int main()
{
    FileInput f("inputs/5.txt");

    std::vector<array<array<int, 2>, 2>> lineSegments;
    while (f.hasNext())
    {
        array<int, 2> start = StringToPoint(f.nextString());
        f.nextString(); // Arrow
        array<int, 2> end = StringToPoint(f.nextString());
        lineSegments.push_back({start, end});
    }

    std::cout << "Day 5" << std::endl;
    Part1(lineSegments);
    Part2(lineSegments);
    return 0;
}