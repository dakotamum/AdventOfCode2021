#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <functional>
#include <map>
typedef std::pair<int, int> coord;
typedef std::pair<int, coord> pqEntry;

std::vector<std::vector<int>> readInput()
{
    std::vector<std::vector<int>> cave;
    std::string line;
    std::ifstream fin("input.txt");
    while(fin >> line)
    {
        std::vector<int> caveline;
        for(int i = 0; i < line.size(); i++) caveline.push_back(line[i] - '0');
        cave.push_back(caveline);
    }
    fin.close();
    return cave;
}

void part1()
{
    std::vector<std::vector<int>> cave = readInput();
    std::map<coord, bool> alreadyVisited;
    std::priority_queue<pqEntry, std::vector<pqEntry>, std::greater<pqEntry>> pq;
    auto endOfCave = coord({cave.size() - 1, cave[0].size() - 1});
    int sumOfShortestPath = 0;
    pq.push({0, {0, 0}});

    while(!pq.empty())
    {
        auto currCoord = pq.top();
        pq.pop();
        int currI = currCoord.second.first;
        int currJ = currCoord.second.second;
        int value = currCoord.first;
        if(!alreadyVisited[currCoord.second])
        {
            alreadyVisited[currCoord.second] = true;
            if(currI + 1 < cave.size()    && !alreadyVisited[{currI + 1, currJ}])
            {
                pq.push({value + cave[currI + 1][currJ], {currI + 1, currJ}});
                if(coord({currI + 1, currJ}) == endOfCave)
                {
                    sumOfShortestPath = value + cave[currI + 1][currJ];
                    break;
                }
            }
            if(currI - 1 >= 0             && !alreadyVisited[{currI - 1, currJ}])
            {
                pq.push({value + cave[currI - 1][currJ], {currI - 1, currJ}});
                if(coord({currI - 1, currJ}) == endOfCave)
                {
                    sumOfShortestPath = value + cave[currI - 1][currJ];
                    break;
                }
            } 
            if(currJ + 1 < cave[0].size() && !alreadyVisited[{currI, currJ + 1}])
            {
                pq.push({value + cave[currI][currJ + 1], {currI, currJ + 1}});
                if(coord({currI, currJ + 1}) == endOfCave)
                {
                    sumOfShortestPath = value + cave[currI][currJ + 1];
                    break;
                }
            }
            if(currJ - 1 >= 0             && !alreadyVisited[{currI, currJ - 1}])
            {
                pq.push({value + cave[currI][currJ - 1], {currI, currJ - 1}});
                if(coord({currI, currJ - 1}) == endOfCave)
                {
                    sumOfShortestPath = value + cave[currI][currJ - 1];
                    break;
                }
            }
        }
    }
    std::cout << sumOfShortestPath << std::endl;
}

int getValue(std::vector<std::vector<int>> cave, int i, int j)
{
    int cavewidth  = cave[0].size();
    int cavelength = cave.size();
    return (cave[i%cavelength][j%cavewidth] + ((i - (i%cavelength))/cavelength) + ((j - (j%cavewidth))/cavewidth) - 1) % 9 + 1;
}

void part2()
{
    std::vector<std::vector<int>> cave = readInput();
    std::map<coord, bool> alreadyVisited;
    std::priority_queue<pqEntry, std::vector<pqEntry>, std::greater<pqEntry>> pq;
    auto endOfCave = coord({5*cave.size() - 1, 5*cave[0].size() - 1});
    int sumOfShortestPath = 0;
    pq.push({0, {0, 0}});

    while(!pq.empty())
    {
        auto currCoord = pq.top();
        pq.pop();
        int currI = currCoord.second.first;
        int currJ = currCoord.second.second;
        int value = currCoord.first;
        if(!alreadyVisited[currCoord.second])
        {
            alreadyVisited[currCoord.second] = true;
            if(currI + 1 < 5*cave.size()    && !alreadyVisited[{currI + 1, currJ}])
            {
                pq.push({value + getValue(cave, currI+1, currJ), {currI + 1, currJ}});
                if(coord({currI + 1, currJ}) == endOfCave)
                {
                    sumOfShortestPath = value + getValue(cave, currI+1, currJ);
                    break;
                }
            }
            if(currI - 1 >= 0             && !alreadyVisited[{currI - 1, currJ}])
            {
                pq.push({value + getValue(cave, currI-1, currJ), {currI - 1, currJ}});
                if(coord({currI - 1, currJ}) == endOfCave)
                {
                    sumOfShortestPath = value + getValue(cave, currI-1, currJ);
                    break;
                }
            } 
            if(currJ + 1 < 5*cave[0].size() && !alreadyVisited[{currI, currJ + 1}])
            {
                pq.push({value + getValue(cave, currI, currJ+1), {currI, currJ + 1}});
                if(coord({currI, currJ + 1}) == endOfCave)
                {
                    sumOfShortestPath = value + getValue(cave, currI, currJ+1);
                    break;
                }
            }
            if(currJ - 1 >= 0             && !alreadyVisited[{currI, currJ - 1}])
            {
                pq.push({value + getValue(cave, currI, currJ-1), {currI, currJ - 1}});
                if(coord({currI, currJ - 1}) == endOfCave)
                {
                    sumOfShortestPath = value + getValue(cave, currI, currJ-1);
                    break;
                }
            }
        }
    }
    std::cout << sumOfShortestPath << std::endl;
}

int main()
{
    part1(); 
    part2(); 
    return 0;
}