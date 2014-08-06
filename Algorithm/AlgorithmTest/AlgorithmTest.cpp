// AlgorithmTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Array.h>
#include <iostream>
using namespace std;
using namespace veda;
#include <stdlib.h>
int _tmain(int argc, _TCHAR* argv[])
{
	Array<int> arr(10);
	for (int i = 0; i < arr.length(); i++)
	{
		arr[i] = i;
	}
	for (Array<int>::const_iterator it = arr.cbegin(); it != arr.cend(); ++it)
	{
		cout << *it << endl; 
	}


	system("PAUSE");
	return 0;
}

