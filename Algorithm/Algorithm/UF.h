#pragma once
#include <memory>
#include <algorithm>
using namespace std;

#include "Array.h"
class UF
{
public:

	UF(int n);
	~UF();

	void un(int p, int q);
	bool connected(int p, int q);
private:
	unique_ptr<veda::Array<int>> id;
};

