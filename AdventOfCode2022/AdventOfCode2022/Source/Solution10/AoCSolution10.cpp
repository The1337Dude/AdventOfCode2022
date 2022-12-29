#include "AoCSolution10.h"

void AoCSolution10::Initialize(const vector<string>& Input)
{
	ProblemInput = Input;
	ParseInput();
}

string AoCSolution10::GetResult(const int Part)
{
	CPU Cpu;
	Cpu.ProcessInstructions(Instructions);

	Cpu.DrawCRT();

	return to_string(Cpu.GetSignalStrength(20) +
		Cpu.GetSignalStrength(60) + 
		Cpu.GetSignalStrength(100) + 
		Cpu.GetSignalStrength(140) + 
		Cpu.GetSignalStrength(180) + 
		Cpu.GetSignalStrength(220));
}

void AoCSolution10::ParseInput()
{
	for (int RowIndex = 0; RowIndex < ProblemInput.size(); RowIndex++)
	{
		vector<string> Tokens = AoCHelpers::Tokenize(ProblemInput[RowIndex], ' ');
		ECPUInstruction Instruction;
		if (Tokens[0] == "noop")
		{
			cout << Tokens[0] << endl;
			Instruction.InstructionType = ECPUInstructionType::NOOP;
		}
		else
		{
			cout << Tokens[0] << " " << Tokens[1] << endl;
			Instruction.InstructionType = ECPUInstructionType::ADDX;
			Instruction.Immediate = atoi(Tokens[1].c_str());
		}

		Instructions.push_back(Instruction);
	}
}

void CPU::ProcessInstructions(const vector<ECPUInstruction>& Instructions)
{
	for (const auto& Instruction : Instructions)
	{
		switch (Instruction.InstructionType)
		{
			case ECPUInstructionType::NOOP:
				Tick();
				break;
			case ECPUInstructionType::ADDX:
				Tick();
				Tick();
				Register += Instruction.Immediate;
				break;
		}
	}
}
