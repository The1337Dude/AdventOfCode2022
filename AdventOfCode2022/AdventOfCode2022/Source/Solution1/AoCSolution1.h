#pragma once

#include "../Helpers/AoCHelpers.h"
#include <queue>

class AoCSolution1 : public IAocSolution
{
public:
	void Initialize(const vector<string>& Input) override;
	string GetResult(const int Part) override;

private:

	void ProcessInputAndGenerateHeap();
	string GetTopElementSum(const int Number);

	priority_queue<int> SumHeap;
	vector<string> ProblemInput;
};