// AoC_day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

void task1();
void task2();
int identifyAndDestroy(int, int, vector<vector<char>>&);

int main()
{
	//task1();
	task2();
}

void task1()
{
	vector<vector<char>> schematic;
	ifstream input;
	input.open("input.txt");
	while (input.good())
	{
		string line;
		int lineCount = 0;
		vector<char> tempLine;
		while (getline(input, line))
		{
			istringstream ss(line);
			char x;
			while (ss >> x)
			{
				tempLine.push_back(x);
			}
			schematic.push_back(tempLine);
			tempLine.clear();
		}
	}

	int xMax = schematic[0].size();
	int yMax = schematic.size();

	int sum = 0;

	for (int y = 1; y < yMax - 1; y++)
	{
		for (int x = 3; x < xMax - 3; x++)
		{
			char middleChar = schematic[y][x];
			if (middleChar == '.' || (middleChar - '0' >= 0 && middleChar - '0' <= 9))
				continue;
			for (int i = -1; i < 2; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					if (i == 0 && j == 0)
						continue;
					if (schematic[y + i][x + j] - '0' >= 0 && schematic[y + i][x + j] - '0' <= 9)
					{
						int part = identifyAndDestroy(x + j, y + i, schematic);
						cout << "part identified : " << part << endl;
						sum += part;
					}
				}
			}
		}
	}
	cout << "Sum of parts is: " << sum << endl;
}

void task2() //lets be naive and assume that there are no "gear trains" (: if it won't work only then it will become a problem
{
	vector<vector<char>> schematic;
	ifstream input;
	input.open("input.txt");
	while (input.good())
	{
		string line;
		int lineCount = 0;
		vector<char> tempLine;
		while (getline(input, line))
		{
			istringstream ss(line);
			char x;
			while (ss >> x)
			{
				tempLine.push_back(x);
			}
			schematic.push_back(tempLine);
			tempLine.clear();
		}
	}

	int xMax = schematic[0].size();
	int yMax = schematic.size();

	int sum = 0;

	for (int y = 1; y < yMax - 1; y++)
	{
		for (int x = 3; x < xMax - 3; x++)
		{
			char middleChar = schematic[y][x];
			if (middleChar != '*')
				continue;
			int part1 = 0;
			int part2 = 0;
			int product = 0;
			for (int i = -1; i < 2; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					if (i == 0 && j == 0)
						continue;
					if (schematic[y + i][x + j] - '0' >= 0 && schematic[y + i][x + j] - '0' <= 9)
					{
						int part = identifyAndDestroy(x + j, y + i, schematic);
						if (part1 == 0) {
							part1 = part;
							cout << "part 1 identified: " << part << endl;
						}
						else {
							part2 = part;
							cout << "part 2 identified: " << part << endl;
							product = part1 * part2;
							cout << "product of parts: " << product << endl;
							sum += product;
						}
					}
				}
			}
		}
	}
	cout << "Sum of parts is: " << sum << endl;
}

int identifyAndDestroy(int x, int y, vector<vector<char>>& schematic)
{
	int number = 0;
	if (schematic[y][x + 1] - '0' < 0 || schematic[y][x + 1] - '0' > 9)
	{
		if (schematic[y][x - 1] - '0' < 0 || schematic[y][x - 1] - '0' > 9)
		{
			number = schematic[y][x] - '0';
			schematic[y][x] = '.';
			return number;
		}
		if (schematic[y][x - 2] - '0' < 0 || schematic[y][x - 2] - '0' > 9)
		{
			number = ((schematic[y][x - 1] - '0') * 10) + (schematic[y][x] - '0');
			schematic[y][x - 1] = '.';
			schematic[y][x] = '.';
			return number;
		}
		number = ((schematic[y][x - 2] - '0') * 100) +  ((schematic[y][x - 1] - '0') * 10) + (schematic[y][x] - '0');
		schematic[y][x - 2] = '.';
		schematic[y][x - 1] = '.';
		schematic[y][x] = '.';
		return number;
	}
	if (schematic[y][x - 1] - '0' < 0 || schematic[y][x - 1] - '0' > 9)
	{
		if (schematic[y][x + 2] - '0' < 0 || schematic[y][x + 2] - '0' > 9)
		{
			number = ((schematic[y][x] - '0') * 10) + (schematic[y][x + 1] - '0');
			schematic[y][x + 1] = '.';
			schematic[y][x] = '.';
			return number;
		}
		number = (schematic[y][x + 2] - '0') + ((schematic[y][x + 1] - '0') * 10) + ((schematic[y][x] - '0') * 100);
		schematic[y][x + 2] = '.';
		schematic[y][x + 1] = '.';
		schematic[y][x] = '.';
		return number;
	}
	number = ((schematic[y][x - 1] - '0') * 100) + ((schematic[y][x] - '0') * 10) + (schematic[y][x + 1] - '0');
	schematic[y][x - 1] = '.';
	schematic[y][x] = '.';
	schematic[y][x + 1] = '.';
	return number;
}
