#include <iostream>
#include <array>
#include <vector>

#include "lib/FileInput.h"
#include "lib/Util.h"

using std::array;

class Point
{
public:
    int height;
    array<int, 2> position;
    bool isLowPoint, isInBasin;

    Point() : height(0), isLowPoint(false), isInBasin(false), position({-1, -1}) {}
    Point(int height, array<int, 2> position) : height(height), isLowPoint(true), isInBasin(false), position(position) {}

    void SetPosition(array<int, 2> position)
    {
        this->position = position;
    }

    std::vector<array<int, 2>> GetNeighbours(const int &map_width, const int &map_height)
    {
        std::vector<array<int, 2>> neighbours;

        if (position[0] > 0)
        {
            neighbours.push_back({position[0] - 1, position[1]});
        }

        if (position[0] < map_height - 1)
        {
            neighbours.push_back({position[0] + 1, position[1]});
        }

        if (position[1] > 0)
        {
            neighbours.push_back({position[0], position[1] - 1});
        }

        if (position[1] < map_width - 1)
        {
            neighbours.push_back({position[0], position[1] + 1});
        }

        return neighbours;
    }

    void ConnectNeighbours(Point &neighbour)
    {

        if (neighbour.height < height)
        {
            isLowPoint = false;
        }
        else if (neighbour.height > height)
        {
            neighbour.isLowPoint = false;
        }
        else
        {
            isLowPoint = false;
            neighbour.isLowPoint = false;
        }
    }

    bool IsValid()
    {
        return height >= 0 && height <= 9;
    }
};

class HeightMap
{
    std::vector<std::vector<Point>> map;
    std::vector<std::vector<Point *>> basins;
    int mapWidth, mapHeight;
    std::vector<Point *> lowPoints;

public:
    HeightMap(int mapWidth) : mapWidth(mapWidth), mapHeight(0) {}

    int GetMapHeight()
    {
        return mapHeight;
    }

    void AddRow(std::vector<Point> &row)
    {
        map.push_back(row);
        mapHeight++;
    }

    void AddNeighboursAbove()
    {
        if (mapHeight > 1)
        {
            for (int i = 0; i < mapWidth; ++i)
            {
                map[mapHeight - 1][i].ConnectNeighbours(map[mapHeight - 2][i]);
            }
        }
    }

    void AddRowAndMeetNeighbours(std::vector<Point> &row)
    {
        AddRow(row);
        AddNeighboursAbove();
    }

    void FindLowPoints()
    {
        for (int i = 0; i < mapHeight; ++i)
        {
            for (int j = 0; j < mapWidth; ++j)
            {
                Point *point = &map[i][j];
                if (point->isLowPoint)
                {
                    lowPoints.push_back(point);
                }
            }
        }
    }

    std::vector<Point *> GetLowPoints()
    {
        return lowPoints;
    }

    void FindBasins()
    {
        for (Point *point : lowPoints)
        {
            std::vector<Point *> basin;
            GrowBasin(*this, basin, point);
            basins.push_back(basin);
        }
    }

    std::vector<std::vector<Point *>> GetBasins()
    {
        return basins;
    }

    static void GrowBasin(HeightMap &heightMap, std::vector<Point *> &basin, Point *point)
    {
        point->isInBasin = true;
        basin.push_back(point);

        for (array<int, 2> &pos : point->GetNeighbours(heightMap.mapWidth, heightMap.mapHeight))
        {
            Point *neighbour = &(heightMap.map[pos[0]][pos[1]]);
            if (neighbour->height == 9 || neighbour->isInBasin)
            {
                continue;
            }

            GrowBasin(heightMap, basin, neighbour);
        }
    }
};

// 539
void Part1(HeightMap &heightMap)
{
    heightMap.FindLowPoints();
    std::vector<Point *> lowPoints = heightMap.GetLowPoints();
    int sum = 0;
    for (auto &point : lowPoints)
    {
        sum += point->height + 1;
    }

    std::cout << "Part 1: "
              << sum << std::endl;
}

// 736920
void Part2(HeightMap &heightMap)
{
    heightMap.FindBasins();
    std::vector<std::vector<Point *>> basins = heightMap.GetBasins();

    std::array<int, 3> threeLargestBasinSizes = {INT_MIN, INT_MIN, INT_MIN};
    for (std::vector<Point *> basin : basins)
    {
        int size = basin.size();
        if (size > threeLargestBasinSizes[0])
        {
            threeLargestBasinSizes[2] = threeLargestBasinSizes[1];
            threeLargestBasinSizes[1] = threeLargestBasinSizes[0];
            threeLargestBasinSizes[0] = size;
        }
        else if (size > threeLargestBasinSizes[1])
        {
            threeLargestBasinSizes[2] = threeLargestBasinSizes[1];
            threeLargestBasinSizes[1] = size;
        }
        else if (size > threeLargestBasinSizes[2])
        {
            threeLargestBasinSizes[2] = size;
        }
    }

    std::cout << "Part 2: "
              << threeLargestBasinSizes[0] * threeLargestBasinSizes[1] * threeLargestBasinSizes[2] << std::endl;
}

int main()
{
    FileInput f("inputs/9.txt");

    int width = (f.nextString()).length();
    f.GoToBeginning();
    HeightMap heightMap(width);

    while (f.hasNext())
    {
        std::string s = f.nextString();
        std::vector<Point> row;

        int firstHeight = std::stoi(std::string(1, s[0]));
        int mapHeight = heightMap.GetMapHeight();
        row.push_back(Point(firstHeight, {mapHeight, 0}));
        for (int i = 1; i < s.length(); ++i)
        {
            int height = std::stoi(std::string(1, s[i]));
            Point point(height, {mapHeight, i});
            point.ConnectNeighbours(row.back());
            row.push_back(point);
        }

        heightMap.AddRowAndMeetNeighbours(row);
    }

    std::cout << "Day 9" << std::endl;
    Part1(heightMap);
    Part2(heightMap);
    return 0;
}