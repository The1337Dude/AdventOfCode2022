#pragma once

#include "../Helpers/AoCHelpers.h"
#include <stack>
#include <vector>

struct SContainerColumn
{
	stack<char> Stack;
};

struct SInstruction
{
	int SourceContainerIndex = 0;
	int DestinationContainerIndex = 0;
	int Quantity;
};

struct SBay
{
	vector<SContainerColumn> Columns;

	void AddContainerColumn(const vector<char>& ContainerContents);

	void ExecuteInstruction(const SInstruction& Instruction, const bool MaintainOrder = false);

	vector<char> GetTopElements();
};

class AoCSolution5 : public IAocSolution
{
public:
	void Initialize(const vector<string>& Input) override;
	string GetResult(const int Part) override;

private:
	SBay Bay;
	vector<SInstruction> Instructions;
	void ParseInput();

	vector<string> ProblemInput;
};
