#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

std::map<std::string, std::vector<std::string>> readInput()
{
    std::map<std::string, std::vector<std::string>> mappy;

    std::ifstream fin("input.txt");
    std::string line;
    while(std::getline(fin, line))
    {
        std::string first, second;
        int dashIndex = 0;
        for(int i = 0; i < line.size(); i++)
        {
            if (line[i] == '-')
            {
                dashIndex = i;
                break;
            }
            else first.push_back(line[i]);
        }
        for(int i = dashIndex + 1; i < line.size(); i++) second.push_back(line[i]);
        mappy[first].push_back(second);
        mappy[second].push_back(first);
    }
    return mappy;
}

bool isLowerCase(std::string caveName)
{
    return (int(caveName[0]) > 90);
}

bool isIn(std::vector<std::string> aVector, std::string aString)
{
    bool found = false;
    for(int i = 0; i < aVector.size(); i++)
    {
        if(aString == aVector[i])
        {
            found  = true;
            break;
        }
    }
    return found;
}

void getPossiblePathsOneSmallCave(std::vector<std::vector<std::string>>& allPossibleCombos, std::map<std::string, std::vector<std::string>> mappy, std::string currentCave, std::vector<std::string> currentPossibilities = {}, std::vector<std::string> lowerCaseAlreadyVisited = {})
{
    if (currentCave == "end")
    {
        currentPossibilities.push_back(currentCave);
        allPossibleCombos.push_back(currentPossibilities);
        return;
    }
    currentPossibilities.push_back(currentCave);
    if(isLowerCase(currentCave) && currentCave != "start" && currentCave != "end")
    {
        lowerCaseAlreadyVisited.push_back(currentCave);
    }
    for(int i = 0; i < mappy[currentCave].size(); i++)
    {
        if(!isIn(lowerCaseAlreadyVisited, mappy[currentCave][i]) && mappy[currentCave][i] != "start")
        {
            getPossiblePathsOneSmallCave(allPossibleCombos, mappy, mappy[currentCave][i], currentPossibilities, lowerCaseAlreadyVisited);
        }
    }
}

void getPossiblePathsTwoSmallCave(std::vector<std::vector<std::string>>& allPossibleCombos, std::map<std::string, std::vector<std::string>> mappy, std::string currentCave, std::vector<std::string> currentPossibilities = {}, std::vector<std::string> lowerCaseAlreadyVisited = {}, bool visitedSmallCaveTwice = false)
{
    if (currentCave == "end")
    {
        currentPossibilities.push_back(currentCave);
        allPossibleCombos.push_back(currentPossibilities);
        return;
    }
    currentPossibilities.push_back(currentCave);
    if(isLowerCase(currentCave) && currentCave != "start" && currentCave != "end" && !isIn(lowerCaseAlreadyVisited, currentCave))
    {
        lowerCaseAlreadyVisited.push_back(currentCave);
    }
    for(int i = 0; i < mappy[currentCave].size(); i++)
    {
        if((!isIn(lowerCaseAlreadyVisited, mappy[currentCave][i]) || !visitedSmallCaveTwice) && mappy[currentCave][i] != "start")
        {
            if(isIn(lowerCaseAlreadyVisited, mappy[currentCave][i]))
            {
                getPossiblePathsTwoSmallCave(allPossibleCombos, mappy, mappy[currentCave][i], currentPossibilities, lowerCaseAlreadyVisited, true);
            }
            else getPossiblePathsTwoSmallCave(allPossibleCombos, mappy, mappy[currentCave][i], currentPossibilities, lowerCaseAlreadyVisited, visitedSmallCaveTwice);
        }
    }
}

void part1()
{
    std::map<std::string, std::vector<std::string>> mappy = readInput();
    std::vector<std::vector<std::string>> allPossibleCombos = {};
    getPossiblePathsOneSmallCave(allPossibleCombos, mappy, "start");
    std::cout << allPossibleCombos.size() << std::endl;
}

void part2()
{
    std::map<std::string, std::vector<std::string>> mappy = readInput();
    std::vector<std::vector<std::string>> allPossibleCombos = {};
    getPossiblePathsTwoSmallCave(allPossibleCombos, mappy, "start");
    std::cout << allPossibleCombos.size() << std::endl;

}

int main()
{
    part1(); 
    part2(); 
    return 0;
}