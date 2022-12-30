#include "AoCSolution9.h"

void AoCSolution9::Initialize(const vector<string>& Input)
{
	ProblemInput = Input;
	ParseInput();
}

string AoCSolution9::GetResult(const int Part)
{
	SRope Rope(10, 26, 21, 2);

	for (const auto& Instruction : Instructions)
	{
		Rope.ProcessInstruction(Instruction);
	}

	return to_string(Rope.GetNumberOfUniqueNodesVisitedByTail());
}

void AoCSolution9::ParseInput()
{
	for (int RowIndex = 0; RowIndex < ProblemInput.size(); RowIndex++)
	{
		vector<string> Tokens = AoCHelpers::Tokenize(ProblemInput[RowIndex], ' ');
		SMovementInstruction Instruction;
		
		if (Tokens[0] == "U")
		{
			Instruction.Direction = EDirectionType::Up;
		}
		else if (Tokens[0] == "D")
		{
			Instruction.Direction = EDirectionType::Down;
		}
		else if (Tokens[0] == "L")
		{
			Instruction.Direction = EDirectionType::Left;
		}
		else
		{
			Instruction.Direction = EDirectionType::Right;
		}
		
		Instruction.NumberOfSteps = atoi(Tokens[1].c_str());

		Instructions.push_back(Instruction);
	}
}

void SRope::ProcessInstruction(const SMovementInstruction& Instruction)
{
	int Counter = Instruction.NumberOfSteps;
	const int Magnitude = Instruction.Direction == EDirectionType::Left || Instruction.Direction == EDirectionType::Up ? -1 : 1;

	while (Counter--)
	{
		const Coordinates& HeadCurrentPosition = Head->GetCurrentPosition();
		switch (Instruction.Direction)
		{
		case EDirectionType::Left:
		case EDirectionType::Right:
			Head->UpdatePosition({ HeadCurrentPosition.first + Magnitude, HeadCurrentPosition.second });
			break;
		case EDirectionType::Up:
		case EDirectionType::Down:
			Head->UpdatePosition({ HeadCurrentPosition.first, HeadCurrentPosition.second + Magnitude });
			break;
		}
		DrawGrid();
		UpdateRopePosition();
	}
}

void SRope::DrawGrid()
{
	cout << "**************************************" << endl;
	for (int Row = 0; Row < GridHeight; Row++)
	{
		for (int Column = 0; Column < GridWidth; Column++)
		{
			int KnotIndex;
			for (KnotIndex = 0; KnotIndex < Knots.size(); KnotIndex++)
			{
				const auto KnotPosition = Knots[KnotIndex].GetCurrentPosition();
				if (KnotPosition.first == Column && KnotPosition.second == Row)
				{
					if (KnotIndex == 0)
					{
						cout << "H";
					}
					else if (KnotIndex == Knots.size() - 1)
					{
						cout << "T";
					}
					else
					{
						cout << KnotIndex + 1;
					}
					break;
				}
			}
			if (KnotIndex >= Knots.size())
			{
				cout << ".";
			}
		}
		cout << endl;
	}
}

void SRope::UpdateRopePosition()
{
	for (int KnotIndex = 1; KnotIndex < Knots.size(); KnotIndex++)
	{
		SKnot& HeadKnot = Knots[KnotIndex - 1];
		SKnot& TailKnot = Knots[KnotIndex];

		if (AreNodesTooFar(HeadKnot, TailKnot))
		{
			const Coordinates HeadPosition = HeadKnot.GetCurrentPosition();
			const Coordinates TailPosition = TailKnot.GetCurrentPosition();

			// H.T, T.H, (x,y) (x + 2,y), (x - 2, y)(x,y) -> (x-1,y)(x-1,y)
			// H  T (x, y) (x, y + 2) 
			// .  .					 -> 
			// T  H (x,y) (x , y - 2) 

			// H.. (x,y)
			// ..T (x+2, y+1) -> (x + 1, y)

			const int XCoordinateDiff = TailPosition.first - HeadPosition.first;
			const int YCoordinateDiff = TailPosition.second - HeadPosition.second;

			TailKnot.UpdatePosition({ HeadPosition.first + XCoordinateDiff / AllowedDifference, HeadPosition.second + YCoordinateDiff / AllowedDifference });
			DrawGrid();
		}
		else
		{
			break;
		}
	}
}

bool SRope::AreNodesTooFar(const SKnot& Knot1, const SKnot& Knot2)
{
	const Coordinates HeadPosition = Knot1.GetCurrentPosition();
	const Coordinates TailPosition = Knot2.GetCurrentPosition();

	return abs(HeadPosition.first - TailPosition.first) >= AllowedDifference || abs(HeadPosition.second - TailPosition.second) >= AllowedDifference;
}
