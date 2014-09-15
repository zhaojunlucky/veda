// testProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <ZString.h>
using namespace veda;
#pragma comment(lib, "Veda.lib")
#include <iostream>
using namespace std;

void testStringConstructor();
void testOperator();
void testOthers();

 
int _tmain(int argc, _TCHAR* argv[])
{
	String str;
	wstring ws;
	testStringConstructor();
	testOperator();
	testOthers();
	system("PAUSE");
	return 0;
}

void testStringConstructor()
{
	wcout << L"constructor test:" << endl;
	String iStr(-5);
	wcout <<L"String(int):" << iStr << endl;
	String uiStr((unsigned int)5);
	wcout << L"String(unsigned int):" << uiStr << endl;

	String sStr((short)-5);
	wcout << L"String(short):" << sStr << endl;
	String usStr((unsigned short)5);
	wcout << L"String(unsigned short):" << usStr << endl;

	wchar_t c = 'c';
	String cStr(c);
	wcout << L"String(char):" << cStr << endl;
	String ucStr((unsigned char)c);
	wcout << L"String(unsigned char):" << ucStr << endl;

	String i64Str((__int64)-5);
	wcout << L"String(__int64):" << i64Str << endl;
	String ui64Str((unsigned __int64)5);
	wcout << L"String(unsigned __int64):" << ui64Str << endl;

	String lStr((long)-5);
	wcout << L"String(long):" << lStr << endl;
	String ulStr((unsigned long)5);
	wcout << L"String(unsigned long):" << ulStr << endl;

	String fStr(8.909f);
	wcout << L"String(float):" << fStr << endl;

	String dStr(9.909f);
	wcout << L"String(double):" << dStr << endl;

	String ldStr((long double)9999.888);
	wcout << L"String(long double):" << ldStr << endl;

	tchar* p = _T("test");
	String pStr(p);
	wcout << L"String(const tchar*):" << pStr << endl;

	String tmp = _T("test test  ddddddddddddddddfwefsfdsdfsfsfsdfsfdsdfsddddddddddddddddddddddddddddddd");
	wcout << "address:" << (int)&tmp[0]<<endl;

	String ppStr(tmp);
	wcout << L"String(const String&):" << ppStr << endl;

	String pppStr(std::move(tmp));
	wcout << "address:" << (int)&pppStr[0] << endl;
	wcout << L"String(const String&&):" << pppStr << endl;
}

void testOperator()
{
	wcout << L"test operator:" << endl;

	String tmp = L"12wd3cr23yr728cry28c7nr72cnyr23787y3r7cy2873yrc827ryc8273yrc823ryc273cr2";

	String strAss = tmp;
	wcout << L"operator =(const String&):" << strAss << endl;

	String iAss = 9;
	wcout << L"operator =(int):" << iAss << endl;
	String uiAss = (unsigned int)9;
	wcout << L"operator =(unsigned int):" << uiAss << endl;

	String sAss = (short)9;
	wcout << L"operator =(short):" << sAss << endl;
	String usAss = (unsigned short)9;
	wcout << L"operator =(unsigned short):" << sAss << endl;

	String i64Ass = (__int64)9;
	wcout << L"operator =(__int64):" << i64Ass << endl;
	String ui64Ass = (unsigned __int64)9;
	wcout << L"operator =(unsigned __int64):" << ui64Ass << endl;

	String lAss = (long)9;
	wcout << L"operator =(long):" << lAss << endl;
	String ulAss = (unsigned long)9;
	wcout << L"operator =(unsigned long):" << ulAss << endl;

	String fAss = 9.78787f;
	wcout << L"operator =(float):" << fAss << endl;
	String dAss = 9.78787;
	wcout << L"operator =(double):" << dAss << endl;
	String ldAss = (long double)9.78787;
	wcout << L"operator =(long double):" << ldAss << endl;

	wchar_t c = 'z';
	String cAss = c;
	wcout << L"operator =(tchar):" << cAss << endl;
	
	String ccAss = (const tchar*)tmp;
	wcout << L"operator =(const tchar*):" << ccAss << endl;

	wcout << L"address:" << (int)&tmp[0]<< endl;
	String mAss(std::move(tmp));
	wcout << L"address:" << (int)&mAss[0]<< endl;
	wcout << L"operator = (const String&&):" << mAss << endl;

	String s = L"s";

	s += 1;
	s += (unsigned int)2;
	s += (short)3;
	s += (unsigned short)4;
	s += (long)5;
	s += (unsigned long)6;
	s += (__int64)7;
	s += (unsigned __int64)8;
	wcout << L"operator += (int,unsigned int,short, unsigned short, long,unsigned long,__int64,unsigned __int64):" << s << endl;
	
	wchar_t space = ' ';
	s += 0.8999f;
	s += space;
	s += 9.9900;
	s += L" ";
	s += (long double)8.888809;
	wcout << L"operator += (tchar,tchar*, float, double,long double):" << s << endl;


}

void testOthers()
{
	String tmp = L"  spacespace    ";
	wcout << L"trim:[" << tmp.trim()->getData()<<L"]" << endl;
	wcout << L"trimLeft:[" << tmp.trimLeft()->getData() << L"]" << endl;
	wcout << L"trimRight:[" << tmp.trimRight()->getData() << L"]" << endl;

	wcout << L"find:" << tmp.find((wchar_t)'c') << endl;
	wcout << L"find:" << tmp.find((wchar_t)'c', 7) << endl;
	size_t pos = tmp.find((wchar_t)'z');
	wcout << L"find:" << pos << endl;

	String str1 = L"dd";
	String str2 = L"Dd";
	wcout << str1.equals(str2) << endl;
	wcout << str1.equalsIgnoreCase(str2) << endl;

	wcout << tmp << ",space," << tmp.find(L"space") << endl;
	wcout << tmp << ",spacez," << tmp.find(L"spacez") << endl;
}