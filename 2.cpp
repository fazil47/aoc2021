#include <iostream>
#include <string>

#include "FileInput.h"

bool isDepth(std::string direction)
{
    return direction == "down" || direction == "up";
}

void part1(FileInput &f)
{
    std::string direction;
    int distance, xPosition = 0, depth = 0;
    while (f.hasNext())
    {
        direction = f.nextString();
        distance = f.nextInt();

        if (isDepth(direction))
        {
            if (direction == "down")
            {
                depth += distance;
            }
            else
            {
                depth -= distance;
            }
        }
        else
        {
            xPosition += distance;
        }
    }
    std::cout << "Part 1: " << xPosition * depth << std::endl;
}

void part2(FileInput &f)
{
    std::string direction;
    int distance, xPosition = 0, depth = 0, aim = 0;
    while (f.hasNext())
    {
        direction = f.nextString();
        distance = f.nextInt();

        if (isDepth(direction))
        {
            if (direction == "down")
            {
                aim += distance;
            }
            else
            {
                aim -= distance;
            }
        }
        else
        {
            xPosition += distance;
            depth += aim * distance;
        }
    }
    std::cout << "Part 2: " << xPosition * depth << std::endl;
}

int main()
{
    FileInput f("2.txt");
    std::cout << "Day 2" << std::endl;
    part1(f);
    f.GoToBeginning();
    part2(f);
    return 0;
}