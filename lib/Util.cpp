#include <sstream>
#include <algorithm>

#include "Util.h"

std::vector<std::string> Util::Split(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::string> Util::Split(const std::string &s, std::string delimiter)
{
    std::vector<std::string> tokens = {s};
    for (int i = 0; i < delimiter.length(); i++)
    {
        std::vector<std::string> newTokens;
        for (std::string s : tokens)
        {
            std::vector<std::string> splitUpStrings = Split(s, delimiter[i]);
            newTokens.insert(newTokens.end(), splitUpStrings.begin(), splitUpStrings.end());
        }
        tokens = newTokens;
    }
    return tokens;
}

std::vector<int> Util::Split(const std::string &s, char delimiter, int base)
{
    std::vector<int> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(std::stoi(token, nullptr, base));
    }
    return tokens;
}

bool Util::In(const std::vector<int> &v, int value)
{
    for (int i : v)
    {
        if (i == value)
        {
            return true;
        }
    }

    return false;
}

bool Util::In(const std::string &s, char c)
{
    for (char i : s)
    {
        if (i == c)
        {
            return true;
        }
    }

    return false;
}

// Returns a string containing all characters in a that are not in b
std::string Util::StringDifference(const std::string &a, const std::string &b)
{
    std::string difference;
    for (char aChar : a)
    {
        bool found = false;
        for (char bChar : b)
        {
            if (aChar == bChar)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            difference += aChar;
        }
    }
    return difference;
}

std::string Util::StringUnion(const std::string &a, const std::string &b)
{
    std::string combined = b;

    for (char aChar : a)
    {
        bool found = false;
        for (char bChar : b)
        {
            if (aChar == bChar)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            combined += aChar;
        }
    }

    std::sort(combined.begin(), combined.end());

    return combined;
}

std::string Util::StringIntersection(const std::string &a, const std::string &b)
{
    std::string intersection;

    for (char aChar : a)
    {
        for (char bChar : b)
        {
            if (aChar == bChar)
            {
                intersection += aChar;
            }
        }
    }
    return intersection;
}

bool Util::IsSubString(const std::string &bigger, const std::string &smaller)
{
    if (bigger.length() < smaller.length())
    {
        return false;
    }

    for (int i = 0; i < bigger.length() - smaller.length() + 1; ++i)
    {
        if (bigger.substr(i, smaller.length()) == smaller)
        {
            return true;
        }
    }

    return false;
}

bool Util::IsStringSubSet(const std::string &bigger, const std::string &smaller)
{
    if (bigger.length() < smaller.length())
    {
        return false;
    }

    for (char c : smaller)
    {
        if (!Util::In(bigger, c))
        {
            return false;
        }
    }

    return true;
}