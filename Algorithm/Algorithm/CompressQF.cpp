#include "CompressQF.h"


CompressQF::CompressQF(int n)
	:WeightQF(n)
{
}


CompressQF::~CompressQF()
{
}

int CompressQF::root(int p)
{
	while (p != id->at(p))
	{
		id->at(p) = id->at(id->at(p));
		p = id->at(p);
	}
	return p;
}
