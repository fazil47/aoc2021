#include <iostream>
#include "FileInput.h"
#include <vector>
#include <math.h>

const int NUM_DIGITS = 12;

int stringToDecimal(std::string s)
{
    int result = 0;
    for (int i = 0; i < s.length(); i++)
    {
        result += (s[i] - '0') * pow(2, NUM_DIGITS - i - 1);
    }
    return result;
}

int findO2Rating(const std::vector<std::string> &input, int bit_position, const int bit_count[2])
{
    if (input.size() == 1 || bit_position == NUM_DIGITS)
    {
        return stringToDecimal(input[0]);
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

    return findO2Rating(new_input, bit_position + 1, new_bit_count);
}

int findCo2Rating(const std::vector<std::string> &input, int bit_position, const int bit_count[2])
{
    if (input.size() == 1 || bit_position == NUM_DIGITS)
    {
        return stringToDecimal(input[0]);
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

    return findCo2Rating(new_input, bit_position + 1, new_bit_count);
}

int main()
{
    FileInput f("3.txt");

    int bit_count[2] = {0};
    int o2 = 0, co2 = 0;
    std::string s;
    std::vector<std::string> bin_nums;

    while (f.hasNext())
    {
        s = f.nextString();

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

    o2 = findO2Rating(bin_nums, 0, bit_count);
    co2 = findCo2Rating(bin_nums, 0, bit_count);

    std::cout << o2 * co2 << std::endl;

    return 0;
}