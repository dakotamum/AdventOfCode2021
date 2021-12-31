#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <stdio.h>

std::string getBinFromHex()
{
    std::string binNumber, input;
    std::ifstream fin("input.txt");
    fin >> input;
    for(int i = 0; i < input.size(); i++)
    {
        std::string aBinNum;
        int currentNum = 0;
        if(input[i] - '0' > 9) currentNum = input[i] - '0' - 7;
        else currentNum = input[i] - '0';
        for(int j = 0; j < 4; j++)
        {
            aBinNum.insert(aBinNum.begin(), currentNum % 2 == 0 ? '0' : '1');
            currentNum /= 2;
        }
        binNumber += aBinNum;
    }
    fin.close();
    return binNumber;
}

long long int getDecFromBin(std::string bin)
{
    long long int dec = 0;
    int power = 0;
    for(int i = bin.size() - 1; i >= 0; i--)
    {
        if(bin[i] == '1') dec += pow(2, power);
        power++;
    }
    return dec;
}

void parsePacket(std::string bin, int& currentIdx, int& subBitCount, int& subPacketCount, int& versionSum)
{
    int initialIdx = currentIdx;
    int packetVersion = getDecFromBin(bin.substr(currentIdx, 3));
    versionSum += packetVersion;
    int packetType = getDecFromBin(bin.substr(currentIdx + 3, 3));

    if(packetType == 4)
    {
        currentIdx += 6;
        bool stop = false;
        std::string binRep = std::string();
        while(!stop)
        {
            if(bin[currentIdx] == '0') stop = true;
            binRep += bin.substr(currentIdx + 1, 4);
            currentIdx += 5;
        }
    }
    else
    {
        char lengthTypeID = bin[currentIdx + 6];
        if (lengthTypeID == '0')
        {
            int numSubPacketBits = getDecFromBin(bin.substr(currentIdx + 7, 15));
            currentIdx += 22;
            int subBits = 0, subPkts = 0;
            while(subBits < numSubPacketBits)
            {
                parsePacket(bin, currentIdx, subBits, subPkts, versionSum);
            }
        }
        else if (lengthTypeID == '1')
        {
            int numSubPackets = getDecFromBin(bin.substr(currentIdx + 7, 11));
            currentIdx += 18;
            int subBits = 0, subPkts = 0;
            while(subPkts < numSubPackets)
            {
                parsePacket(bin, currentIdx, subBits, subPkts, versionSum);
            }
        }
    }
    subBitCount += (currentIdx - initialIdx);
    subPacketCount ++;
}

void part1()
{
    int currentIdx = 0, subBitCount = 0, subPacketCount = 0, versionSum = 0;
    parsePacket(getBinFromHex(), currentIdx, subBitCount, subPacketCount, versionSum);
    std::cout << "version sum: " << versionSum << std::endl;
}

long long int sum(std::vector<long long int> packetValues)
{
    long long int sum = 0;
    for(int i = 0; i < packetValues.size(); i++) sum += packetValues[i];
    return sum;
}

long long int product(std::vector<long long int> packetValues)
{
    long long int product = 1;
    for(int i = 0; i < packetValues.size(); i++) product = packetValues[i] * product;
    return product;
}

long long int min(std::vector<long long int> packetValues)
{
    long long int min = packetValues[0];
    for(int i = 0; i < packetValues.size(); i++)
    {
        if(packetValues[i] < min) min = packetValues[i];
    }
    return min;
}

long long int max(std::vector<long long int> packetValues)
{
    long long int max = packetValues[0];
    for(int i = 0; i < packetValues.size(); i++)
    {
        if(packetValues[i] > max) max = packetValues[i];
    }
    return max;
}

long long int greaterThan(std::vector<long long int> packetValues)
{
    if(packetValues[0] > packetValues[1]) return 1;
    else return 0;
}

long long int lessThan(std::vector<long long int> packetValues)
{
    if(packetValues[0] < packetValues[1]) return 1;
    else return 0;
}

long long int equalThan(std::vector<long long int> packetValues)
{
    if(packetValues[0] == packetValues[1]) return 1;
    else return 0;
}

long long int parsePacket(std::string bin, int& currentIdx, int& subBitCount, int& subPacketCount)
{
    int initialIdx = currentIdx;
    int packetVersion = getDecFromBin(bin.substr(currentIdx, 3));
    int packetType = getDecFromBin(bin.substr(currentIdx + 3, 3));
    long long int numToReturn = 0;

    if(packetType == 4)
    {
        currentIdx += 6;
        bool stop = false;
        std::string binRep = std::string();
        while(!stop)
        {
            if(bin[currentIdx] == '0') stop = true;
            binRep += bin.substr(currentIdx + 1, 4);
            currentIdx += 5;
        }
        numToReturn = getDecFromBin(binRep);
    }
    else
    {
        char lengthTypeID = bin[currentIdx + 6];
        std::vector<long long int> subPacketValues;
        if (lengthTypeID == '0')
        {
            int numSubPacketBits = getDecFromBin(bin.substr(currentIdx + 7, 15));
            currentIdx += 22;
            int subBits = 0, subPkts = 0;
            while(subBits < numSubPacketBits)
            {
                subPacketValues.push_back(parsePacket(bin, currentIdx, subBits, subPkts));
            }
        }
        else if (lengthTypeID == '1')
        {
            int numSubPackets = getDecFromBin(bin.substr(currentIdx + 7, 11));
            currentIdx += 18;
            int subBits = 0, subPkts = 0;
            while(subPkts < numSubPackets)
            {
                subPacketValues.push_back(parsePacket(bin, currentIdx, subBits, subPkts));
            }
        }
        switch(packetType)
        {
            case 0:
                numToReturn = sum(subPacketValues);
                break;
            case 1:
                numToReturn = product(subPacketValues);
                break;
            case 2:
                numToReturn = min(subPacketValues);
                break;
            case 3:
                numToReturn = max(subPacketValues);
                break;
            case 5:
                numToReturn = greaterThan(subPacketValues);
                break;
            case 6:
                numToReturn = lessThan(subPacketValues);
                break;
            case 7:
                numToReturn = equalThan(subPacketValues);
                break;
            default:
                break;
        }
    }
    subBitCount += (currentIdx - initialIdx);
    subPacketCount ++;
    return numToReturn;
}

void part2()
{
    int currentIdx = 0, subBitCount = 0, subPacketCount = 0;
    long long int totalPacketValue = 0;
    totalPacketValue = parsePacket(getBinFromHex(), currentIdx, subBitCount, subPacketCount);
    std::cout << "total packet value: " << totalPacketValue << std::endl;
}

int main()
{
    part1(); 
    part2(); 
    return 0;
}
