#pragma once
#include "QF.h"
#include "Array.h"
#include <memory>
class WeightQF : public QF
{
public:
	WeightQF(int n);
	~WeightQF();

	virtual void un(int p, int q);

protected:
	std::unique_ptr<veda::Array<int>> size;
};

