#include "QuickUnionFind.h"


QuickUnionFind::QuickUnionFind(int n)
{
	id.reset(new Array<int>(n));
	for (int i = 0; i < n; i++)
	{
		(*id)[i] = i;
	}
}


QuickUnionFind::~QuickUnionFind()
{
}
