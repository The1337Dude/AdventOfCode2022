#include "AoCHelpers.h"
#include <filesystem>
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
}