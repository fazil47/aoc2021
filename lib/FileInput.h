#pragma once
#include <fstream>
#include <string>

class FileInput
{
    std::fstream file;

public:
    FileInput(const char *fileName);
    ~FileInput();
    int nextInt();
    char nextChar();
    std::string nextString();
    std::string nextLine();
    float nextFloat();
    bool hasNext();
    void GoToBeginning();
};