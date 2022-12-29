#pragma once

#include "../Helpers/AoCHelpers.h"
#include<map>
#include<queue>
#include<set>

typedef pair<int, int> Coordinates;

enum class EBlizzardDirectionType : int
{
	Up,
	Right,
	Down,
	Left
};

struct STerrain;

//#.######
//#>>.<^<#
//#.<..<<#
//#>v.><>#
//#<^v^^>#
//######.#


struct SBlizzard
{
	EBlizzardDirectionType Direction = EBlizzardDirectionType::Right;
	Coordinates StartingPosition;

public:
	Coordinates GetPositionAtTime(const int Time, const int TerrainWidth, const int TerrainHeight) const
	{
		const int Magnitude = (Direction == EBlizzardDirectionType::Left || Direction == EBlizzardDirectionType::Up) 
								? -1 : 1;

		if (Direction == EBlizzardDirectionType::Left || Direction == EBlizzardDirectionType::Right)
		{
			return { StartingPosition.first + (Time * Magnitude) % TerrainWidth, StartingPosition.second };
		}
		else
		{
			return { StartingPosition.first , StartingPosition.second + (Time * Magnitude) % TerrainHeight};
		}
	}
};

struct STerrain
{
	map<Coordinates, vector<SBlizzard>> NodeMap;
	int Height;
	int Width;

public:
	STerrain(const int InHeight, const int InWidth)
	{
		Height = InHeight;
		Width = InWidth;
	}

	void AddBlizzard(const SBlizzard&& Blizzard)
	{
		switch (Blizzard.Direction)
		{
			case EBlizzardDirectionType::Left:
			case EBlizzardDirectionType::Right:
				for (int X = 0; X < Width; X++)
				{
					const Coordinates Coords = { X, Blizzard.StartingPosition.second };
					NodeMap[Coords].push_back(Blizzard);
				}
				break;
			case EBlizzardDirectionType::Up:
			case EBlizzardDirectionType::Down:
				for (int Y = 0; Y < Height; Y++)
				{
					const Coordinates Coords = { Blizzard.StartingPosition.first, Y };
					NodeMap[Coords].push_back(Blizzard);
				}
				break;
		}
	}

	bool IsNodeFree(const Coordinates& Position, const int Time) const
	{
		if (Position.first < 0 || Position.first > Width - 1 || Position.second < 0 || Position.second > Height - 1)
		{
			return false;
		}

		auto Iterator = NodeMap.find(Position);
		if (Iterator == NodeMap.end())
		{
			return true;
		}

		for (const auto& Blizzard : Iterator->second)
		{
			if (Position == Blizzard.GetPositionAtTime(Time, Width, Height))
			{
				return false;
			}
		}

		return true;
	}
};

enum class EPlayerMovementType : int
{
	Wait,
	Up,
	Down,
	Left,
	Right,
};

struct SPlayer
{
	Coordinates CurrentPosition = {0, -1};
	Coordinates Destination;
	int PlayerMoves = 0;

public:
	SPlayer(const Coordinates& InStartPosition, const Coordinates& InDestination)
	{
		CurrentPosition = InStartPosition;
		Destination = InDestination;
	}

	void UpdatePosition(const Coordinates& NextPosition)
	{
		CurrentPosition = NextPosition;
		PlayerMoves++;
	}

	bool HasReachedDestination() const { return CurrentPosition == Destination; }

	set<Coordinates> GetPossibleMoves(const STerrain& Terrain, const int CurrentTime) const
	{
		set<Coordinates> Result;

		// current position is out of the grid
		if (CurrentPosition.second == -1)
		{
			const Coordinates StartCoordinates = { 0, 0 };
			if (Terrain.IsNodeFree(StartCoordinates, CurrentTime))
			{
				Result.insert(StartCoordinates);
			}
			// wait case
			Result.insert(CurrentPosition);

			return Result;
		}
		
		// Wait Case
		if (Terrain.IsNodeFree(CurrentPosition, CurrentTime))
		{
			Result.insert(CurrentPosition);
		}

		// current position is 0,0
		if (CurrentPosition.first == 0 && CurrentPosition.second == 0)
		{
			Result.insert({ 0, -1 });
		}

		// end position
		if (CurrentPosition.first == Terrain.Width - 1 && CurrentPosition.second == Terrain.Height - 1)
		{
			Result.insert({ Terrain.Width - 1, Terrain.Height });
		}

		//any arbitraty possition
		const vector<Coordinates> PossibleNextCoordinates = {
			// left
			{CurrentPosition.first - 1, CurrentPosition.second},
			// right
			{CurrentPosition.first + 1, CurrentPosition.second},
			// Up
			{CurrentPosition.first, CurrentPosition.second - 1},
			// Down
			{CurrentPosition.first, CurrentPosition.second + 1}
		};

		for (const auto& PossibleNextCoordinate : PossibleNextCoordinates)
		{
			if (Terrain.IsNodeFree(PossibleNextCoordinate, CurrentTime))
			{
				Result.insert(PossibleNextCoordinate);
			}
		}

		return Result;
	}
};


class PQueueComparator
{
public:
	bool operator() (const SPlayer& Entry1, const SPlayer& Entry2)
	{
		return distance(Entry1.CurrentPosition.first,
						Entry1.CurrentPosition.second,
						Entry1.Destination.first,
						Entry1.Destination.second) 
						>
				distance(Entry2.CurrentPosition.first,
						 Entry2.CurrentPosition.second,
				         Entry2.Destination.first,
				         Entry2.Destination.second)
			
			&& Entry1.PlayerMoves > Entry2.PlayerMoves;
	}

private:
	float distance(int x1, int y1, int x2, int y2)
	{
		// Calculating distance
		return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
	}
};


class AoCSolution24 : public IAocSolution
{
public:
	void Initialize(const vector<string>& Input) override;
	string GetResult(const int Part) override;

private:
	void DrawTerrain(SPlayer& PlayerIteration, STerrain& Terrain, const int CurrentTime);
	queue<pair<SPlayer, int>> SimQueue;
	vector<string> ProblemInput;
};


// Node
// you can move up, down, left, or right, or you can wait in place.
// You and the blizzards act simultaneously
// you cannot share a position with a blizzard.
// Either Free
// Either Occupied 
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

// I need to get the Player from A to B
// Player can move (X +/- 1, Y +/- 1) or stay at the same spot
// 


// Node's occupancy as a function of Time
// At time T -> Agents in the Row who are moving horizontally
// At time T -> Agents in the Column who are moving vertically 

// NodeNextFree:
	// Blizzard as a funtion of Time = Blizzard Initial Position +|- T % (length | width)
	// Left = [Current Node - T % width ]

// Node
// T is the time from start of the game
// Each Position(Actor, T) = Position(Actor,0)
// At time T is only affected by Actors Node.Position.X + T % (), Node Position.Y + T]
