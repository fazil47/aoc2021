#include <iostream>
#include "FileInput.h"
#include <vector>

class Triplet
{
    int count;
    std::vector<int> vec;

public:
    Triplet()
    {
        vec.clear();
    }

    int add(int x)
    {
        if (vec.size() < 2)
        {
            vec.push_back(x);
            return -1;
        }
        else
        {
            int sum = vec[0] + vec[1] + x;
            vec.clear();
            return sum;
        }
    }
};

int main()
{
    FileInput fi("1.txt");
    Triplet t1, t2, t3;
    int s1 = 0, s2 = 0, s3 = 0, sum_prev = 0, sum_curr = 0, count = 0;

    int x = fi.nextInt();
    t1.add(x);

    x = fi.nextInt();
    t1.add(x);
    t2.add(x);

    x = fi.nextInt();
    sum_curr = t1.add(x);
    t2.add(x);
    t3.add(x);

    while (fi.hasNext())
    {
        x = fi.nextInt();

        s1 = t1.add(x);
        s2 = t2.add(x);
        s3 = t3.add(x);

        sum_prev = sum_curr;
        sum_curr = s1 > 0 ? s1 : (s2 > 0 ? s2 : s3);
        if (sum_curr > sum_prev)
        {
            count++;
        }
    }

    std::cout << count << std::endl;
    return 0;
}