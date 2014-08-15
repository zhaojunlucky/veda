#pragma once

#include <Array.h>
#include <Sort.h>
#include <Random.h>
using namespace veda;
#include <iostream>
using namespace std;

void randomData(Array<int>& arr)
{
	Random r; 
	for (auto& v : arr)
	{
		v = r.randomInt();
	}
}
void output(Array<int>& arr)
{
	for (auto& v : arr)
	{
		cout << v << " ";
	}
	cout << endl;
}
void testSelection()
{
	Array<int> arr(10);
	randomData(arr);
	cout << "selection:" << endl;
	output(arr);
	selection(arr, (size_t)0, arr.length());
	output(arr);
}

void testInsertion()
{
	Array<int> arr(10);
	randomData(arr);
	cout << "insertion:" << endl;
	output(arr);
	insertion(arr, (size_t)0, arr.length());
	output(arr);
}