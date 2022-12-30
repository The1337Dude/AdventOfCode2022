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

struct SBlizzard
{
	EBlizzardDirectionType Direction = EBlizzardDirectionType::Right;
	Coordinates CurrentPosition;
};

struct STerrain
{
	vector<SBlizzard> Blizzards;
	map<Coordinates, int> NodeMap;
	int Height;
	int Width;

public:
	STerrain(const int InHeight, const int InWidth)
	{
		Height = InHeight;
		Width = InWidth;
	}

	void AddBlizzard(SBlizzard&& Blizzard)
	{
		NodeMap[Blizzard.CurrentPosition]++;
		Blizzards.push_back(move(Blizzard));
	}

	bool IsNodeFree(const Coordinates& Position) const
	{
		if (Position.first < 0 || Position.first > Width - 1 || Position.second < 0 || Position.second > Height - 1)
		{
			return false; 
		}

		const auto Iterator = NodeMap.find(Position);
		return Iterator == NodeMap.end() || (Iterator != NodeMap.end() && Iterator->second == 0);
	}
	
	void Tick()
	{
		for (auto& Blizzard : Blizzards)
		{
			NodeMap[Blizzard.CurrentPosition]--;
			Blizzard.CurrentPosition = GetNextPosition(Blizzard);
			NodeMap[Blizzard.CurrentPosition]++;
		}
	}
private:
	Coordinates GetNextPosition(const SBlizzard& Blizzard) const
	{
		Coordinates Result = Blizzard.CurrentPosition;
		switch (Blizzard.Direction)
		{
		case EBlizzardDirectionType::Left:
			if (Result.first == 0)
			{
				Result.first = Width - 1;
			}
			else
			{
				Result.first--;
			}
			break;
		case EBlizzardDirectionType::Right:
			if (Result.first == Width - 1)
			{
				Result.first = 0;
			}
			else
			{
				Result.first++;
			}
			break;
		case EBlizzardDirectionType::Down:
			if (Result.second == Height - 1)
			{
				Result.second = 0;
			}
			else
			{
				Result.second++;
			}
			break;
		case EBlizzardDirectionType::Up:
			if (Result.second == 0)
			{
				Result.second = Height - 1;
			}
			else
			{
				Result.second--;
			}
			break;
		default:
			break;
		}
		return Result;
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

	set<Coordinates> GetPossibleMoves(const STerrain& Terrain) const
	{
		set<Coordinates> Result;

		// current position is out of the grid
		if (CurrentPosition.second == -1)
		{
			const Coordinates StartCoordinates = { 0, 0 };
			if (Terrain.IsNodeFree(StartCoordinates))
			{
				Result.insert(StartCoordinates);
			}
			else
			{
				// wait case
				Result.insert(CurrentPosition);
			}

			return Result;
		}
		
		// Wait Case
		if (Terrain.IsNodeFree(CurrentPosition))
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
			if (Terrain.IsNodeFree(PossibleNextCoordinate))
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
	bool operator() (const pair<SPlayer, STerrain>& Entry1, const pair<SPlayer, STerrain>& Entry2)
	{
		return Entry1.first.PlayerMoves > Entry2.first.PlayerMoves;
		/*return distance(Entry1.first.CurrentPosition.first,
						Entry1.first.CurrentPosition.second,
						Entry1.first.Destination.first,
						Entry1.first.Destination.second) 
						>
			 distance(Entry2.first.CurrentPosition.first,
				Entry2.first.CurrentPosition.second,
				Entry2.first.Destination.first,
				Entry2.first.Destination.second);*/
	}
};


class AoCSolution24 : public IAocSolution
{
public:
	void Initialize(const vector<string>& Input) override;
	string GetResult(const int Part) override;

private:
	int MinMoves(SPlayer& PlayerIteration, STerrain& Terrain);
	void DrawTerrain(SPlayer& PlayerIteration, STerrain& Terrain);
	priority_queue<pair<SPlayer, STerrain>, vector<pair<SPlayer, STerrain>>, PQueueComparator> SimQueue;
	vector<string> ProblemInput;
};