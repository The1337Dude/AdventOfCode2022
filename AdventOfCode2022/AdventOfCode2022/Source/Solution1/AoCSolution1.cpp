#include "AoCSolution1.h"

void AoCSolution1::Initialize(const vector<string>& Input)
{
	ProblemInput = Input;
	ProcessInputAndGenerateHeap();
}

string AoCSolution1::GetResult(const int Part)
{
	if (Part == 1)
	{
		return GetTopElementSum(1);
	}

	return GetTopElementSum(3);
}

void AoCSolution1::ProcessInputAndGenerateHeap()
{
	int Sum = 0;
	for (const auto& Line : ProblemInput)
	{
		if (Line.empty())
		{
			SumHeap.push(Sum);
			Sum = 0;
			continue;
		}

		Sum += atoi(Line.c_str());
	}

	// Push last element too
	if (Sum != 0)
	{
		SumHeap.push(Sum);
	}
}

string AoCSolution1::GetTopElementSum(const int Number)
{
	int ResultValue = 0;
	priority_queue<int> TempHeap = SumHeap;

	for (int Count = 0; Count < Number; Count++)
	{
		ResultValue += TempHeap.top();
		TempHeap.pop();
	}

	return to_string(ResultValue);
}

