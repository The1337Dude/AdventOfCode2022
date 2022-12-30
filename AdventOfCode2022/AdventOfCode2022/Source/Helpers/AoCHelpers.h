#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

#define INPUT_DIR "D:/AdventOfCode2022/AdventOfCode2022/AdventOfCode2022/Input/"

namespace AoCHelpers
{
	vector<string> ProcessInput(const int ProblemNumber);
	vector<string> ProcessInput(const string& Path);
	vector<string> Tokenize(const string& InputString, const char& Token);
	float distance(int x1, int y1, int x2, int y2);
	float distance(int x1, int y1, int x2, int y2);
}

class IAocSolution
{
public:
	virtual void Initialize(const vector<string>& Input) = 0;
	virtual string GetResult(const int Part) = 0;
};
