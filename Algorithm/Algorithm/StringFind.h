#pragma once
#include <hash_map>
#include <memory>
#include "Vector.h"
#include "MathBasic.h"

namespace veda
{
#ifndef NPOS
#define  NPOS  (size_t)(-1)
#endif
	// Boyer-Moore algorithm
	// http://www-igm.univ-mlv.fr/~lecroq/string/node14.html
	// http://www.ruanyifeng.com/blog/2013/05/boyer-moore_string_search_algorithm.html
	template<class value_type>
	size_t find(const value_type* str, size_t strSize, const value_type* pattern, size_t patSize);

	template<class value_type>
	std::shared_ptr<Vector<size_t>> find(const value_type* str, size_t strSize, const value_type* pattern, size_t patSize);
}


