#pragma once
#include "Array.h"
#include <memory>

class QF
{
public:
	QF(int n);
	~QF();

	bool connected(int p, int q);
	void un(int p, int q);
private:
	int root(int p);
private:
	std::unique_ptr<veda::Array<int>> id;
};

