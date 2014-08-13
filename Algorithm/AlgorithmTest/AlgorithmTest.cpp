// AlgorithmTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Array.h>
#include <iostream>

#include <WeightQF.h>
#include <UF.h>
#include <CompressQF.h>
#include <stdlib.h>
#include <BinarySearch.h>
#include <Vector.h>
#include <vector>
#include <Prime.h>
#include <functional>
#include <Queue.h>
#include <queue>

using namespace std;
using namespace veda;

void testArrayClass();
void testBinarySearch();
int _tmain(int argc, _TCHAR* argv[])
{
	ArrayQueue < int> q(10);
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	cout << "queue:"<< q.dequeue() << endl;

	Vector<int> test;
	test.add(1);
	test.add(2);
	test.add(3);
	test.add(4);
	test.add(5);
	
	for (Vector<int>::const_iterator it = test.cbegin(); it != test.cend(); ++it)
	{
		cout << *it << " " ;
	}

	cout << endl;

	for (Vector<int>::iterator it = test.begin(); it != test.end(); ++it)
	{
		++(*it);
	}

	for (auto& v : test)
	{
		cout << v << " ";
	}
	cout << endl;

	CompressQF uf(10);
	cout << uf.connected(0, 1) << endl;
	uf.un(0, 1);
	cout << uf.connected(0, 1) << endl;
	uf.un(9, 1);
	cout << uf.connected(1, 9) << endl;
	testBinarySearch();

	cout << "29 is prime " << veda::isPrime(29) << endl;

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