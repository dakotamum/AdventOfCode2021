#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <utility>

void readInput(std::map<std::pair<int, int>, bool>& paper, std::vector<std::pair<char, int>>& foldingDirections)
{
    std::ifstream fin("input.txt");
    std::string line;
    while(std::getline(fin, line))
    {
        if(line == std::string()) break;
        std::istringstream ss(line);
        std::string x, y;
        std::getline(ss, x, ',');
        std::getline(ss, y, ',');
        paper[{std::stoi(x), std::stoi(y)}] = true;
    }
    std::string tmp;
    while(fin >> tmp)
    {
        fin >> tmp;
        fin >> tmp;
        char coordDirection = tmp.front();
        tmp.erase(tmp.begin());
        tmp.erase(tmp.begin());
        int number = std::stoi(tmp); 
        foldingDirections.push_back({coordDirection, number});
    }
    fin.close();
}

void part1()
{
    std::map<std::pair<int, int>, bool> paper;
    std::vector<std::pair<char, int>> foldingDirections;
    readInput(paper, foldingDirections);
    std::pair<char, int> firstDirection = foldingDirections[0];

    std::map<std::pair<int, int>, bool> foldedPaper;
    
    if(firstDirection.first == 'x')
    {
       for(auto const& iter : paper)
       {
           if(iter.first.first > firstDirection.second) foldedPaper[{2*(firstDirection.second) - iter.first.first, iter.first.second}] = true;
           else foldedPaper[{iter.first.first, iter.first.second}] = true;

       } 
    }
    else if(firstDirection.first == 'y')
    {
       for(auto const& iter : paper)
       {
           if(iter.first.second > firstDirection.second) foldedPaper[{iter.first.first, 2*(firstDirection.second) - iter.first.second}] = true;
           else foldedPaper[{iter.first.first, iter.first.second}] = true;
       } 
    }
    std::cout << foldedPaper.size();
}

void part2()
{
    std::map<std::pair<int, int>, bool> paper;
    std::vector<std::pair<char, int>> foldingDirections;
    readInput(paper, foldingDirections);
    
    for(int i = 0; i < foldingDirections.size(); i++)
    {
        std::map<std::pair<int, int>, bool> foldedPaper;
        if(foldingDirections[i].first == 'x')
        {
            for(auto const& iter : paper)
            {
                if(iter.first.first > foldingDirections[i].second) foldedPaper[{2*(foldingDirections[i].second) - iter.first.first, iter.first.second}] = true;
                else foldedPaper[{iter.first.first, iter.first.second}] = true;

            } 
        }
        else if(foldingDirections[i].first == 'y')
        {
            for(auto const& iter : paper)
            {
                if(iter.first.second > foldingDirections[i].second) foldedPaper[{iter.first.first, 2*(foldingDirections[i].second) - iter.first.second}] = true;
                else foldedPaper[{iter.first.first, iter.first.second}] = true;
            } 
        }
        paper.clear();
        paper = foldedPaper;
    }
    std::cout << paper.size() << std::endl;;

    int bigX = 0;
    int bigY = 0;
    for(const auto& iter : paper)
    {
        if(iter.first.first > bigX) bigX = iter.first.first;
        if(iter.first.second > bigY) bigY = iter.first.second;
    }
    std::vector<std::vector<char>> answer;
    for(int i = 0; i < bigY+1; i++)
    {
        std::vector<char> newRow;
        for(int j = 0; j < bigX+1; j++) newRow.push_back(' ');
        answer.push_back(newRow);
    }
    for(auto const& iter : paper)
    {
        answer[iter.first.second][iter.first.first] = '@';
    }
    std::ofstream fout("answer.txt");
    for(int i = 0; i < answer.size(); i++)
    {
        for(int j = 0; j < answer[0].size(); j++) fout << answer[i][j];
        fout << std::endl;
    }
    fout.close();
}

int main()
{
    part1(); 
    part2(); 
    return 0;
}