#include <iostream>
#include <fstream>

void part1()
{
	int number;
	std::ifstream fin("input.txt");
	int prevNum;
	fin >> prevNum;
	int nextNum;
	int count = 0;
	while (fin >> nextNum)
	{
		if (nextNum > prevNum)
			count++;
		prevNum = nextNum;
	}
	std::cout << count << std::endl;
}

void part2()
{
	int number;
	std::ifstream fin("input.txt");
	int prevNum1, prevNum2, prevNum3;
	fin >> prevNum1;
	fin >> prevNum2;
	fin >> prevNum3;
	int prevSum = prevNum1 + prevNum2 + prevNum3;

	int nextNum;
	int count = 0;
	
	while (fin >> nextNum)
	{
		int nextSum = prevNum2 + prevNum3 + nextNum;
		if (nextSum > prevSum)
			count++;
		prevNum2 = prevNum3;
		prevNum3 = nextNum;
		prevSum = nextSum;
	}
	std::cout << count << std::endl;
}

int main()
{
	part1();
	part2();
	return 0;
}
