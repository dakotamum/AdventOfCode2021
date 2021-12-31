#include <iostream>
#include <fstream>
#include <string>
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

int getDecFromBin(std::string bin)
{
    int dec = 0;
    int power = 0;
    for(int i = bin.size() - 1; i >= 0; i--)
    {
        if(bin[i] == '1') dec += pow(2, power);
        power++;
    }
    return dec;
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

void parsePacket(std::string bin)
{
    int packetVersion = getDecFromBin(bin.substr(0, 3));
    int packetType = getDecFromBin(bin.substr(3, 3));
    std::cout << packetVersion << std::endl;
    std::cout << packetType << std::endl;

    if(packetType == 4)
    {
        int currentIdx = 6;
        bool stop = false;
        std::string binRep = std::string();
        while(!stop)
        {
            std::cout << "current index: " << currentIdx << std::endl;
            if(bin[currentIdx] == '0') stop = true;
            binRep += bin.substr(currentIdx + 1, 4);
            currentIdx += 5;
        }
        std::cout << binRep << std::endl;
        std::cout << getDecFromBin(binRep) << std::endl;
    }
    else
    {
        char lengthTypeID = bin[6];
        if (lengthTypeID == '0')
        {
            int numSubPacketBits = getDecFromBin(bin.substr(7, 15));
            std::cout << numSubPacketBits << std::endl;
        }

        else if (lengthTypeID == '1')
        {
            int numSubPackets = getDecFromBin(bin.substr(7, 11));
            std::cout << numSubPackets << std::endl;
        }
    }
}

void part1()
{
    parsePacket(getBinFromHex());
    std::cout << getBinFromHex() << std::endl;
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