#include "WeightQF.h"


WeightQF::WeightQF(int n)
	:QF(n)
{
	size.reset(new veda::Array<int>(n));
	for (int i = 0; i < n; i++)
	{
		(*id)[i] = i;
		(*size)[i] = 1;
	}
}


WeightQF::~WeightQF()
{
}

void WeightQF::un(int p, int q)
{
	auto pr = root(p);
	auto qr = root(q);
	if (pr != qr)
	{
		if (size->at(pr) > size->at(qr))
		{
			size->at(pr) += size->at(qr);
			id->at(qr) = pr;
		}
		else
		{
			size->at(qr) += size->at(pr);
			id->at(pr) = qr;
		}
	}
}