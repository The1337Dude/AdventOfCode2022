#include <iostream>
using namespace std;

#include "Source/Solution9/AoCSolution9.h"

int main()
{
	shared_ptr<IAocSolution> Solution = make_shared<AoCSolution9>();

	Solution->Initialize(AoCHelpers::ProcessInput(9));

	const int Part2 = 2;
	cout << Solution->GetResult(Part2) << endl;

	return 0;
}
