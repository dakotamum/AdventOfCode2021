#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>

std::pair<std::pair<int, int>, std::pair<int, int>> readInput()
{
    std::pair<std::pair<int, int>, std::pair<int, int>> bounds;
    std::ifstream fin("input.txt");

    std::string tmp;
    fin >> tmp; fin >> tmp;
    std::getline(fin, tmp, '=');
    std::getline(fin, tmp, '.');
    bounds.first.first = std::stoi(tmp);
    std::getline(fin, tmp, '.');
    std::getline(fin, tmp, ',');
    bounds.first.second = std::stoi(tmp);
    std::getline(fin, tmp, '=');
    std::getline(fin, tmp, '.');
    bounds.second.first = std::stoi(tmp);
    std::getline(fin, tmp, '.');
    std::getline(fin, tmp, '.');
    bounds.second.second = std::stoi(tmp);
    fin.close();
    return bounds;
}

bool crossedLowerY(int ypos, int lowery)
{
    if (ypos < lowery)
    {
        std::cout << "overshot in y direction" << std::endl;
        return true;
    }
    else return false;
}

bool crossedUpperX(int xpos, int upperx)
{
    if (xpos > upperx)
    {
        std::cout << "overshot in x direction" << std::endl;
        return true;
    }
    else return false;
}

bool madeIt(int xpos, int ypos, int lowery, int uppery, int lowerx, int upperx)
{
    if(ypos >= lowery && ypos <= uppery && xpos >= lowerx && xpos <= upperx)
    {
        std::cout << "made it!" << std::endl;
        return true;
    }
    else return false;
}

bool step(int& xvel, int& yvel, int& xpos, int& ypos, int lowery, int uppery, int lowerx, int upperx)
{
    xpos += xvel;
    ypos += yvel;
    if(xvel > 0) xvel--;
    yvel--;
    return(crossedLowerY(ypos, lowery) || crossedUpperX(xpos, upperx) || madeIt(xpos, ypos, lowery, uppery, lowerx, upperx));
}

void part1()
{
    auto bounds = readInput(); 
    int lowerx = bounds.first.first, upperx = bounds.first.second;
    int lowery = bounds.second.first, uppery = bounds.second.second;
    int xpos = 0, ypos = 0;

    int xvel = 6, yvel = 3;
    while(!step(xvel, yvel, xpos, ypos, lowery, uppery, lowerx, upperx))
    {
        std::cout << "xpos: " << xpos << std::endl;
        std::cout << "ypos: " << ypos << std::endl;
        std::cout << "---------------" << std::endl;
    }
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