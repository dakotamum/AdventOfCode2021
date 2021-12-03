#include <iostream>
#include <fstream>
#include <string>

void part1()
{
	std::ifstream fin("input.txt");

	std::string direction;
	int number;
	int horizontal = 0;
	int depth = 0;
	while (fin >> direction)
	{
		fin >> number;
		if(direction == "forward")
		{
			horizontal += number;	
		}
		if(direction == "down")
		{
			depth += number;	
		}
		if(direction == "up")
		{
			depth -= number;	
		}
	}
	std::cout << horizontal * depth << std::endl;
	fin.close();
}

void part2()
{
	std::ifstream fin("input.txt");
	std::string direction;
	int number;
	int horizontal = 0;
	int depth = 0;
	int aim = 0;
	while (fin >> direction)
	{
		fin >> number;
		if(direction == "forward")
		{
			horizontal += number;	
			depth += number * aim;
		}
		if(direction == "down")
		{
			aim += number;
		}
		if(direction == "up")
		{
			aim -= number;
		}
	}
	std::cout << horizontal * depth << std::endl;
	fin.close();
}

int main()
{
	//part1();
	part2();
	return 0;
}
