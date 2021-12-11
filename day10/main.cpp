#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <map>

void part1()
{
    std::map<char, char> closingCharacter;
    closingCharacter['{'] = '}';
    closingCharacter['('] = ')';
    closingCharacter['<'] = '>';
    closingCharacter['['] = ']';
    std::map<char, int> errorScore;
    errorScore['}'] = 1197;
    errorScore[')'] = 3;
    errorScore['>'] = 25137;
    errorScore[']'] = 57;
    int totalErrorScore = 0;

    std::ifstream fin("input.txt");
    std::string line;
    while(std::getline(fin, line))
    {
        std::stack<char> stacky;
        for(int i = 0; i < line.size(); i++)
        {
            if(line[i] == '[' || line[i] == '<' || line[i] == '(' || line[i] == '{')
            {
                stacky.push(line[i]);
            }
            else if(line[i] == closingCharacter[stacky.top()])
            {
                stacky.pop();
            }
            else if(line[i] != closingCharacter[stacky.top()])
            {
                totalErrorScore += errorScore[line[i]];
                break;
            }
        }
    }

    std::cout << totalErrorScore << std::endl;
    fin.close();
}

double correctionSequenceScore(std::queue<char> correctionQueue)
{
    std::map<char, int> correctionScore;
    correctionScore['}'] = 3;
    correctionScore[')'] = 1;
    correctionScore['>'] = 4;
    correctionScore[']'] = 2;
    double score = 0;
    while(!correctionQueue.empty())
    {
        score *= 5;
        score += correctionScore[correctionQueue.front()];
        correctionQueue.pop();
    }
    return score;
}

void part2()
{
    std::map<char, char> closingCharacter;
    closingCharacter['{'] = '}';
    closingCharacter['('] = ')';
    closingCharacter['<'] = '>';
    closingCharacter['['] = ']';
    std::vector<double> correctionScores;
    std::ifstream fin("input.txt");
    std::string line;
    while(fin >> line)
    {
        std::stack<char> stacky;
        bool error = false;
        for(int i = 0; i < line.size(); i++)
        {
            if(line[i] == '[' || line[i] == '<' || line[i] == '(' || line[i] == '{')
            {
                stacky.push(line[i]);
            }
            else if(line[i] == closingCharacter[stacky.top()])
            {
                stacky.pop();
            }
            else if(line[i] != closingCharacter[stacky.top()])
            {
                error = true;
                break;
            }
        }
        if(!error)
        {
            std::queue<char> correctionQueue;
            while(!stacky.empty())
            {
                correctionQueue.push(closingCharacter[stacky.top()]);
                stacky.pop();
            }
            correctionScores.push_back(correctionSequenceScore(correctionQueue));
        }
    }

    for(int i = 0; i < correctionScores.size(); i++)
    {
        for(int j = 0; j < correctionScores.size() - 1; j++)
        {
            if (correctionScores[j] > correctionScores[j+1])
            {
                double tmp = correctionScores[j];
                correctionScores[j] = correctionScores[j+1];
                correctionScores[j+1] = tmp;
            }
        }
    }

    std::cout << std::fixed << std::setprecision(0) << correctionScores[correctionScores.size()/2] << std::endl;

    fin.close();
}

int main()
{
    part1(); 
    part2(); 
    return 0;
}