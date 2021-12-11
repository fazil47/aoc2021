#include <sstream>

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