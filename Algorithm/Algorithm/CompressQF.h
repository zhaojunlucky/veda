#pragma once
#include "WeightQF.h"
class CompressQF : public WeightQF
{
public:
	CompressQF(int n);
	~CompressQF();

protected:
	virtual int root(int p);
};

