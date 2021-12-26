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
    static bool In(const std::string &s, char c);
    static bool IsSubString(const std::string &bigger, const std::string &smaller);
    static std::string StringDifference(const std::string &a, const std::string &b);
    static std::string StringUnion(const std::string &a, const std::string &b);
    static std::string StringIntersection(const std::string &a, const std::string &b);
    static bool IsStringSubSet(const std::string &bigger, const std::string &smaller);
};