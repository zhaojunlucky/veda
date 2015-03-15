#pragma once
#include <iostream>
using namespace std;

template< class ...T>
void varSize(T... args)
{
	wcout << "variable template arguments size:"
		<< sizeof... (args) << endl;
}

// assume template type is wchar_t*
template <class T>
void print(T v)
{
	wcout << v << L" ";
}
template <class T, class ..._Types>
void print(T first, _Types ... rest)
{
	wcout << first << " ";
	print(rest...);
}


void print2()
{
	wcout << endl;
}

template <class T, class ..._Types>
void print2(T first, _Types ...rest)
{
	wcout << first << L" ";
	print2(rest...);
}
