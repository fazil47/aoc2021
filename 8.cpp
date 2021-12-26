#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <unordered_map>

#include "lib/FileInput.h"
#include "lib/Util.h"

// Maps the patterns to the correct digits
std::unordered_map<std::string, int> FindPatternToDigit(const std::array<std::string, 10> &signalPatterns)
{
    std::unordered_map<std::string, int> patternToDigit;
    std::array<std::string, 10> digitToPattern;
    std::unordered_map<char, char> originalToReconnection;
    std::vector<std::string> unknownFiveLetterPatterns, unknownSixLetterPatterns;

    // Finding patterns of 1, 4, 7 and 8
    for (std::string pattern : signalPatterns)
    {
        int len = pattern.length();
        if (len == 2)
        {
            digitToPattern[1] = pattern;
            patternToDigit[pattern] = 1;
        }
        else if (len == 3)
        {
            digitToPattern[7] = pattern;
            patternToDigit[pattern] = 7;
        }
        else if (len == 4)
        {
            digitToPattern[4] = pattern;
            patternToDigit[pattern] = 4;
        }
        else if (len == 5)
        {
            unknownFiveLetterPatterns.push_back(pattern);
        }
        else if (len == 6)
        {
            unknownSixLetterPatterns.push_back(pattern);
        }
        else if (len == 7)
        {
            digitToPattern[8] = pattern;
            patternToDigit[pattern] = 8;
        }
    }

    // To find signal of a
    originalToReconnection['a'] = Util::StringDifference(digitToPattern[7], digitToPattern[7])[0];

    // To find pattern of 9
    std::string pattern4Union7 = Util::StringUnion(digitToPattern[4], digitToPattern[7]);
    for (int i = 0; i < unknownSixLetterPatterns.size(); ++i)
    {
        std::string pattern = unknownSixLetterPatterns[i];
        if (Util::IsStringSubSet(pattern, pattern4Union7))
        {
            digitToPattern[9] = pattern;
            patternToDigit[pattern] = 9;
            unknownSixLetterPatterns.erase(unknownSixLetterPatterns.begin() + i);
            break;
        }
    }

    // To find signal of g
    originalToReconnection['g'] = Util::StringDifference(digitToPattern[9], pattern4Union7)[0];

    // To find pattern of 3
    for (int i = 0; i < unknownFiveLetterPatterns.size(); ++i)
    {
        std::string pattern = unknownFiveLetterPatterns[i];
        if (Util::IsStringSubSet(pattern, digitToPattern[1]))
        {
            digitToPattern[3] = pattern;
            patternToDigit[pattern] = 3;
            unknownFiveLetterPatterns.erase(unknownFiveLetterPatterns.begin() + i);
            break;
        }
    }

    // To find signal of b
    originalToReconnection['b'] = Util::StringDifference(digitToPattern[9], digitToPattern[3])[0];

    // To find signal of e
    originalToReconnection['e'] = Util::StringDifference(digitToPattern[8], digitToPattern[9])[0];

    // To find pattern of 2
    for (int i = 0; i < unknownFiveLetterPatterns.size(); ++i)
    {
        std::string pattern = unknownFiveLetterPatterns[i];
        if (Util::In(pattern, originalToReconnection['e']))
        {
            digitToPattern[2] = pattern;
            patternToDigit[pattern] = 2;
            unknownFiveLetterPatterns.erase(unknownFiveLetterPatterns.begin() + i);
            break;
        }
    }

    // To find pattern of 5
    digitToPattern[5] = unknownFiveLetterPatterns[0];
    patternToDigit[digitToPattern[5]] = 5;
    unknownFiveLetterPatterns.clear();

    // To find pattern of 6
    std::string eReconnection = std::string(1, originalToReconnection['e']);
    std::string pattern5UnionE = Util::StringUnion(digitToPattern[5], eReconnection);
    for (int i = 0; i < unknownSixLetterPatterns.size(); ++i)
    {
        std::string pattern = unknownSixLetterPatterns[i];
        if (pattern == pattern5UnionE)
        {
            digitToPattern[6] = pattern;
            patternToDigit[pattern] = 6;
            unknownSixLetterPatterns.erase(unknownSixLetterPatterns.begin() + i);
            break;
        }
    }

    // To find pattern of 0
    digitToPattern[0] = unknownSixLetterPatterns[0];
    patternToDigit[digitToPattern[0]] = 0;
    unknownSixLetterPatterns.clear();

    return patternToDigit;
}

