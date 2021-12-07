#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>

std::map<int, double> readInput()
{
    std::map<int, double> inputMap;
    std::ifstream fin("input.txt");
    std::string stringNum;
    while(std::getline(fin, stringNum, ',')) inputMap[std::stoi(stringNum)]++;
    fin.close();
    return inputMap;
}

double getLanternFish(int iterations)
{
    std::map<int, double> mappy = readInput();
    double sum = 0;
    for(int i = 0; i < iterations; i++)
    {
        std::map<int, double> newMappy;
        for(int j = 8; j > 0; j--)
        {
            newMappy[j-1] = mappy[j];
        }
        newMappy[6] += mappy[0];
        newMappy[8] = mappy[0];
        mappy = newMappy;
    }
    for(const auto& it : mappy) sum += it.second;
    return sum;
}

void part1()
{
    std::cout << std::fixed << std::setprecision(0) << getLanternFish(80) << std::endl;
}

void part2()
{
    std::cout << std::fixed << std::setprecision(0) << getLanternFish(256) << std::endl;
}

int main()
{
    part1(); 
    part2(); 
    return 0;
}