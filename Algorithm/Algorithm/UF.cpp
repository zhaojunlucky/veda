#include "UF.h"
#include <vector>

UF::UF(int n)
{
	id.reset(new veda::Array<int>(n));
	for (int i = 0; i < n; i++)
	{
		(*id)[i] = i;
	}
}


UF::~UF()
{
}

void UF::un(int p, int q)
{
	if (!connected(p, q))
	{
		

	}
}

bool UF::connected(int p, int q)
{
	return (*id)[p] == (*id)[q];
}
