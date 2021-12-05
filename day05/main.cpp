#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

struct Line
{
    int x1, y1, x2, y2;
    Line(int x1Coord, int y1Coord, int x2Coord, int y2Coord)
    {
        x1 = x1Coord; y1 = y1Coord; x2 = x2Coord; y2 = y2Coord;
    }
};

std::vector<Line> readInput()
{
    std::vector<Line> lines;
    std::ifstream fin("input.txt");
    std::string(inputLine);
    while(getline(fin, inputLine))
    {
        std::string x1, y1, x2, y2, tmp;
        std::istringstream ss(inputLine);
        getline(ss, x1, ','); ss >> y1; ss >> tmp; getline(ss, x2, ','); ss >> y2;
        lines.push_back(Line(std::stoi(x1), std::stoi(y1), std::stoi(x2), std::stoi(y2)));
    }
    fin.close();
    return lines;
}

void part1()
{
    std::vector<Line> lines = readInput();
    std::vector<std::vector<int>> ventsMap;
    int greaterThanOneCount = 0;
    for(int i = 0; i < 1000; i++)
    {
        std::vector<int> newRow;
        for(int j = 0; j < 1000; j++) { newRow.push_back(0); }
        ventsMap.push_back(newRow);
    }
    for(int i = 0; i < lines.size(); i++)
    {
        if(lines[i].x1 == lines[i].x2)
        {
            int x = lines[i].x1;
            int lowerY, upperY;
            if(lines[i].y1 <= lines[i].y2)
            {
                lowerY = lines[i].y1;
                upperY = lines[i].y2;
            } 
            else
            {
                lowerY = lines[i].y2;
                upperY = lines[i].y1;
            }
            for(int j = lowerY; j <= upperY; j++)
            {
                ventsMap[j][x] += 1;
            }
        }
        else if(lines[i].y1 == lines[i].y2)
        {
            int y = lines[i].y1;
            int lowerX, upperX;
            if(lines[i].x1 <= lines[i].x2)
            {
                lowerX = lines[i].x1;
                upperX = lines[i].x2;
            } 
            else
            {
                lowerX = lines[i].x2;
                upperX = lines[i].x1;
            }
            for(int j = lowerX; j <= upperX; j++)
            {
                ventsMap[y][j] += 1;
            }
        }
    } 

    for(int i = 0; i < ventsMap.size(); i++)
    {
        for(int j = 0; j < ventsMap[i].size(); j++)
        {
            if(ventsMap[i][j] > 1) greaterThanOneCount++;
        }
    }
    std::cout << greaterThanOneCount << std::endl;
}

void part2()
{

}

int main()
{
    part1(); 
    part2(); 
    return 0;
}