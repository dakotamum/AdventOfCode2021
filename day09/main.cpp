#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <utility>

std::vector<std::vector<int>> readInput()
{
    std::vector<std::vector<int>> smokeMap;
    std::ifstream fin("input.txt");
    std::string line;
    while(fin >> line)
    {
        std::vector<int> rowOfInts;
        for(int i = 0; i < line.size(); i++)
        {
            rowOfInts.push_back(line[i] - '0');
        }
        smokeMap.push_back(rowOfInts);
    }
    fin.close();
    return smokeMap;
}

void part1()
{
    std::vector<std::vector<int>> smokeMap = readInput();
    std::vector<int> lowPoints;
    int rowSize = smokeMap[0].size();

    for(int i = 0; i < smokeMap.size(); i++)
    {
        for(int j = 0; j < rowSize; j++)
        {
            int currentNum = smokeMap[i][j];
            bool smallestNumber = true;
            if(i-1 >= 0 && j-1 >= 0)
                if (smokeMap[i-1][j-1] <= currentNum)
                    smallestNumber = false;
            if(i-1 >= 0)
                if (smokeMap[i-1][j] <= currentNum)
                    smallestNumber = false;
            if(i-1 >= 0 && j+1 < rowSize)
                if (smokeMap[i-1][j+1] <= currentNum)
                    smallestNumber = false;
            if(j-1 >= 0)
                if (smokeMap[i][j-1] <= currentNum)
                    smallestNumber = false;
            if(j+1 < rowSize)
                if (smokeMap[i][j+1] <= currentNum)
                    smallestNumber = false;
            if(i+1 < smokeMap.size() && j-1 >= 0)
                if (smokeMap[i+1][j-1] <= currentNum)
                    smallestNumber = false;
            if(i+1 < smokeMap.size())
                if (smokeMap[i+1][j] <= currentNum)
                    smallestNumber = false;
            if(i+1 < smokeMap.size() && j+1 < rowSize)
                if (smokeMap[i+1][j+1] <= currentNum)
                    smallestNumber = false;

            if(smallestNumber) lowPoints.push_back(currentNum);
        }
    }

    int lowPointsSum = 0;
    for(int i = 0; i < lowPoints.size(); i++)
    {
        lowPointsSum += lowPoints[i] + 1;
    }
    std::cout << lowPointsSum << std::endl;
}


void findFlows(std::map<std::pair<int, int>, bool>& flowMap, std::vector<std::vector<int>> map, int i, int j)
{
    flowMap[{i, j}] = true;
    if(i+1 < map.size()) if(map[i+1][j] > map[i][j] && !flowMap[{i+1, j}] && map[i+1][j] != 9) findFlows(flowMap, map, i+1, j);
    if(i-1 >= 0) if(map[i-1][j] > map[i][j] && !flowMap[{i-1, j}] && map[i-1][j] != 9) findFlows(flowMap, map, i-1, j);
    if(j+1 < map[0].size()) if(map[i][j+1] > map[i][j] && !flowMap[{i, j+1}] && map[i][j+1] != 9) findFlows(flowMap, map, i, j+1);
    if(j-1 >= 0) if(map[i][j-1] > map[i][j] && !flowMap[{i, j-1}] && map[i][j-1] != 9) findFlows(flowMap, map, i, j-1);
}


void part2()
{
    std::vector<std::vector<int>> smokeMap = readInput();
    std::vector<int> lowPoints;
    int rowSize = smokeMap[0].size();
    std::vector<std::map<std::pair<int, int>, bool>> flowMaps;

    int firstLargestBasin = 0;
    int secondLargestBasin = 0;
    int thirdLargestBasin = 0;

    for(int i = 0; i < smokeMap.size(); i++)
    {
        for(int j = 0; j < rowSize; j++)
        {
            int currentNum = smokeMap[i][j];
            bool smallestNumber = true;
            if(i-1 >= 0 && j-1 >= 0)
                if (smokeMap[i-1][j-1] <= currentNum)
                    smallestNumber = false;
            if(i-1 >= 0)
                if (smokeMap[i-1][j] <= currentNum)
                    smallestNumber = false;
            if(i-1 >= 0 && j+1 < rowSize)
                if (smokeMap[i-1][j+1] <= currentNum)
                    smallestNumber = false;
            if(j-1 >= 0)
                if (smokeMap[i][j-1] <= currentNum)
                    smallestNumber = false;
            if(j+1 < rowSize)
                if (smokeMap[i][j+1] <= currentNum)
                    smallestNumber = false;
            if(i+1 < smokeMap.size() && j-1 >= 0)
                if (smokeMap[i+1][j-1] <= currentNum)
                    smallestNumber = false;
            if(i+1 < smokeMap.size())
                if (smokeMap[i+1][j] <= currentNum)
                    smallestNumber = false;
            if(i+1 < smokeMap.size() && j+1 < rowSize)
                if (smokeMap[i+1][j+1] <= currentNum)
                    smallestNumber = false;
            if(smallestNumber)
            {
                std::map<std::pair<int, int>, bool> newMap;
                findFlows(newMap, smokeMap, i, j);
                flowMaps.push_back(newMap);
            }
        }
    }
    for (int i = 0; i < flowMaps.size(); i++)
    {
        int count = 0;
        for (const auto& it : flowMaps[i]) if(it.second) count++;
        if(count > firstLargestBasin)
        {
            int tmp1 = firstLargestBasin;
            int tmp2 = secondLargestBasin;
            firstLargestBasin = count;
            secondLargestBasin = tmp1;
            thirdLargestBasin = tmp2;
        }
        else if(count > secondLargestBasin)
        {
            int tmp = secondLargestBasin;
            secondLargestBasin = count;
            thirdLargestBasin = tmp;
        }
        else if(count > thirdLargestBasin)
            thirdLargestBasin = count;
    }
    std::cout << firstLargestBasin * secondLargestBasin * thirdLargestBasin << std::endl;
}

int main()
{
    part1(); 
    part2(); 
    return 0;
}