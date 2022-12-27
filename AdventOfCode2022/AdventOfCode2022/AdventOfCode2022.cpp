#include <iostream>
using namespace std;

#include "Source/Solution1/AoCSolution1.h"

int main()
{
	AoCSolution1 Solution;
	Solution.Initialize(AoCHelpers::ProcessInput(1));
	const int Part = 2;
	cout << Solution.GetResult(Part) << endl;

	return 0;
}
