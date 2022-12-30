#include "AoCSolution3.h"

void AoCSolution3::Initialize(const vector<string>& Input)
{
	ProblemInput = Input;
	
}

string AoCSolution3::GetResult(const int InPart)
{
	int ResultSum = 0;
	Part = InPart;
	ParseInput();

	for (const auto& RuckSackContents : Contents)
	{
		SRuckSack RuckSack(RuckSackContents);
		const char CommonElement = RuckSack.GetCommonElement();
		cout << "Common Element: " << CommonElement << endl;
		ResultSum += GetPriority(CommonElement);
	}

	return to_string(ResultSum);
}

int AoCSolution3::GetPriority(char InChar)
{
	return islower(InChar) ? (InChar - 'a') + 1 : (InChar - 'A') + 27;
}

void AoCSolution3::ParseInput()
{
	if (Part == 1)
	{
		for (int RowIndex = 0; RowIndex < ProblemInput.size(); RowIndex++)
		{
			// cout << ProblemInput[RowIndex] << " -> ";
			Contents.push_back({ ProblemInput[RowIndex].substr(0, ProblemInput[RowIndex].length() / 2), ProblemInput[RowIndex].substr(ProblemInput[RowIndex].length() / 2, ProblemInput[RowIndex].length() / 2) });
			// cout << Contents[RowIndex].first << " , " << Contents[RowIndex].second << endl;
		}
	}
	else
	{
		for (int RowIndex = 0; RowIndex < ProblemInput.size() - 2; )
		{
			Contents.push_back({ ProblemInput[RowIndex++], ProblemInput[RowIndex++], ProblemInput[RowIndex++] });
		}
	}
}
