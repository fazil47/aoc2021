#pragma once

#include <vector>
#include <string>

class Util
{
public:
    static std::vector<std::string> Split(const std::string &s, char delimiter);
    static std::vector<std::string> Split(const std::string &s, std::string delimiter);
    static std::vector<int> Split(const std::string &s, char delimiter, int base);
    static bool In(const std::vector<int> &v, int value);
};