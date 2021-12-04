#include <iostream>
#include <string>
#include "FileInput.h"

int main()
{
    FileInput f("1.txt");
    int new_num, prev, count = 0;
    new_num = f.nextInt();
    prev = new_num;
    while (f.hasNext())
    {
        new_num = f.nextInt();
        if (new_num == 0)
            break;

        if (new_num > prev)
        {
            count++;
        }
        prev = new_num;
    }
    std::cout << count << std::endl;
    return 0;
}