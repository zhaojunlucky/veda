#pragma once

#include <Array.h>
#include <Sort.h>
#include <Random.h>
#include <MergeSort.h>
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
	selection(arr, 0, arr.length());
	cout << "check sort:" << (check(arr, 0, arr.length()) ? "true" : "false") << endl;
	output(arr);
}

void testInsertion()
{
	Array<int> arr(10);
	randomData(arr);
	cout << "insertion:" << endl;
	output(arr);
	insertion(arr, 0, arr.length());
	cout << "check sort:" << (check(arr, 0, arr.length()) ? "true" : "false") << endl;
	output(arr);
}

void testShell()
{
	Array<int> arr(10);
	randomData(arr);
	cout << "shell:" << endl;
	output(arr);
	shell(arr, 0, arr.length());
	cout << "check sort:" << (check(arr, 0, arr.length()) ? "true" : "false") << endl;
	output(arr);
}

void testShuffle()
{
	Array<int> arr(10);
	for (size_t i = 0; i < arr.length();i++)
	{
		arr[i] = (int)i;
	}
	cout << "shuffle:" << endl;
	output(arr);
	shuffle(arr,arr.length());
	output(arr);
}

void testMergeSort()
{
	Array<int> arr(10);
	randomData(arr);
	cout << "merge:" << endl;
	output(arr);
	mergeSort(arr, 0, arr.length());
	cout << "check sort:" << (check(arr, 0, arr.length()) ? "true" : "false") << endl;
	output(arr);
}

void testHeapSort()
{
	Array<int> arr(10);
	randomData(arr);
	cout << "heap:" << endl;
	output(arr);
	heapSort(arr, 0, arr.length());
	cout << "heap sort:" << (check(arr, 0, arr.length()) ? "true" : "false") << endl;
	output(arr);
}