#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <utility>

void readInput(std::map<std::string, long long int>& currentMap , std::map<std::string, std::string>& rulesMap)
{
    std::ifstream fin("input.txt");
    std::string newString;
    fin >> newString;
    for(int i = 0; i < newString.size() - 1; i++)
    {
        std::string newPair;
        newPair.push_back(newString[i]);
        newPair.push_back(newString[i+1]);
        currentMap[newPair]+=1;
    }
    while(fin >> newString)
    {
        std::string twoLetters = newString;
        fin >> newString;
        fin >> newString;
        std::string toInsert = newString;
        rulesMap[twoLetters] = toInsert;
    }
    fin.close();
}

long long int getHighAndLowCountDifference(std::map<std::string, long long int> aMap)
{
    std::map<char, long long int> countMap;
    for(const auto& iter : aMap)
    {
        countMap[iter.first[0]] += iter.second;
        countMap[iter.first[1]] += iter.second;
    }
    long long int highCount = 0;
    long long int lowCount = 100000000000000;
    for(auto& iter : countMap)
    {
        if(iter.second % 2 != 0) iter.second+=1;
        iter.second /= 2;
        if(iter.second > highCount) highCount = iter.second;
        if(iter.second < lowCount) lowCount = iter.second;
    }
    return highCount - lowCount;
}

void part1()
{
    std::map<std::string, long long int> currentMap;
    std::map<std::string, std::string> rulesMap;
    readInput(currentMap, rulesMap);
    int numSteps = 10;

    for(int i = 0; i < numSteps; i++)
    {
        std::map<std::string, long long int> newMap = currentMap;
        for(const auto& iter : currentMap)
        {
            if(rulesMap[iter.first] != std::string())
            {
                std::string firstSplit = iter.first;
                std::string secondSplit = iter.first;
                firstSplit[0] = rulesMap[iter.first][0];
                secondSplit[1] = rulesMap[iter.first][0];
                newMap[firstSplit] += iter.second;
                newMap[secondSplit] += iter.second;
                newMap[iter.first] -= iter.second;
            }
        }
        currentMap = newMap;
    }
    std::cout << getHighAndLowCountDifference(currentMap) << std::endl;
}

void part2()
{   
    std::map<std::string, long long int> currentMap;
    std::map<std::string, std::string> rulesMap;
    readInput(currentMap, rulesMap);
    int numSteps = 40;

    for(int i = 0; i < numSteps; i++)
    {
        std::map<std::string, long long int> newMap = currentMap;
        for(const auto& iter : currentMap)
        {
            if(rulesMap[iter.first] != std::string())
            {
                std::string firstSplit = iter.first;
                std::string secondSplit = iter.first;
                firstSplit[0] = rulesMap[iter.first][0];
                secondSplit[1] = rulesMap[iter.first][0];
                newMap[firstSplit] += iter.second;
                newMap[secondSplit] += iter.second;
                newMap[iter.first] -= iter.second;
            }
        }
        currentMap = newMap;
    }
    std::cout << getHighAndLowCountDifference(currentMap) << std::endl;
}

int main()
{
    part1(); 
    part2(); 
    return 0;
}