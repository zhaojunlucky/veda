// AlgorithmTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Array.h>
#include <iostream>
using namespace std;
using namespace veda;
#include <WeightQF.h>
#include <UF.h>
#include <CompressQF.h>
#include <stdlib.h>
#include <BinarySearch.h>
#include <Vector.h>
#include <vector>
void testArrayClass();
void testBinarySearch();
int _tmain(int argc, _TCHAR* argv[])
{
	Vector<int> test;
//	int a = test[0];
	CompressQF uf(10);
	cout << uf.connected(0, 1) << endl;
	uf.un(0, 1);
	cout << uf.connected(0, 1) << endl;
	uf.un(9, 1);
	cout << uf.connected(1, 9) << endl;
	testBinarySearch();
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

void testBinarySearch()
{
	Array<int> arr(10);
	for (int i = 0; i < arr.length(); i++)
	{
		arr[i] = i;
		cout << i << " ";
	}
	cout << endl;
	int index = binarySearch(arr, 5);
	cout << 5 << ":" << index << endl;

	index = binarySearch(arr, 9);
	cout << 9 << ":" << index << endl;
}