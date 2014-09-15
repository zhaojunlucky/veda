// AlgorithmTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;
#include "testSort.h"
#include "testStringFind.h"

int _tmain(int argc, _TCHAR* argv[])
{
	testSelection();
	testInsertion();
	testShell();
	testShuffle();
	testMergeSort();

	testStringFind();
	testStringFindAll();

	system("PAUSE");
	return 0;
}

