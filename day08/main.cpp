#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

bool existsIn(std::string number, char letter)
{
    bool found = false;
    for(int i = 0; i < number.size(); i++) if(number[i] == letter) found = true;
    return found;
}

std::map<char, char> getSegmentMap(std::string patterns)
{
    std::string twoSeg, threeSeg, fourSeg, sevenSeg;
    std::vector<std::string> fiveSegs;
    std::vector<std::string> sixSegs;
    std::istringstream ss(patterns);
    std::string aNumber;
    while(ss >> aNumber)
    {
        switch(aNumber.size())
        {
            case 2:
                twoSeg = aNumber;
                break;
            case 3:
                threeSeg = aNumber;
                break;
            case 4:
                fourSeg = aNumber;
                break;
            case 5:
                fiveSegs.push_back(aNumber);
                break;
            case 6:
                sixSegs.push_back(aNumber);
                break;
            case 7:
                sevenSeg = aNumber;
                break;
            default:
                break;
        }
    }

    char segA, segB, segC, segD, segE, segF, segG;
    for(int i = 0; i < threeSeg.size(); i++) if(!existsIn(twoSeg, threeSeg[i])) segA = threeSeg[i];

    if(existsIn(sixSegs[0], twoSeg[0]) && existsIn(sixSegs[1], twoSeg[0]) && existsIn(sixSegs[2], twoSeg[0]))
    {
        segF = twoSeg[0];
        segC = twoSeg[1];
    }
    else
    {
        segF = twoSeg[1];
        segC = twoSeg[0];
    }

    std::string bOrdPossibilities;
    for(int i = 0; i < fourSeg.size(); i++) if(!existsIn(twoSeg, fourSeg[i])) bOrdPossibilities.push_back(fourSeg[i]);
    if(existsIn(sixSegs[0], bOrdPossibilities[0]) && existsIn(sixSegs[1], bOrdPossibilities[0]) && existsIn(sixSegs[2], bOrdPossibilities[0]))
    {
        segB = bOrdPossibilities[0];
        segD = bOrdPossibilities[1];
    }
    else
    {
        segB = bOrdPossibilities[1];
        segD = bOrdPossibilities[0];
    }

    std::string eOrGPossibilities = "abcdefg";
    eOrGPossibilities.erase(std::remove(eOrGPossibilities.begin(), eOrGPossibilities.end(), segA), eOrGPossibilities.end());
    eOrGPossibilities.erase(std::remove(eOrGPossibilities.begin(), eOrGPossibilities.end(), segB), eOrGPossibilities.end());
    eOrGPossibilities.erase(std::remove(eOrGPossibilities.begin(), eOrGPossibilities.end(), segC), eOrGPossibilities.end());
    eOrGPossibilities.erase(std::remove(eOrGPossibilities.begin(), eOrGPossibilities.end(), segD), eOrGPossibilities.end());
    eOrGPossibilities.erase(std::remove(eOrGPossibilities.begin(), eOrGPossibilities.end(), segF), eOrGPossibilities.end());

    if(existsIn(sixSegs[0], eOrGPossibilities[0]) && existsIn(sixSegs[1], eOrGPossibilities[0]) && existsIn(sixSegs[2], eOrGPossibilities[0]))
    {
        segE = eOrGPossibilities[1];
        segG = eOrGPossibilities[0];
    }
    else
    {
        segE = eOrGPossibilities[0];
        segG = eOrGPossibilities[1];
    }

    std::map<char, char> segmentMap;

    segmentMap['a'] = segA;
    segmentMap['b'] = segB;
    segmentMap['c'] = segC;
    segmentMap['d'] = segD;
    segmentMap['e'] = segE;
    segmentMap['f'] = segF;
    segmentMap['g'] = segG;

    return segmentMap;
}

int getOutputInt(std::map<char, char> segmentMap, std::string number)
{
    int numberInt = 0;
    switch(number.size())
    {
        case 2:
            numberInt = 1;
            break;
        case 3:
            numberInt = 7;
            break;
        case 4:
            numberInt = 4;
            break;
        case 5:
            if(!existsIn(number, segmentMap['c'])) numberInt = 5;
            else if(existsIn(number, segmentMap['f'])) numberInt = 3;
            else numberInt = 2;
            break;
        case 6:
            if(!existsIn(number, segmentMap['d'])) numberInt = 0;
            else if(!existsIn(number, segmentMap['e'])) numberInt = 9;
            else numberInt = 6;
            break;
        case 7:
            numberInt = 8;
            break;
        default:
            break;
    } 
    return numberInt;
}

void part1()
{
    std::ifstream fin("input.txt");
    std::string pattern;
    int simpleNumbersCount = 0;
    while(std::getline(fin, pattern, '|'))
    {
        std::string output;
        std::getline(fin, output);
        std::stringstream ss(output);
        std::string outputNumber;
        while(ss >> outputNumber) if(outputNumber.size() == 2 || outputNumber.size() == 3 || outputNumber.size() == 4 || outputNumber.size() == 7) simpleNumbersCount++;
    }
    fin.close();
    std::cout << simpleNumbersCount << std::endl;
}

void part2()
{
    std::ifstream fin("input.txt");
    std::string pattern;
    int totalOutputsCount = 0;
    while(std::getline(fin, pattern, '|'))
    {
        std::string output;
        std::getline(fin, output);
        std::stringstream ss(output);
        std::string outputNumber;
        std::map<char, char> segmentMap = getSegmentMap(pattern);
        int multiplier = 1000;
        while(ss >> outputNumber)
        {
            totalOutputsCount += (getOutputInt(segmentMap, outputNumber) * multiplier);
            multiplier /= 10;
        }
    }
    fin.close();
    std::cout << totalOutputsCount << std::endl;
}

int main()
{
    part1(); 
    part2(); 
    return 0;
}