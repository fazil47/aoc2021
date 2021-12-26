#include <iostream>
#include <vector>
#include <math.h>
#include <array>

#include "lib/FileInput.h"

int findO2Rating(const std::vector<std::string> &input, int bit_position, const int bit_count[2], int num_digits)
{
    if (input.size() == 1 || bit_position == num_digits)
    {
        return std::stoi(input[0], nullptr, 2);
    }

    std::vector<std::string> new_input;

    char most_common = bit_count[0] > bit_count[1] ? '0' : '1';
    int new_bit_count[2] = {0};

    for (int i = 0; i < input.size(); i++)
    {
        if (input[i][bit_position] == most_common)
        {
            if (input[i][bit_position + 1] == '0')
            {
                new_bit_count[0]++;
            }
            else
            {
                new_bit_count[1]++;
            }
            new_input.push_back(input[i]);
        }
    }

    return findO2Rating(new_input, bit_position + 1, new_bit_count, num_digits);
}

int findCo2Rating(const std::vector<std::string> &input, int bit_position, const int bit_count[2], int num_digits)
{
    if (input.size() == 1 || bit_position == num_digits)
    {
        return stoi(input[0], nullptr, 2);
    }

    std::vector<std::string> new_input;

    char least_common = bit_count[0] <= bit_count[1] ? '0' : '1';
    int new_bit_count[2] = {0};

    for (int i = 0; i < input.size(); i++)
    {
        if (input[i][bit_position] == least_common)
        {
            if (input[i][bit_position + 1] == '0')
            {
                new_bit_count[0]++;
            }
            else
            {
                new_bit_count[1]++;
            }
            new_input.push_back(input[i]);
        }
    }

    return findCo2Rating(new_input, bit_position + 1, new_bit_count, num_digits);
}

// 852500
void part1(std::vector<std::string> input, const int num_digits)
{
    // First element of each sub-array is the number of 0s in a particular column and the second element is the number of 1s in a particular column
    std::vector<std::array<int, 2>> bit_count(num_digits, std::array<int, 2>({0}));
    int gamma = 0, epsilon = 0;

    for (std::string s : input)
    {
        for (int i = 0; i < num_digits; i++)
        {
            if (s[i] == '0')
            {
                bit_count[i][0]++;
            }
            else
            {
                bit_count[i][1]++;
            }
        }
    }

    // The decimal value is found by bit shifting
    for (int i = 0; i < num_digits; i++)
    {
        int most_common = bit_count[i][0] > bit_count[i][1] ? 0 : 1;
        gamma += most_common;
        gamma <<= 1;
        epsilon += 1 - most_common;
        epsilon <<= 1;
    }
    gamma >>= 1;
    epsilon >>= 1;

    std::cout << "Part 1: " << gamma * epsilon << std::endl;
}

// 1007985
void part2(std::vector<std::string> input, const int num_digits)
{
    int bit_count[2] = {0};
    int o2 = 0, co2 = 0;
    std::string s;
    std::vector<std::string> bin_nums;

    for (std::string s : input)
    {
        if (s[0] == '0')
        {
            bit_count[0]++;
        }
        else
        {
            bit_count[1]++;
        }

        bin_nums.push_back(s);
    }

    o2 = findO2Rating(bin_nums, 0, bit_count, num_digits);
    co2 = findCo2Rating(bin_nums, 0, bit_count, num_digits);

    std::cout << "Part 2: " << o2 * co2 << std::endl;
}

int main()
{
    FileInput f("inputs/3.txt");

    std::vector<std::string> input;
    while (f.hasNext())
    {
        input.push_back(f.nextString());
    }
    const int num_digits = input[0].size();

    std::cout << "Day 3" << std::endl;
    part1(input, num_digits);
    f.GoToBeginning();
    part2(input, num_digits);
    return 0;
}