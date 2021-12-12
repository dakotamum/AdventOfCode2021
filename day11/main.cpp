#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::vector<int>> readInput()
{
    std::ifstream fin("input.txt");
    std::string line;
    std::vector<std::vector<int>> octopusMap;
    while(std::getline(fin, line))
    {
        std::vector<int> octopusLine;
        for(int i = 0; i < line.size(); i++)
        {
            octopusLine.push_back(line[i] - '0');
        }
        octopusMap.push_back(octopusLine);
    }
    fin.close(); 
    return octopusMap;
}

void incrementAllByOne(std::vector<std::vector<int>>& octopusMap)
{
    for(int i = 0; i < octopusMap.size(); i++) for(int j = 0; j < octopusMap[0].size(); j++) octopusMap[i][j]++;
}

void glowUp(std::vector<std::vector<int>>& octopusMap, int i, int j, int& flashes)
{
    octopusMap[i][j] = 0;
    flashes++;

    if(i-1 >= 0) if(octopusMap[i-1][j] != 0) if (++octopusMap[i-1][j] > 9) glowUp(octopusMap, i-1, j, flashes);
    if(i+1 < octopusMap.size()) if(octopusMap[i+1][j] != 0) if (++octopusMap[i+1][j] > 9) glowUp(octopusMap, i+1, j, flashes);
    if(j-1 >= 0) if(octopusMap[i][j-1] != 0) if (++octopusMap[i][j-1] > 9) glowUp(octopusMap, i, j-1, flashes);
    if(j+1 < octopusMap[0].size()) if(octopusMap[i][j+1] != 0) if (++octopusMap[i][j+1] > 9) glowUp(octopusMap, i, j+1, flashes);
    if(i-1 >= 0 && j-1 >= 0) if(octopusMap[i-1][j-1] != 0) if (++octopusMap[i-1][j-1] > 9) glowUp(octopusMap, i-1, j-1, flashes);
    if(i-1 >= 0 && j+1 < octopusMap[0].size()) if(octopusMap[i-1][j+1] != 0) if (++octopusMap[i-1][j+1] > 9) glowUp(octopusMap, i-1, j+1, flashes);
    if(i+1 < octopusMap.size() && j-1 >= 0) if(octopusMap[i+1][j-1] != 0) if (++octopusMap[i+1][j-1] > 9) glowUp(octopusMap, i+1, j-1, flashes);
    if(i+1 < octopusMap.size() && j+1 < octopusMap[0].size()) if(octopusMap[i+1][j+1] != 0) if (++octopusMap[i+1][j+1] > 9) glowUp(octopusMap, i+1, j+1, flashes);
}

void printMap(std::vector<std::vector<int>> octopusMap)
{
    for(int i = 0; i < octopusMap.size(); i++)
    {
        for(int j = 0; j < octopusMap[0].size(); j++)
        {
            std::cout << octopusMap[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

void nextStep(std::vector<std::vector<int>>& octopusMap, int& flashes)
{
    incrementAllByOne(octopusMap);
    for(int i = 0; i < octopusMap.size(); i++) for(int j = 0; j < octopusMap[0].size(); j++) if (octopusMap[i][j] > 9) glowUp(octopusMap, i, j, flashes);
}

bool checkIfAllFlashed(std::vector<std::vector<int>> octopusMap)
{
    bool wholeMapFlashed = true;
    for(int i = 0; i < octopusMap.size(); i++)
    {
        bool wholeRowFlashed = true;
        for(int j = 0; j < octopusMap[0].size(); j++)
        {
            if(octopusMap[i][j] != 0)
            {
                wholeRowFlashed = false;
                break;
            }
        }
        if (!wholeRowFlashed)
        {
            wholeMapFlashed = false;
            break;
        }
    }
    return wholeMapFlashed;
}

void part1()
{
    int flashes = 0;
    std::vector<std::vector<int>> octopusMap = readInput();
    for(int i = 0; i < 100; i++)
    {
        nextStep(octopusMap, flashes);
    }
    std::cout << flashes << std::endl;
}

void part2()
{
    int flashes = 0;
    std::vector<std::vector<int>> octopusMap = readInput();
    bool allFlashed = false;
    int stepCount = 0;
    while(!allFlashed)
    {
        nextStep(octopusMap, flashes);
        stepCount++;
        allFlashed = checkIfAllFlashed(octopusMap);
    }
    std::cout << stepCount << std::endl;
}

int main()
{
    part1(); 
    part2(); 
    return 0;
}