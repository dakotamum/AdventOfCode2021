#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>

class BingoCard
{
    private:
        struct cardSlot
        {
            int number;
            bool isMarked;
            cardSlot(int aNum, bool marked = false)
            {
                number = aNum;
                isMarked = marked;
            }
        }; 
        std::vector<std::vector<cardSlot>> m_cardSlots;

    public:
        BingoCard(std::vector<std::vector<int>> numbers)
        {
            for(int i = 0; i < numbers.size(); i++)
            {
                std::vector<cardSlot> newRow;
                for(int j = 0; j < numbers.size(); j++)
                {
                    newRow.push_back(cardSlot(numbers[i][j]));
                }
                m_cardSlots.push_back(newRow);
            }
        }
        void markNumber(int aNum)
        {
            for(int i = 0; i < m_cardSlots.size(); i++)
            {
                for(int j = 0; j < m_cardSlots.size(); j++)
                {
                    if(m_cardSlots[i][j].number == aNum)
                    {
                        m_cardSlots[i][j].isMarked = true;
                    }
                }
            }
        }
        int unmarkedSum()
        {
            int sum = 0;
            for(int i = 0; i < m_cardSlots.size(); i++)
            {
                for(int j = 0; j < m_cardSlots.size(); j++)
                {
                    if(m_cardSlots[i][j].isMarked == false) sum += m_cardSlots[i][j].number;
                }
            }
            return sum;
        }

        int checkCard()
        {
            int inARow = 0;
            int sum = 0;
            // check by row
            for(int i = 0; i < m_cardSlots.size(); i++)
            {
                for(int j = 0; j < m_cardSlots.size(); j++)
                {
                    if (m_cardSlots[i][j].isMarked == true)
                        inARow++;
                    else
                    {
                        inARow = 0;
                        break;
                    }
                }
                if (inARow == 5)
                {
                    sum = this->unmarkedSum();
                    break;
                }
            }

            // check by column
            for(int i = 0; i < m_cardSlots.size(); i++)
            {
                for(int j = 0; j < m_cardSlots.size(); j++)
                {
                    if (m_cardSlots[j][i].isMarked == true)
                        inARow++;
                    else
                    {
                        inARow = 0;
                        break;
                    }
                }
                if (inARow == 5)
                {
                    sum = this->unmarkedSum();
                    break;
                }
            }
            return sum;
        }
};

std::tuple<std::vector<int>, std::vector<BingoCard>> readInput()
{
    std::string someStringNumbers;
    std::vector<int> numbers;
    std::ifstream fin("input.txt");
    std::getline(fin, someStringNumbers);
    std::istringstream ss(someStringNumbers);

    while(ss)
    {
        std::string stringNum;
        if(!getline(ss, stringNum, ',')) break;
        numbers.push_back(std::stoi(stringNum));
    }

    std::string newBingoCardRow;
    std::vector<std::vector<int>> newBingoCard;
    std::vector<BingoCard> bingoCards;

    while(getline(fin, newBingoCardRow))
    {
        if (newBingoCardRow != "")
        {
            std::istringstream strstream(newBingoCardRow);
            std::vector<int> newIntsRow;
            int aNum;
            while(strstream >> aNum)
            {
                newIntsRow.push_back(aNum);
            }
            newBingoCard.push_back(newIntsRow);
            if(newBingoCard.size() == 5)
            {
                bingoCards.push_back(BingoCard(newBingoCard));
                newBingoCard.clear();
            }
        }
    }
    fin.close();
    return std::make_tuple(numbers, bingoCards);
}

void markCards(std::vector<BingoCard>& bingoCards, int num)
{
    for(int i = 0; i < bingoCards.size(); i++)
    {
        bingoCards[i].markNumber(num);
    }
}

void part1()
{
    auto tupe = readInput();
    std::vector<int> numbers = std::get<0>(tupe);
    std::vector<BingoCard> bingoCards = std::get<1>(tupe);
    int sum = 0;
    int answer = 0;

    for(int i = 0; i < numbers.size(); i++)
    {
        markCards(bingoCards, numbers[i]);
        for (int j = 0; j < bingoCards.size(); j++)
        {
            sum = bingoCards[j].checkCard();
            if (sum != 0)
            {
                answer = sum * numbers[i];
                break;
            }
        }
        if (sum != 0) break;
    }
    std::cout << answer << std::endl;
}

void part2()
{
    auto tupe = readInput();
    std::vector<int> numbers = std::get<0>(tupe);
    std::vector<BingoCard> bingoCards = std::get<1>(tupe);
    int sum = 0;
    int answer = 0;


    for(int i = 0; i < numbers.size(); i++)
    {
        std::vector<BingoCard> cardsThatHaveNotWon;
        markCards(bingoCards, numbers[i]);
        for (int j = 0; j < bingoCards.size(); j++)
        {
            sum = bingoCards[j].checkCard();
            if (sum == 0 && bingoCards.size() > 1) cardsThatHaveNotWon.push_back(bingoCards[j]);
            else if (sum != 0 && bingoCards.size() == 1)
            {
                answer = sum * numbers[i];
                break;
            }
        }
        bingoCards = cardsThatHaveNotWon;
    }
    std::cout << answer << std::endl;
}

int main()
{
    part1(); 
    part2(); 
    return 0;
}