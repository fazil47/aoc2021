#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

#include "lib/FileInput.h"
#include "lib/Util.h"

int get_increasing_sum(int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += i;
    }
    return sum;
}

int get_reverse_increasing_sum(int sum)
{
    int i = 0;

    while (sum > 0)
    {
        sum -= i;
        i++;
    }

    return i - 1;
}

float get_mean(const std::vector<int> &v)
{
    float sum = 0;
    int size = v.size();

    for (int i = 0; i < size; i++)
    {
        sum += v[i];
    }

    return sum / static_cast<float>(size);
}

int get_median(const std::vector<int> &v)
{
    int size = v.size();

    if (size % 2 == 0)
    {
        return (v[size / 2] + v[size / 2 - 1]) / 2;
    }
    else
    {
        return v[size / 2];
    }
}

float get_variance(const std::vector<int> &v)
{
    float mean = get_mean(v);
    float ssum = 0;
    for (int i = 0; i < v.size(); i++)
    {
        ssum += pow(v[i] - mean, 2);
    }
    return ssum / static_cast<float>(v.size());
}

float get_standard_deviation(const std::vector<int> &v)
{
    return sqrt(get_variance(v));
}

int get_fuel_cost(const std::vector<int> &distances, int destination, bool constant_fuel_rate = true)
{
    int sum = 0;
    if (constant_fuel_rate)
    {
        for (int n : distances)
        {
            sum += abs(n - destination);
        }
    }
    else
    {
        for (int n : distances)
        {
            sum += get_increasing_sum(abs(n - destination));
        }
    }
    return sum;
}

// 329389
void Part1(const std::vector<int> &h_positions)
{
    int median = get_median(h_positions);

    std::cout << "Part 1: "
              << get_fuel_cost(h_positions, median) << std::endl;
}

// 86397080 at 459
void Part2(const std::vector<int> &h_positions)
{
    float mean = get_mean(h_positions);
    float min_mean = std::min(ceil(mean), floor(mean));

    std::cout << "Part 2: "
              << get_fuel_cost(h_positions, min_mean, false) << std::endl;
}

int main()
{
    FileInput f("inputs/7.txt");
    std::vector<int> h_positions = Util::Split(f.nextLine(), ',', 10);
    std::sort(h_positions.begin(), h_positions.end());

    std::cout << "Day 7" << std::endl;
    Part1(h_positions);
    Part2(h_positions);
    return 0;
}