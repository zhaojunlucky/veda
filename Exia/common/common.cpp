// common.cpp : Defines the entry point for the console application.
//

#include "FileWriter.hpp"
#include <string>

int main(int argc, char* argv[])
{
	eio::WFileWriter file("c:/users/i076777/desktop/1.txt");
	std::wstring tmp = L"qqqq≤‚ ‘";
	file.Write(tmp.c_str(),tmp.size());
	file.close();
	return 0;
}

