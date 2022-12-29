#include <iostream>
using namespace std;

#include "Source/Solution1/AoCSolution1.h"
#include "Source/Solution24/AoCSolution24.h"
#include "Source/Solution5/AoCSolution5.h"

int main()
{
	/*AoCSolution1 Solution;*/
	//AoCSolution24 Solution;

	AoCSolution5 Solution;
	Solution.Initialize(AoCHelpers::ProcessInput(5));
	//const int Part1 = 1;
	//cout << Solution.GetResult(Part1) << endl;
	const int Part2 = 2;
	cout << Solution.GetResult(Part2) << endl;

	return 0;
}
