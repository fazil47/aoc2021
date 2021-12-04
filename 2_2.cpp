#include <iostream>
#include "FileInput.h"
#include <string>

bool isDepth(std::string direction)
{
    return direction == "down" || direction == "up";
}

int main()
{
    FileInput f("2.txt");
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
    std::cout << xPosition * depth << std::endl;
    return 0;
}