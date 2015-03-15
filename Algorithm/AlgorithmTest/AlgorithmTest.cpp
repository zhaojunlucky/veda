// AlgorithmTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;
#include "testSort.h"
#include "testStringFind.h"
#include <Vector.h>
#include <Asserts.h>
#include <iostream>
#include <VarTemplate.h>

int _tmain(int argc, _TCHAR* argv[])
{
	std::wcout.imbue(locale(locale(), "", LC_CTYPE));
	varSize(L"hello", L"world", L"!");
	std::cout << "print1:" << endl;
	print(L"hello", L"world", L"!");
	std::cout << endl;
	
	std::cout << "print2:"<<endl;
	print2(L"hello", L"world", L"!");
	try
	{
		veda::Assert<wchar_t> assert;
		assert.isTrue(false, L"error≤‚ ‘ message");
	}
	catch (veda::Assert<wchar_t>::_AssertException & e)
	{
		std::wcout << L"¥ÌŒÛ≤‚ ‘£∫" << e.getMessage() << std::endl;
		std::wcout << std::endl;
	}
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

