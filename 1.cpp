#include <iostream>
#include <string>
#include <vector>

#include "lib/FileInput.h"

int accumulateSum(int start, int count, std::vector<int> &vec)
{
    int accumulatedSum = 0;
    for (int i = start; i < start + count; i++)
    {
        accumulatedSum += vec[i];
    }
    return accumulatedSum;
}

void part1(std::vector<int> &vec)
{
    int count = 0;
    for (int i = 1; i < vec.size(); ++i)
    {
        if (accumulateSum(i - 1, 1, vec) < accumulateSum(i, 1, vec))
        {
            count++;
        }
    }
    std::cout << "Part 1: " << count << std::endl;
}

void part2(std::vector<int> &vec)
{
    int count = 0;
    for (int i = 1; i < vec.size(); ++i)
    {
        if (accumulateSum(i - 1, 3, vec) < accumulateSum(i, 3, vec))
        {
            count++;
        }
    }
    std::cout << "Part 2: " << count << std::endl;
}

int main()
{
    FileInput f("inputs/1.txt");
    std::vector<int> inputVec;
    while (f.hasNext())
    {
        inputVec.push_back(f.nextInt());
    }
    std::cout << "Day 1" << std::endl;
    part1(inputVec);
    part2(inputVec);
    return 0;
}