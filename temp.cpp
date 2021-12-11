#include <iostream>
// #include <string>
// #include <vector>

#include "Util.h"

int main()
{
    std::string s = "Hello,How are you, I am fine";
    std::vector<std::string> v = Util::Split(s, ',');
    for (auto i : v)
    {
        std::cout << i << std::endl;
    }
    return 0;
}