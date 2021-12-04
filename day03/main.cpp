#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

std::vector<std::string> readInput()
{
    std::ifstream fin("input.txt");
    std::string binNum;
    std::vector<std::string> input;
    while (fin >> binNum) input.push_back(binNum);
    fin.close();
    return input;
}

int binToDec(std::string binNum)
{
    int decNum = 0;
    for(int i = 0; i < binNum.size(); i++) if (binNum[binNum.size() - 1 - i] == '1') decNum += pow(2, i);
    return decNum;
}

char commonDigit(std::vector<std::string> binNums, int index, bool common = false)
{
    int zerosCount = 0;
    int onesCount = 0;
    for (int i = 0; i < binNums.size(); i++)
    {
        if (binNums[i][index] == '0') zerosCount++;
        else onesCount++;
    }
    if (zerosCount > onesCount) return '0';
    else return '1';
}

char uncommonDigit(std::vector<std::string> binNums, int index)
{
    int zerosCount = 0;
    int onesCount = 0;
    for (int i = 0; i < binNums.size(); i++)
    {
        if (binNums[i][index] == '0') zerosCount++;
        else onesCount++;
    }
    if (zerosCount <= onesCount) return '0';
    else return '1';
}

void part1()
{
    std::vector<std::string> input = readInput();
    std::string commonBin;
    std::string unCommonBin;
    int binSize = input[0].size();
    for (int i = 0; i < binSize; i++)
    {
        int zeroCount = 0;
        int oneCount = 0;
        for (int j = 0; j < input.size(); j++)
        {
            if (input[j][i] == '0')
                zeroCount++;
            else
                oneCount++;
        }
        if (zeroCount > oneCount)
        {
            commonBin.push_back('0');
            unCommonBin.push_back('1');
        }
        else
        {
            commonBin.push_back('1');
            unCommonBin.push_back('0');
        }
    }
    std::cout << binToDec(commonBin) * binToDec(unCommonBin) << std::endl;
}

void part2()
{
    std::vector<std::string> input = readInput();
    std::vector<std::string> commonPossibilities = input;
    std::vector<std::string> uncommonPossibilities = input;

    int binSize = input[0].size();
    for (int i = 0; i < binSize; i++)
    {
        std::vector<std::string> newCommonPossibilities;
        for (int j = 0; j < commonPossibilities.size(); j++) if (commonPossibilities[j][i] == commonDigit(commonPossibilities, i)) newCommonPossibilities.push_back(commonPossibilities[j]);
        commonPossibilities = newCommonPossibilities;
        if (commonPossibilities.size() == 1) break;
    }
    for (int i = 0; i < binSize; i++)
    {
        std::vector<std::string> newUncommonPossibilities;
        for (int j = 0; j < uncommonPossibilities.size(); j++) if (uncommonPossibilities[j][i] == uncommonDigit(uncommonPossibilities, i)) newUncommonPossibilities.push_back(uncommonPossibilities[j]);
        uncommonPossibilities = newUncommonPossibilities;
        if (uncommonPossibilities.size() == 1) break;
    }

    std::cout << binToDec(commonPossibilities[0]) * binToDec(uncommonPossibilities[0]) << std::endl;
}

int main()
{
    part1(); 
    part2(); 
    return 0;
}