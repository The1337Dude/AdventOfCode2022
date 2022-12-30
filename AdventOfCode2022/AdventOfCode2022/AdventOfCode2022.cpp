#include <iostream>
using namespace std;

#include "Source/Solution3/AoCSolution3.h"

int main()
{
	shared_ptr<IAocSolution> Solution = make_shared<AoCSolution3>();

	Solution->Initialize(AoCHelpers::ProcessInput(3));

	const int Part2 = 2;
	cout << Solution->GetResult(Part2) << endl;

	return 0;
}
