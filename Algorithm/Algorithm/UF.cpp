#include "UF.h"

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
		int qCom = (*id)[q];
		int pCom = (*id)[p];

		for (auto&com : *id)
		{
			if (com == pCom)
			{
				com = qCom;
			}
		}
	}
}

bool UF::connected(int p, int q)
{
	return (*id)[p] == (*id)[q];
}
