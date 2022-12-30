#pragma once

#include "../Helpers/AoCHelpers.h"
#include<map>
#include<set>

struct SCompartment
{
	SCompartment(const string& InItems)
	{
		Items = InItems;
	}

	string GetItems() const { return Items; }

private:
	string Items;
};

struct SRuckSack
{
	SRuckSack(const vector<string>& Contents)
	{
		for (const auto& Items : Contents)
		{
			Compartments.push_back(SCompartment(Items));
		}
	}

	char GetCommonElement()
	{
		map<char, int> CharMap;

		for (int CompartmentIndex = 0; CompartmentIndex < Compartments.size(); CompartmentIndex++)
		{
			for (const char& Char : Compartments[CompartmentIndex].GetItems())
			{
				auto Iterator = CharMap.find(Char);
				if (Iterator == CharMap.end())
				{
					if (CompartmentIndex != 0)
					{
						CharMap.insert({ Char, -1 });
					}
					else
					{
						CharMap.insert({ Char, CompartmentIndex + 1 });
					}
				}
				else
				{
					if (Iterator->second == CompartmentIndex)
					{
						Iterator->second = CompartmentIndex + 1;
						if (Iterator->second == Compartments.size())
						{
							return Char;
						}
					}
				}
			}
		}
		
		return ' ';
	}

private:
	vector<SCompartment> Compartments;
};

class AoCSolution3 : public IAocSolution
{
public:
	void Initialize(const vector<string>& Input) override;
	string GetResult(const int Part) override;

private:
	int GetPriority(char InChar);
	void ParseInput();
	vector<string> ProblemInput;

	int Part = 1;
	vector<vector<string>> Contents;
};
