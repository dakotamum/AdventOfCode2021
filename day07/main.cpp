#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>

std::vector<int> readInput()
{
    std::vector<int> input;
    std::ifstream fin("input.txt");
    std::string stringNum;
    while(std::getline(fin, stringNum, ','))
    {
        input.push_back(std::stoi(stringNum));
    }
    fin.close();
    return input;
}

void part1()
{
    std::vector<int> crabPositions = readInput();

    int largestPosition = 0;
    for(int i = 0; i < crabPositions.size(); i++)
    {
        if(crabPositions[i] >= largestPosition)
        {
            largestPosition = crabPositions[i];
        }
    }
    double smallestFuelConsumption = 999999999;
    int smallestFuelConsumptionNumber = 0;
    for(int i = 0; i <= largestPosition; i++)
    {
        double totalFuelConsumption = 0;
        for(int j = 0; j < crabPositions.size(); j++)
        {
            totalFuelConsumption += abs(crabPositions[j] - i);
        }
        if (totalFuelConsumption < smallestFuelConsumption)
        {
            smallestFuelConsumption = totalFuelConsumption;
            smallestFuelConsumptionNumber = i;
        }
    }
    std::cout << std::fixed << std::setprecision(0) << smallestFuelConsumption << std::endl;
}

void part2()
{
    std::vector<int> crabPositions = readInput();

    int largestPosition = 0;
    for(int i = 0; i < crabPositions.size(); i++)
    {
        if(crabPositions[i] >= largestPosition)
        {
            largestPosition = crabPositions[i];
        }
    }
    double smallestFuelConsumption = 999999999;
    int smallestFuelConsumptionNumber = 0;
    for(int i = 0; i <= largestPosition; i++)
    {
        double totalFuelConsumption = 0;
        for(int j = 0; j < crabPositions.size(); j++)
        {
            totalFuelConsumption += (abs(crabPositions[j] - i))*(abs(crabPositions[j] - i) + 1)/2;
        }
        if (totalFuelConsumption < smallestFuelConsumption)
        {
            smallestFuelConsumption = totalFuelConsumption;
            smallestFuelConsumptionNumber = i;
        }
    }
    std::cout << std::fixed << std::setprecision(0) << smallestFuelConsumption << std::endl;
}

int main()
{
    part1(); 
    part2();
    return 0;
}