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


// Looks like the stars indeed need to align for this one
// Start from the destination see when the last node is free
	// Keep ticking the clock till the last node opens up
	// Run breadth first search only till this particular 


// From Start to Finish as soon as possible
	// map keeps changing
	// while we keep ticking the map
		// When does a path from start to end emerge?

	// Minimum cost spanning tree -> which connects the first and last nodes within the minimum number of ticks


// Cost:
// Start Can stay here for a while
// Can stay in two nodes only for a while
// F(a,b) = a needs to be free now and b needs to be free within the timespan of a + 1
// 
// a -> ---
// b ->  -- -
// c ->   -  -
// F(a,b,c) = F(b) + 1


// Define a numeric expression and try to minimize our cost 

// Why the fuck I'm I trying to use a cost function ????
// Cost = Time
// T - time from the start 
// F(Terrrain, T, a, b) = 
// 
// Same node a,a cost = a if a is free in the next move
// Same node a,a cost = -1(infinity) if a is not free

// a,b (a and b are adjacent) F(a,b) 


// From Start to Finish
// Terrain keeps changing
// 


// void(Coords A, Coords B, Terrain)

int GetMinTicksAfterWhichAPositionIsFree(const Coordinates& Position, const STerrain& Terrain)
{
	return 0;
}

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
			Blizzard.StartingPosition = { X - 1, Y - 1 };
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

	SimQueue.push({ Player , 0 });

	DrawTerrain(Player, Terrain, 0);


	//return to_string(MinMoves(Player, Terrain));


	while (!SimQueue.empty())
	{
		static int epochCount = 0;
		auto PlayerIteration = SimQueue.front().first;
		auto Time = SimQueue.front().second;
		SimQueue.pop();

		Time++;

		DrawTerrain(PlayerIteration, Terrain, Time);

		if (PlayerIteration.HasReachedDestination())
		{
			return to_string(PlayerIteration.PlayerMoves);
		}

		const auto& PossibleMoves = PlayerIteration.GetPossibleMoves(Terrain, Time);
		for (const auto& NextMove : PossibleMoves)
		{
			auto NewPlayer = PlayerIteration;
			NewPlayer.UpdatePosition(NextMove);
			SimQueue.push({ NewPlayer, Time });
		}

		epochCount++;
	}

	return string();
}

void AoCSolution24::DrawTerrain(SPlayer& Player, STerrain& Terrain, const int CurrentTime)
{
	for (int height = 0; height < Terrain.Height; height++)
	{
		for (int width = 0; width < Terrain.Width; width++)
		{
			const Coordinates Coords{ width, height };
			const auto IsNodeFree = Terrain.IsNodeFree(Coords, Player.PlayerMoves);
			if (IsNodeFree)
			{
				if (Player.CurrentPosition.first == width && Player.CurrentPosition.second == height)
				{
					cout << "X";
				}
				else
				{
					cout << " ";
				}
			}
			else
			{
				cout << "^";
			}
		}
		cout << endl;
	}

	cout << "**********************************************************************" << endl;
}