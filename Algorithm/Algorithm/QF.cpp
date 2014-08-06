#include "QF.h"


QF::QF(int n)
{
	id.reset(new veda::Array<int>(n));
	for (int i = 0; i < n; i++)
	{
		(*id)[i] = i;
	}
}


QF::~QF()
{
}


void QF::un(int p, int q)
{
	int rp = root(p);
	int rq = root(q);
	if (rp != rq)
	{
		(*id)[rp] = rq;
	}
}

bool QF::connected(int p, int q)
{
	return root(q) == root(p);
}

int QF::root(int p)
{
	while ((*id)[p] != p)
	{
		p = (*id)[p];
	}

	return p;
}
