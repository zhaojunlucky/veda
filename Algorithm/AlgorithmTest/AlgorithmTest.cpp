// AlgorithmTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Array.h>
#include <iostream>
using namespace std;
using namespace veda;
#include <UF.h>
#include <stdlib.h>
void testArrayClass();
int _tmain(int argc, _TCHAR* argv[])
{

	UF uf(10);
	cout << uf.connected(0, 1) << endl;
	uf.un(0, 1);
	cout << uf.connected(0, 1) << endl;
	uf.un(9, 1);
	cout << uf.connected(1, 9) << endl;

	system("PAUSE");
	return 0;
}

void testArrayClass()
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

	for (Array<int>::iterator it = arr.begin(); it != arr.end(); ++it)
	{
		*it = 9 - *it;
	}
	cout << endl;
	for (auto& v : arr)
	{
		cout << v << endl;
		v += 1;
	}
	cout << endl;
	for (auto& v : arr)
	{
		cout << v << endl;
	}
}
