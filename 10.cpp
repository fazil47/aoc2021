#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "lib/FileInput.h"
#include "lib/Util.h"

enum LegalCharacter
{
    Curly,
    Normal,
    Square,
    Angle,
    Unset
};

class Chunk
{
    LegalCharacter boundaryChar = Unset;
    bool isClosed;
    std::vector<Chunk> children;

    bool IsClosingChar(char c)
    {
        return c == ')' || c == ']' || c == '}' || c == '>';
    }

    bool AllChildrenClosed()
    {
        for (auto &child : children)
        {
            if (!child.isClosed)
            {
                return false;
            }
        }
        return true;
    }

    bool IsClosingBoundary(char c)
    {
        if (boundaryChar == Normal)
            return c == ')';
        else if (boundaryChar == Curly)
            return c == '}';
        else if (boundaryChar == Square)
            return c == ']';
        else if (boundaryChar == Angle)
            return c == '>';
        else
            return false;
    }

    char GetClosingBoundary()
    {
        if (boundaryChar == Normal)
            return ')';
        else if (boundaryChar == Curly)
            return '}';
        else if (boundaryChar == Square)
            return ']';
        else if (boundaryChar == Angle)
            return '>';
        else
            return '\0';
    }

    void SetBoundaryChar(char c)
    {
        if (c == '{')
        {
            boundaryChar = LegalCharacter::Curly;
        }
        else if (c == '[')
        {
            boundaryChar = LegalCharacter::Square;
        }
        else if (c == '<')
        {
            boundaryChar = LegalCharacter::Angle;
        }
        else if (c == '(')
        {
            boundaryChar = LegalCharacter::Normal;
        }
    }

    int GetErrorScore(char c)
    {
        switch (c)
        {
        case ')':
            return 3;
        case ']':
            return 57;
        case '}':
            return 1197;
        case '>':
            return 25137;
        }

        return -1;
    }

public:
    Chunk() : boundaryChar(Unset), isClosed(false) {}

    bool IsClosed()
    {
        return isClosed;
    }

    // Returns syntax error score
    int AddCharacter(char c)
    {
        if (boundaryChar == Unset)
        {
            SetBoundaryChar(c);
        }
        else if (AllChildrenClosed() && IsClosingChar(c))
        {
            if (IsClosingBoundary(c))
            {
                isClosed = true;
            }
            else
            {
                return GetErrorScore(c);
            }
        }
        else
        {
            if (children.size() == 0 || children.back().IsClosed())
            {
                children.push_back(Chunk());
            }

            return children.back().AddCharacter(c);
        }

        return 0;
    }

    // Returns completion string if the chunk isn't closed or unset
    std::string GetCompletionString()
    {
        if (isClosed || boundaryChar == Unset)
        {
            return "";
        }

        std::string completionString = "";
        for (auto &child : children)
        {
            completionString += child.GetCompletionString();
        }

        return completionString + GetClosingBoundary();
    }
};

class NavigationSubsystem
{
    std::vector<std::vector<Chunk>> incompleteLines, corruptedLines;
    int syntaxErrorScore;

    static long long int GetCompletionCharScore(char c)
    {
        switch (c)
        {
        case ')':
            return 1;
        case ']':
            return 2;
        case '}':
            return 3;
        case '>':
            return 4;
        }

        return -1;
    }

    static long long int GetCompletionStringScore(std::string completionString)
    {
        long long int score = 0;
        for (char c : completionString)
        {
            score = (score * 5) + GetCompletionCharScore(c);
        }

        return score;
    }

public:
    NavigationSubsystem() : syntaxErrorScore(0) {}

    int GetErrorScore()
    {
        return syntaxErrorScore;
    }

    void AddLine(std::vector<Chunk> line, int errorScore, bool isCorrupted)
    {
        if (isCorrupted)
        {
            syntaxErrorScore += errorScore;
            corruptedLines.push_back(line);
        }
        else
        {
            incompleteLines.push_back(line);
        }
    }

    std::vector<std::string> GetCompletionStrings()
    {
        std::vector<std::string> completionStrings;
        for (std::vector<Chunk> &line : incompleteLines)
        {
            for (Chunk &chunk : line)
            {
                // Some chunks within an incomplete chunk maybe closed
                if (!chunk.IsClosed())
                {
                    completionStrings.push_back(chunk.GetCompletionString());
                }
            }
        }

        return completionStrings;
    }

    std::vector<long long int> GetCompletionStringScores()
    {
        std::vector<std::string> completionStrings = GetCompletionStrings();
        std::vector<long long int> completionStringScores;

        for (std::string completionString : completionStrings)
        {
            completionStringScores.push_back(GetCompletionStringScore(completionString));
        }

        return completionStringScores;
    }
};

// 315693
void Part1(NavigationSubsystem &navSys)
{
    std::cout << "Part 1: "
              << navSys.GetErrorScore() << std::endl;
}

// 1870887234
void Part2(NavigationSubsystem &navSys)
{
    std::vector<long long int> completionStringScores = navSys.GetCompletionStringScores();

    std::sort(completionStringScores.begin(), completionStringScores.end());

    std::cout << "Part 2: "
              << completionStringScores[completionStringScores.size() / 2] << std::endl;
}

int main()
{
    FileInput f("inputs/10.txt");
    NavigationSubsystem navSys;

    while (f.hasNext())
    {
        std::string lineString = f.nextLine();
        std::vector<Chunk> line(1, Chunk());
        int errorScore = 0;

        for (char c : lineString)
        {
            if (line.back().IsClosed())
            {
                line.push_back(Chunk());
            }

            errorScore = line.back().AddCharacter(c);

            if (errorScore != 0)
            {
                break;
            }
        }

        bool isCorrupted = errorScore != 0;
        navSys.AddLine(line, errorScore, isCorrupted);
    }

    std::cout << "Day 10" << std::endl;
    Part1(navSys);
    Part2(navSys);
    return 0;
}