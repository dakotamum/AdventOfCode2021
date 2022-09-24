#include <iostream>
#include <memory>
#include <string>

struct aPair
{
    std::string stringValue = "";
    int intValue = -1;
    std::unique_ptr<aPair> leftChild = nullptr;
    std::unique_ptr<aPair> rightChild = nullptr;
    aPair(std::string value)
    {
        stringValue = value;
    }
};

void reduce(std::unique_ptr<aPair>& aPair)
{
    int leftBracketCount = 0;
    int rightBracketCount = 0;
    int splitIndex = 0;
    bool endLeftBracket = false;
    std::string first, second;
    std::cout << aPair->stringValue << std::endl;
    aPair->stringValue.erase(0, 1);
    aPair->stringValue.erase(aPair->stringValue.length() - 1, 1);
    
    if(aPair->stringValue[0] != '[')
    {
        splitIndex = 1;
    }
    else
    {
        for(int i = 0; i < aPair->stringValue.length(); i++)
        {

            if(!endLeftBracket)
            {
                if(aPair->stringValue[i] == '[')
                {
                    leftBracketCount++;
                }
                else if(aPair->stringValue[i] != ',')
                {
                    endLeftBracket = true;
                }
            }
            if(aPair->stringValue[i] == ']')
            {
                if(endLeftBracket && ++rightBracketCount == leftBracketCount)
                {
                    splitIndex = i;        
                    break;
                }
            }
            if(aPair->stringValue[i] == '[')
            {
                rightBracketCount = 0;
            }
        }
    }

    std::cout << aPair->stringValue.substr(0, splitIndex + 1) << std::endl;
    std::cout << aPair->stringValue.substr(splitIndex + 2, aPair->stringValue.length() - 1) << std::endl;
}

int main()
{
    
    std::unique_ptr<aPair> rootPair = std::make_unique<aPair>("[5,7]");
    reduce(rootPair);
    
    return 0;
}

