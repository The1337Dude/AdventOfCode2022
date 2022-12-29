#pragma once

#include "../Helpers/AoCHelpers.h"

enum class ECPUInstructionType
{
	NOOP,
	ADDX,
};

struct ECPUInstruction
{
	ECPUInstructionType InstructionType = ECPUInstructionType::NOOP;
	int Immediate = 0;
};

class CPU
{
public:
	void ProcessInstructions(const vector<ECPUInstruction>& Instructions);
	int GetSignalStrength(const int Tick) { return  Tick < Signal.size() ? Signal[Tick - 1] * Tick : INT_MAX; }

	CPU()
	{
		for (int i = 0; i < CRTSize; i++)
		{
			CRT[i] = '.';
		}
	}

	void DrawCRT()
	{
		for (int Clock = 0; Clock < 240; Clock++)
		{
			const int RegisterValue = Signal[Clock];
			if (Clock % 40 == RegisterValue || Clock % 40 == RegisterValue - 1 || Clock % 40 == RegisterValue + 1)
			{
				CRT[Clock] = '#';
			}
			else
			{
				CRT[Clock] = '.';
			}
		}
		for (int j = 0; j < 6; j++)
		{
			for (int i = 0; i < 40; i++)
			{
				cout << CRT[j * 40 + i];
			}
			cout << endl;
		}
	};

private:
	void Tick()
	{ 
		cout << Clock << " " << Register << endl;
		Signal.push_back(Register);
		Clock++;
	};
	vector<int> Signal;
	int Clock = 0;
	int Register = 1;

	const int CRTSize = 240;
	char CRT[240];
};

class AoCSolution10 : public IAocSolution
{
public:
	void Initialize(const vector<string>& Input) override;
	string GetResult(const int Part) override;

private:
	void ParseInput();
	vector<ECPUInstruction> Instructions;
	vector<string> ProblemInput;
};
