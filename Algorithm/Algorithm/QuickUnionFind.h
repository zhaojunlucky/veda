#pragma once
#include <memory>
using namespace std;

#include "Array.h"
class QuickUnionFind
{
public:
	QuickUnionFind(int n);
	~QuickUnionFind();

	void un(int a, int b);
	int find(int a);
private:
	unique_ptr<Array<int>> id;
};

