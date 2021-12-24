#include <string>

#include "FileInput.h"

FileInput::FileInput(const char *fileName)
{
    file.open(fileName);
}

FileInput::~FileInput()
{
    file.close();
}

int FileInput::nextInt()
{
    int value;
    file >> value;
    return value;
}

std::string FileInput::nextString()
{
    std::string value;
    file >> value;
    return value;
}

std::string FileInput::nextLine()
{
    std::string value;
    std::getline(file, value);
    return value;
}

float FileInput::nextFloat()
{
    float value;
    file >> value;
    return value;
}

char FileInput::nextChar()
{
    char value;
    file >> value;
    return value;
}

bool FileInput::hasNext()
{
    return !file.eof();
}

void FileInput::GoToBeginning()
{
    file.clear();
    file.seekg(0, std::ios::beg);
}