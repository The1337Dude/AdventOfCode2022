#include "AoCHelpers.h"
#include <filesystem>
#include <sstream>
using namespace std;

namespace AoCHelpers
{
	vector<string> ProcessInput(const int ProblemNumber)
	{
		string FilePath;
		FilePath = INPUT_DIR + to_string(ProblemNumber);

		return ProcessInput(FilePath);
	}

	vector<string> ProcessInput(const string& Path)
	{
		vector<string> Result;
		string buffer;
		ifstream InputFile(Path);

		if (InputFile.is_open())
		{
			while (getline(InputFile, buffer))
			{
				Result.push_back(buffer);
			}
		}

		return Result;
	}

	vector<string> Tokenize(const string& InputString, const char& Token)
	{
		vector<string> Result;

		// stringstream class check1
		stringstream stream(InputString);

		string intermediate;

		// Tokenizing w.r.t. space ' '
		while (getline(stream, intermediate, Token))
		{
			Result.push_back(intermediate);
		}

		return Result;
	}

	float distance(int x1, int y1, int x2, int y2)
	{
		// Calculating distance
		return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
	}
}