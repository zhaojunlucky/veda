// AlgorithmTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;
#include "testSort.h"
#include "testStringFind.h"
#include <Vector.h>

int _tmain(int argc, _TCHAR* argv[])
{
	/*veda::Vector<int> test;
	test.add(1);
	test.add(2);

	test.add(3, 0);
	test.add(4, 1);

	for (auto i : test)
	{
		printf("%d ",i);
	}
	printf("\n");
	testSelection();
	testInsertion();
	testShell();
	testShuffle();
	testMergeSort();

	testStringFind();
	testStringFindAll();
	cout << "Reverse find testing" << endl;
	testStringRFind();
	testStringRFindAll();*/

	testHeapSort();

	system("PAUSE");
	return 0;
}

