#include "AoCSolution24.h"

void AoCSolution24::Initialize(const vector<string>& Input)
{
	ProblemInput = Input;
}

// Node
// you can move up, down, left, or right, or you can wait in place.
// You and the blizzards act simultaneously
// you cannot share a position with a blizzard.
// struct Node { }
// Either Free
// Either Occupied 
// Node can hold an actor
// Node { vector<Actors>, connections<Left, Right, > }
// Node - Willbefree?
// Actors { Direction }
// Player -> 
// Do I need to compute 
//#.######
//#>>.<^<#
//#.<..<<#
//#>v.><>#
//#<^v^^>#
//######.#


// Can do a breadth first search evaluating each choice from every move

string AoCSolution24::GetResult(const int Part)
{
	const int TerrainHeight = ProblemInput.size() - 2;
	if (TerrainHeight == 0)
	{
		return string();
	}

	const int TerrainWidth = ProblemInput[0].length() - 2;

	STerrain Terrain(TerrainHeight, TerrainWidth);
	for (int Y = 1; Y < ProblemInput.size() - 1; Y++)
	{
		for (int X = 1; X < ProblemInput[Y].length() - 1; X++)
		{
			SBlizzard Blizzard;
			Blizzard.CurrentPosition = { X - 1, Y - 1 };
			const char Character = ProblemInput[Y][X];
			cout << Character << " ";
			switch (Character)
			{
				case '^':
					Blizzard.Direction = EBlizzardDirectionType::Up;
					Terrain.AddBlizzard(move(Blizzard));
					continue;
				case '<':
					Blizzard.Direction = EBlizzardDirectionType::Left;
					Terrain.AddBlizzard(move(Blizzard));
					continue;
				case '>':
					Blizzard.Direction = EBlizzardDirectionType::Right;
					Terrain.AddBlizzard(move(Blizzard));
					continue;
				case 'v':
					Blizzard.Direction = EBlizzardDirectionType::Down;
					Terrain.AddBlizzard(move(Blizzard));
					continue;
				default:
					continue;
			}
		}

		cout << endl;
	}

	cout << "**********************************************************************" << endl;

	SPlayer Player({ 0, -1 }, { TerrainWidth - 1, TerrainHeight });

	SimQueue.push({ Player, Terrain });

	DrawTerrain(Player, Terrain);

	//return to_string(MinMoves(Player, Terrain));


	while (!SimQueue.empty())
	{
		static int epochCount = 0;
		auto SimIteration = SimQueue.top();
		auto PlayerIteration = SimIteration.first;
		auto TerrainIteration = SimIteration.second;

		if (epochCount % 1000 == 0)
		{
			DrawTerrain(PlayerIteration, TerrainIteration);
		}
		
		SimQueue.pop();

		if (PlayerIteration.HasReachedDestination())
		{
			return to_string(SimIteration.first.PlayerMoves);
		}

		TerrainIteration.Tick();

		const auto& PossibleMoves = PlayerIteration.GetPossibleMoves(TerrainIteration);
		for (const auto& NextMove : PossibleMoves)
		{
			auto NewPlayer = PlayerIteration;
			NewPlayer.UpdatePosition(NextMove);
			SimQueue.push({ NewPlayer, TerrainIteration});
		}

		epochCount++;
	}

	return string();
}

int AoCSolution24::MinMoves(SPlayer& PlayerIteration, STerrain& TerrainIteration)
{
	if (PlayerIteration.HasReachedDestination())
	{
		return PlayerIteration.PlayerMoves;
	}

	TerrainIteration.Tick();
	const auto& PossibleMoves = PlayerIteration.GetPossibleMoves(TerrainIteration);

	vector<int> MinResults;
	for (const auto& NextMove : PossibleMoves)
	{
		auto NewPlayer = PlayerIteration;
		NewPlayer.UpdatePosition(NextMove);
		
		MinResults.push_back(MinMoves(NewPlayer, TerrainIteration));
	}

	if (MinResults.size() != 0)
	{
		return *min_element(MinResults.begin(), MinResults.end());
	}

	return 0;
}

void AoCSolution24::DrawTerrain(SPlayer& Player, STerrain& Terrain)
{
	for (int height = 0; height < Terrain.Height; height++)
	{
		for (int width = 0; width < Terrain.Width; width++)
		{
			const Coordinates Coords{ width, height };
			const auto IsNodeFree = Terrain.IsNodeFree(Coords);
			if (IsNodeFree)
			{
				if (Player.CurrentPosition.first == width && Player.CurrentPosition.second == height)
				{
					cout << "X";
				}
				else
				{
					cout << ".";
				}
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}

	cout << "**********************************************************************" << endl;
}