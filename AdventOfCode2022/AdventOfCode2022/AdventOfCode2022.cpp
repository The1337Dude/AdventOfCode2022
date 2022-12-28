#include <iostream>
using namespace std;

#include "Source/Solution1/AoCSolution1.h"
#include "Source/Solution24/AoCSolution24.h"

int main()
{
	/*AoCSolution1 Solution;*/
	AoCSolution24 Solution;
	Solution.Initialize(AoCHelpers::ProcessInput(24));
	const int Part = 2;
	cout << Solution.GetResult(Part) << endl;

	return 0;
}
