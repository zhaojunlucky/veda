#pragma once
#include <StringFind.h>
#include <Vector.h>
using namespace veda;

#include <iostream>
#include <string>
using namespace std;

void testStringFind(const char* str, size_t size, const char* pattern, size_t patSize)
{
	cout << str << ":" << pattern << "  " << findSubStr<char>(str, size, pattern, patSize) << endl;
}
void testStringFind()
{
	const char* str = "HERE IS A SIMPLE EXAMPLE";
	const char* pattern = "EXAMPLE";
	testStringFind(str,strlen(str),pattern,strlen(pattern));
	

	string str1 = "how old are you, this is a test for find a substring in a string";
	testStringFind(str1.c_str(), str1.size(),"how",3);
	testStringFind(str1.c_str(), str1.size(), "old", 3);
	testStringFind(str1.c_str(), str1.size(), " ", 1);
	testStringFind(str1.c_str(), str1.size(), " are", 4);
	testStringFind(str1.c_str(), str1.size(), "a", 1);
	testStringFind(str1.c_str(), str1.size(), "substring", 9);
	testStringFind(str1.c_str(), str1.size(), "string", 6);
	string sub1 = "find a substring in a string";
	testStringFind(str1.c_str(), str1.size(), sub1.c_str(), sub1.size());
	testStringFind(str1.c_str(), str1.size(), "z", 1);
}

void testStringFindAll(const char* str, size_t size, const char* pattern, size_t patSize)
{
	SubStringIndexesPtr indexes = findAllSubStr<char>(str, size, pattern, patSize);
	cout << str << ":" << pattern << ", indexes:";
	if (indexes->getLength() == 0)
	{
		cout << "not found" << endl;
	}
	else
	{
		for (auto& index : *indexes.get())
		{
			cout << index << " ";
		}
		cout << endl;
	}
}

void testStringFindAll()
{
	string str1 = "how old are you, this is a test for find a substring in a string, yes you";
	testStringFindAll(str1.c_str(), str1.size(), "z", 1);
	testStringFindAll(str1.c_str(), str1.size(), "a", 1);
	testStringFindAll(str1.c_str(), str1.size(), "you", 3);
}