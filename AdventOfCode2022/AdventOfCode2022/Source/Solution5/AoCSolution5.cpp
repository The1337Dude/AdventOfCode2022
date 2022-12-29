#include "AoCSolution5.h"
#include <algorithm>


// Parsing the input is going to be a pain in the ass!
// 
// characters are located = 1, 5, 9 
// 
// 
//[G]                 [D] [R]        
//[W]         [V]     [C] [T] [M]    
//[L]         [P] [Z] [Q] [F] [V]    
//[J]         [S] [D] [J] [M] [T] [V]
//[B]     [M] [H] [L] [Z] [J] [B] [S]
//[R] [C] [T] [C] [T] [R] [D] [R] [D]
//[T] [W] [Z] [T] [P] [B] [B] [H] [P]
//[D] [S] [R] [D] [G] [F] [S] [L] [Q]
// 1   2   3   4   5   6   7   8   9 

//move 1 from 3 to 5
//move 5 from 5 to 4
//move 6 from 7 to 3
//move 6 from 1 to 3

// number of containers = (size of row + 1) / 4

// Location of each column value 4n + 1

void AoCSolution5::Initialize(const vector<string>& Input)
{
	ProblemInput = Input;
	ParseInput();
}

string AoCSolution5::GetResult(const int Part)
{
	string Result;

	for (const auto& Instruction : Instructions)
	{
		Bay.ExecuteInstruction(Instruction, Part == 2);
	}

	for (const auto& Char : Bay.GetTopElements())
	{
		Result += Char;
	}

	return Result;
}

void AoCSolution5::ParseInput()
{
	const auto GetColumnStartValue = [this]()
	{
		for (int InputRowIndex = 0; InputRowIndex < ProblemInput.size(); InputRowIndex++)
		{
			// first occurence of a numeric value
			for (const char& Character : ProblemInput[InputRowIndex])
			{
				if (isdigit(Character))
					return InputRowIndex - 1;
			}
		}

		return -1;
	};

	const auto GetNumberOfColumns = [this]()
	{
		return (ProblemInput[0].size() + 1) / 4;
	};

	const int NumberOfColumns = GetNumberOfColumns();
	vector<vector<char>> Containers;
	int Count = NumberOfColumns;
	while (Count--)
	{
		Containers.push_back(vector<char>());
	}

	for (int RowIndex = GetColumnStartValue(); RowIndex >= 0; RowIndex--)
	{
		for (int ElementNumber = 0; ElementNumber < NumberOfColumns; ElementNumber++)
		{
			const int ContainerElementValueIndex = 4 * ElementNumber + 1;
			if (ProblemInput[RowIndex][ContainerElementValueIndex] != ' ')
			{
				Containers[ElementNumber].push_back(ProblemInput[RowIndex][ContainerElementValueIndex]);
			}
		}
	}

	for (const auto& Container : Containers)
	{
		cout << Container.size() << endl;
		Bay.AddContainerColumn(Container);
	}

	// Parse instructions

	for (int RowIndex = GetColumnStartValue() + 3; RowIndex < ProblemInput.size(); RowIndex++)
	{
		vector<string> Tokens = AoCHelpers::Tokenize(ProblemInput[RowIndex], ' ');
		SInstruction Instruction;
		Instruction.Quantity = atoi(Tokens[1].c_str());
		Instruction.SourceContainerIndex = atoi(Tokens[3].c_str()) - 1;
		Instruction.DestinationContainerIndex = atoi(Tokens[5].c_str()) - 1;

		//cout << Tokens[1] << " " << Tokens[3] << " " << Tokens[5] << endl;
		Instructions.push_back(Instruction);
	}
}

void SBay::AddContainerColumn(const vector<char>& ContainerContents)
{
	SContainerColumn Column;
	for (const auto& Char : ContainerContents)
	{
		Column.Stack.push(Char);
	}

	Columns.push_back(Column);
}

void SBay::ExecuteInstruction(const SInstruction& Instruction, const bool MaintainOrder)
{
	vector<char> PoppedElements;
	for (int Count = 0; Count < Instruction.Quantity; Count++)
	{
		if (Columns[Instruction.SourceContainerIndex].Stack.empty())
		{
			return;
		}


		PoppedElements.push_back(Columns[Instruction.SourceContainerIndex].Stack.top());
		Columns[Instruction.SourceContainerIndex].Stack.pop();
	}

	if (MaintainOrder)
	{
		reverse(PoppedElements.begin(), PoppedElements.end());
	}

	for (const auto& Char : PoppedElements)
	{
		Columns[Instruction.DestinationContainerIndex].Stack.push(Char);
	}
}

vector<char> SBay::GetTopElements()
{
	vector<char> Result;

	for (int ColumnIndex = 0; ColumnIndex < Columns.size(); ColumnIndex++)
	{
		if (!Columns[ColumnIndex].Stack.empty())
		{
			Result.push_back(Columns[ColumnIndex].Stack.top());
		}
	}

	return Result;
}
