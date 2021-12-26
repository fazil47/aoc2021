#include <iostream>
#include <vector>
#include <array>

#include "lib/FileInput.h"
#include "lib/Util.h"

// Grouping lantern fishes based on their internal timer
class LanternFishGroups
{
    int timer;
    long long int population;

public:
    LanternFishGroups() : timer(0), population(0) {}
    LanternFishGroups(int timer) : timer(timer), population(0) {}

    void addFish() { population = population + static_cast<long long int>(1); }
    void addFishes(long long int fishes) { population = population + fishes; }

    int update()
    {
        if (timer > 0)
        {
            timer--;
            return timer;
        }
        else
        {
            timer = 6;
            return 8;
        }
    }

    long long int GetGroupPopulation() { return population; }
};

class LanternFishs
{
    std::array<LanternFishGroups, 9> fishes;
    int day = 0;

public:
    LanternFishs(std::vector<int> initialTimers)
    {
        for (int i = 0; i < 9; i++)
        {
            fishes[i] = LanternFishGroups(i);
        }
        for (int timer : initialTimers)
        {
            fishes[timer].addFish();
        }
    }

    void update()
    {
        day++;

        std::array<LanternFishGroups, 9> newFishes;
        for (int i = 0; i < 9; i++)
        {
            newFishes[i] = LanternFishGroups(i);
        }

        for (int i = 0; i < 9; i++)
        {
            if (fishes[i].GetGroupPopulation() > 0)
            {
                int newTimer = fishes[i].update();

                if (newTimer == 8)
                {
                    newFishes[8].addFishes(fishes[i].GetGroupPopulation());
                    newFishes[6].addFishes(fishes[i].GetGroupPopulation());
                }
                else if (newTimer == 6)
                {
                    newFishes[6].addFishes(fishes[i].GetGroupPopulation());
                }
                else if (newTimer != 6)
                {
                    newFishes[newTimer] = fishes[i];
                }
            }
        }
        fishes = newFishes;
    }

    long long int GetPopulation()
    {
        long long int population = 0;
        for (LanternFishGroups fishGroup : fishes)
        {
            population = population + fishGroup.GetGroupPopulation();
        }
        return population;
    }
};

long long int GetPopulationAfterTime(LanternFishs fishes, int days)
{
    for (int i = 0; i < days; i++)
    {
        fishes.update();
    }

    return fishes.GetPopulation();
}

// 386640
void Part1(LanternFishs &fishes)
{
    std::cout << "Part 1: "
              << GetPopulationAfterTime(fishes, 80) << std::endl;
}

// 1733403626279
void Part2(LanternFishs &fishes)
{
    std::cout << "Part 2: "
              << GetPopulationAfterTime(fishes, 256) << std::endl;
}

int main()
{
    FileInput f("inputs/6.txt");

    std::vector<int> values = Util::Split(f.nextLine(), ',', 10);
    LanternFishs fishes(values);

    std::cout << "Day 6" << std::endl;
    Part1(fishes);
    Part2(fishes);
    return 0;
}