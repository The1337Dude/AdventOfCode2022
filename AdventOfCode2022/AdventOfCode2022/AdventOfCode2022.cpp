#include <iostream>
using namespace std;

#include "Source/Solution1/AoCSolution1.h"
#include "Source/Solution24/AoCSolution24.h"
#include "Source/Solution5/AoCSolution5.h"
#include "Source/Solution10/AoCSolution10.h"

int main()
{
	/*AoCSolution1 Solution;*/
	//AoCSolution24 Solution;

	/*AoCSolution5 Solution;*/

	AoCSolution10 Solution;
	Solution.Initialize(AoCHelpers::ProcessInput(10));

	const int Part2 = 2;
	cout << Solution.GetResult(Part2) << endl;

	return 0;
}
