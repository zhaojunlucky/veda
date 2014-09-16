#pragma once
#include <hash_map>
#include <memory>
#include "Vector.h"
#include "MathBasic.h"
#include "BoyerMoore.h"

namespace veda
{

	// Boyer-Moore algorithm
	// http://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string_search_algorithm
	// http://www-igm.univ-mlv.fr/~lecroq/string/node14.html
	// http://www.ruanyifeng.com/blog/2013/05/boyer-moore_string_search_algorithm.html
	template<class value_type>
	size_t findSubStr(const value_type* str, size_t strSize, const value_type* pattern, size_t patSize)
	{
		ArrayVisitor<value_type> src(str, strSize);
		ArrayVisitor<value_type> pat(pattern, patSize);
		return findBM(src, strSize, pat, patSize);
	}

	template<class value_type>
	size_t rfindSubStr(const value_type* str, size_t strSize, const value_type* pattern, size_t patSize)
	{
		ReverseArrayVisitor<value_type> src(str, strSize);
		ReverseArrayVisitor<value_type> pat(pattern, patSize);
		size_t index = findBM(src, strSize, pat, patSize);
		if (index != NPOS)
		{
			index = strSize - index - patSize;
		}
		return index;
	}

	template<class value_type>
	SubStringIndexesPtr findAllSubStr(const value_type* str, size_t strSize, const value_type* pattern, size_t patSize)
	{
		ArrayVisitor<value_type> src(str, strSize);
		ArrayVisitor<value_type> pat(pattern, patSize);
		return findAllSubStrBM(src, strSize, pat, patSize);
	}

	template<class value_type>
	SubStringIndexesPtr rfindAllSubStr(const value_type* str, size_t strSize, const value_type* pattern, size_t patSize)
	{
		ReverseArrayVisitor<value_type> src(str, strSize);
		ReverseArrayVisitor<value_type> pat(pattern, patSize);
		SubStringIndexesPtr ptr = findAllSubStrBM(src, strSize, pat, patSize);
		for (auto& index : *ptr.get())
		{
			index = strSize - index - patSize;
		}
		return ptr;
	}
}


