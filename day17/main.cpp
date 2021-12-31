#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <cmath>
typedef std::pair<std::pair<int, int>, std::pair<int, int>> bounds;

bounds readInput()
{
    bounds boundage;
    std::ifstream fin("input.txt");
    std::string tmp;
    fin >> tmp; fin >> tmp;
    std::getline(fin, tmp, '=');
    std::getline(fin, tmp, '.');
    boundage.first.first = std::stoi(tmp);
    std::getline(fin, tmp, '.');
    std::getline(fin, tmp, ',');
    boundage.first.second = std::stoi(tmp);
    std::getline(fin, tmp, '=');
    std::getline(fin, tmp, '.');
    boundage.second.first = std::stoi(tmp);
    std::getline(fin, tmp, '.');
    std::getline(fin, tmp, '.');
    boundage.second.second = std::stoi(tmp);
    fin.close();
    return boundage;
}

bool crossedBounds(int xpos, int ypos, bounds boundage)
{
    if (xpos > boundage.first.second) return true;
    else if (ypos < boundage.second.first) return true;
    else return false;
}

bool madeIt(int xpos, int ypos, bounds boundage)
{
    if(xpos >= boundage.first.first && xpos <= boundage.first.second && ypos >= boundage.second.first && ypos <= boundage.second.second) return true;
    else return false;
}

bool step(int& xvel, int& yvel, int& xpos, int& ypos, bounds boundage, int& highY, bool& score)
{
    if(yvel == 0) highY = ypos;
    xpos += xvel;
    ypos += yvel;
    if(xvel > 0) xvel--;
    yvel--;
    if(madeIt(xpos, ypos, boundage))
    {
        score = true;
        return true;
    }
    else if(crossedBounds(xpos, ypos, boundage)) return true;
    else return false;
}

int quad(int coord)
{
    double number = coord;
    double quadNum = (std::sqrt(8*number) - 1)/2;
    return static_cast<int>(std::ceil(quadNum));
}

void part1()
{
    auto bounds = readInput(); 
    int highestY = 0;

    int yMaxVel = abs(bounds.second.first);
    int xMinVel = quad(bounds.first.first); 
    int xMaxVel = bounds.first.second; 

    for(int i = xMinVel; i <= xMaxVel; i++)
    {
        for(int j = 0; j < yMaxVel; j++)
        {
            int xpos = 0, ypos = 0, xvel = i, yvel = j;
            int highY = 0;
            bool score = false;

            while(!step(xvel, yvel, xpos, ypos, bounds, highY, score)){}
            if(score && highY > highestY) highestY = highY;
        }
    }
    std::cout << "highest y position: " << highestY << std::endl;
}

void part2()
{
    auto bounds = readInput(); 
    int highestY = 0;
    int yMaxVel = abs(bounds.second.first);
    int xMinVel = quad(bounds.first.first); 
    int xMaxVel = bounds.first.second; 

    int validCount = 0;

    for(int i = xMinVel; i <= xMaxVel; i++)
    {
        for(int j = bounds.second.first; j < yMaxVel; j++)
        {
            int xpos = 0, ypos = 0, xvel = i, yvel = j;
            int highY = 0;
            bool score = false;

            while(!step(xvel, yvel, xpos, ypos, bounds, highY, score)){}
            if(score) validCount++;
        }
    }
    std::cout << "valid number of initial velocities: " << validCount << std::endl;
}

int main()
{
    part1(); 
    part2(); 
    return 0;
}