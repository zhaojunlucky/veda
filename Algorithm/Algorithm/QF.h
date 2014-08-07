#pragma once
#include "Array.h"
#include <memory>

class QF
{
public:
	QF(int n);
	~QF();

	virtual bool connected(int p, int q);
	virtual void un(int p, int q);
protected:
	virtual int root(int p);
protected:
	std::unique_ptr<veda::Array<int>> id;
};

