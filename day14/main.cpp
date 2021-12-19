#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <utility>

void readInput(std::string& letters, std::map<std::string, std::string>& mappy)
{
    std::ifstream fin("input.txt");
    std::string newString;
    fin >> newString;
    letters = newString; 
    while(fin >> newString)
    {
        std::string twoLetters = newString;
        fin >> newString;
        fin >> newString;
        std::string toInsert = newString;
        mappy[twoLetters] = toInsert;
    }
    fin.close();
}

int mostCommonOccurrence(std::string letters)
{
    std::map<char, int> mappy;
    for(int i = 0; i < letters.size(); i++) mappy[letters[i]]++;
    int highCount = 0;
    for(const auto& iter: mappy) if (iter.second > highCount) highCount = iter.second;
    return highCount;
}

int leastCommonOccurrence(std::string letters)
{
    std::map<char, int> mappy;
    for(int i = 0; i < letters.size(); i++) mappy[letters[i]]++;
    int lowCount = 10000000;
    for(const auto& iter: mappy) if (iter.second < lowCount) lowCount = iter.second;
    return lowCount;
}

void part1()
{
    std::string letters;
    std::map<std::string, std::string> mappy;
    readInput(letters, mappy);

    int numSteps = 10;

    for(int i = 0; i < numSteps; i++)
    {
        int insertionCount = 0;
        std::vector<std::pair<char, int>> insertions;
        for (int j = 0; j < letters.size() - 1; j++)
        {
            std::string letterPair; letterPair.push_back(letters[j]); letterPair.push_back(letters[j+1]);
            if(mappy[letterPair] != std::string())
            {
                insertions.push_back({mappy[letterPair][0], j + 1 + insertionCount});
                insertionCount++;
            }
        }
        for(int j = 0; j < insertions.size(); j++)
        {
            std::string toInsert;
            toInsert.push_back(insertions[j].first);
            letters.insert(insertions[j].second, toInsert);
        }
    }
    std::cout << mostCommonOccurrence(letters) - leastCommonOccurrence(letters) << std::endl;
}

void part2()
{
    std::string letters;
    std::map<std::string, std::string> mappy;
    readInput(letters, mappy);

    int numSteps = 10;

    for(int i = 0; i < numSteps; i++)
    {
        int insertionCount = 0;
        std::vector<std::pair<char, int>> insertions;
        for (int j = 0; j < letters.size() - 1; j++)
        {
            std::string letterPair; letterPair.push_back(letters[j]); letterPair.push_back(letters[j+1]);
            if(mappy[letterPair] != std::string())
            {
                insertions.push_back({mappy[letterPair][0], j + 1 + insertionCount});
                insertionCount++;
            }
        }
        for(int j = 0; j < insertions.size(); j++)
        {
            std::string toInsert;
            toInsert.push_back(insertions[j].first);
            letters.insert(insertions[j].second, toInsert);
        }
    }
    std::cout << mostCommonOccurrence(letters) - leastCommonOccurrence(letters) << std::endl;
}

int main()
{
    part1(); 
    part2(); 
    return 0;
}