#include <iostream>
#include "FileInput.h"
#include <vector>
#include <math.h>

const int NUM_DIGITS = 12;

int main()
{
    FileInput f("3.txt");

    // First element of each sub-array is the number of 0s in a particular column and the second element is the number of 1s in a particular column
    int bit_count[NUM_DIGITS][2] = {0};
    int gamma = 0, epsilon = 0;
    std::string s;

    while (f.hasNext())
    {
        s = f.nextString();
        for (int i = 0; i < NUM_DIGITS; i++)
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

    for (int i = 0; i < NUM_DIGITS; i++)
    {
        int most_common = bit_count[i][0] > bit_count[i][1] ? 0 : 1;
        gamma += most_common * pow(2, NUM_DIGITS - i - 1);
        epsilon += abs(1 - most_common) * pow(2, NUM_DIGITS - i - 1);
    }

    std::cout << gamma * epsilon << std::endl;

    return 0;
}