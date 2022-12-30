#pragma once

#include "../Helpers/AoCHelpers.h"
#include <set>

typedef pair<int, int> Coordinates;

struct SKnot
{
	void UpdatePosition(const Coordinates& InPosition)
	{
		Position = InPosition;
		Visited.insert(Position);
	};

	int GetNumberOfVisitedNodes() { return Visited.size(); }

	Coordinates GetCurrentPosition() const { return Position; }

private:
	Coordinates Position = { 0, 0};
	set<Coordinates> Visited;
};

enum class EDirectionType : int
{
	Up,
	Down,
	Right,
	Left
};

struct SMovementInstruction
{
	EDirectionType Direction;
	int NumberOfSteps;
};

struct SRope
{
	SRope(const int NumberOfNodes, const int InGridWidth, const int InGridHeight, const int InAllowDifference)
	{
		GridWidth = InGridWidth;
		GridHeight = InGridHeight;
		AllowedDifference = InAllowDifference;
		int Counter = NumberOfNodes;
		while(Counter--)
		{
			Knots.push_back(SKnot());
			Knots.back().UpdatePosition(Coordinates(0, InGridHeight - 1));
		}
		Head = &Knots.front();
		Tail = &Knots.back();
		DrawGrid();
	}

	void ProcessInstruction(const SMovementInstruction& Instruction);

	int GetNumberOfUniqueNodesVisitedByTail() { return Tail->GetNumberOfVisitedNodes(); }

private:
	void DrawGrid();
	void UpdateRopePosition();
	bool AreNodesTooFar(const SKnot& Knot1, const SKnot& Knot2);
	int GridWidth;
	int GridHeight;
	int AllowedDifference;
	SKnot* Head;
	SKnot* Tail;
	vector<SKnot> Knots;
};

class AoCSolution9 : public IAocSolution
{
public:
	void Initialize(const vector<string>& Input) override;
	string GetResult(const int Part) override;

private:
	void ParseInput();
	vector<SMovementInstruction> Instructions;
	vector<string> ProblemInput;
};