// 495
void Part1(const std::vector<std::array<std::string, 4>> &fourDigitOutputList)
{
    int count = 0; // Number of 1s, 4s, 7s and 8s

    for (auto &output : fourDigitOutputList)
    {
        for (std::string digit : output)
        {
            int length = digit.length();
            if (length == 2 || length == 3 || length == 4 || length == 7)
            {
                count++;
            }
        }
    }

    std::cout << "Part 1: "
              << count << std::endl;
}

// 1055164
void Part2(const std::vector<std::array<std::string, 10>> &signalPatternsList, const std::vector<std::array<std::string, 4>> &fourDigitOutputList)
{
    int sum = 0;

    for (int i = 0; i < signalPatternsList.size(); ++i)
    {
        std::array<std::string, 10> signalPatterns = signalPatternsList[i];
        std::array<std::string, 4> fourDigitOutput = fourDigitOutputList[i];
        std::unordered_map<std::string, int> patternToDigit = FindPatternToDigit(signalPatterns);

        int value = 0;
        for (std::string digitPattern : fourDigitOutput)
        {
            value = (value * 10) + patternToDigit[digitPattern];
        }
        sum += value;
    }

    std::cout << "Part 2: " << sum << std::endl;
}

int main()
{
    FileInput f("inputs/8.txt");

    std::vector<std::array<std::string, 10>> signalPatternsList;
    std::vector<std::array<std::string, 4>> fourDigitOutputList;

    while (f.hasNext())
    {
        std::array<std::string, 10> signalPatterns;
        for (int i = 0; i < 10; i++)
        {
            signalPatterns[i] = f.nextString();
            std::sort(signalPatterns[i].begin(), signalPatterns[i].end());
        }
        signalPatternsList.push_back(signalPatterns);

        f.nextString(); // skip the delimiter

        std::array<std::string, 4> fourDigitOutput;
        for (int i = 0; i < 4; i++)
        {
            fourDigitOutput[i] = f.nextString();
            std::sort(fourDigitOutput[i].begin(), fourDigitOutput[i].end());
        }
        fourDigitOutputList.push_back(fourDigitOutput);
    }

    std::cout << "Day 8" << std::endl;
    Part1(fourDigitOutputList);
    Part2(signalPatternsList, fourDigitOutputList);
    return 0;
}

// Correct Layout

// 0:      1:      2:      3:      4:
//  aaaa    ....    aaaa    aaaa    ....
// b    c  .    c  .    c  .    c  b    c
// b    c  .    c  .    c  .    c  b    c
//  ....    ....    dddd    dddd    dddd
// e    f  .    f  e    .  .    f  .    f
// e    f  .    f  e    .  .    f  .    f
//  gggg    ....    gggg    gggg    ....

//   5:      6:      7:      8:      9:
//  aaaa    aaaa    aaaa    aaaa    aaaa
// b    .  b    .  .    c  b    c  b    c
// b    .  b    .  .    c  b    c  b    c
//  dddd    dddd    ....    dddd    dddd
// .    f  e    f  .    f  e    f  .    f
// .    f  e    f  .    f  e    f  .    f
//  gggg    gggg    ....    gggg    gggg

// Digits with 2 segments: 1
// Digits with 3 segments: 7
// Digits with 4 segments: 4
// Digits with 5 segments: 2, 3, 5
// Digits with 6 segments: 0, 6, 9
// Digits with 7 segments: 8

// Digits identified: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
// Signals identified: a, b, c, d, e, f, g

// 1, 7, 4 and 8 are unique
// a is found by finding out what is lacking in 1's signal compared to 7
// 9 is found by finding out which 6 letter pattern has every letter in the signals of 4 and 7
// g is found by finding what 9's signal has which is missing from the combination of 4's and 7's signals
// 3 is found by finding out which 5 letter pattern has every letter in the signal of 1
// b is found by finding out which letter from 9's pattern is missing in 3's pattern
// e is the letter that's missing from 9's pattern
// 2 is the only 5 letter pattern with e
// 5 is the only 5 letter pattern left
// 6 is the pattern containing all of 5's letters plus e
// 0 is the only pattern left
// c is the only letter not in 6's pattern
// f is the only letter not in 2's pattern other than b
// d is the only letter not in 0's pattern