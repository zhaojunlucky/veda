#pragma once
#include <memory>
#include "Vector.h"

namespace veda
{
#ifndef NPOS
#define  NPOS  (size_t)(-1)
#endif
	typedef std::shared_ptr<Vector<size_t>> SubStringIndexesPtr;

	template<class value_type>
	static void buildBadCharTable(const value_type* str, size_t strSize, const value_type* pattern, size_t patSize, std::hash_map<value_type, size_t> &badCharTable)
	{
		size_t i = patSize - 1;
		while (i >= 1)
		{
			badCharTable[pattern[i]] = i;
			--i;
		}
		badCharTable[pattern[0]] = 0;
	}

	template<class value_type>
	static void buildGoodSuffixTable(const value_type* pattern, size_t patSize, std::hash_map<size_t, size_t> &goodSuffixTable)
	{
		value_type c = pattern[patSize - 1];
		for (auto i = 1; i < patSize; i++)
		{
			for (auto j = 0; j < patSize - i; j++)
			{
				if (pattern[j] == c)
				{
					goodSuffixTable[i] = j;
					break;
				}
			}
		}
	}

	template<class value_type>
	static size_t compare(const value_type* str, size_t start, const value_type* pattern, size_t patSize)
	{
		size_t i = 1;
		while (i <= patSize && str[start + patSize - i] == pattern[patSize - i])
		{
			i++;
		}
		return i - 1;
	}

	template<class value_type>
	static size_t calcBadCharMoveStep(value_type c, size_t index, std::hash_map<value_type, size_t>& badCharTable)
	{
		auto it = badCharTable.find(c);
		return index - (it == badCharTable.end() ? -1 : (it->second));
	}

	template<class value_type>
	static size_t calcGoodSuffixMoveStep(size_t patIndex, size_t suffixSize, std::hash_map<size_t, size_t>& goodSuffixTable)
	{
		if (suffixSize > 0)
		{
			auto it = goodSuffixTable.find(suffixSize);
			return patIndex - (it == goodSuffixTable.end() ? -1 : (it->second));
		}
		else
		{
			return 0;
		}
	}

	template<class value_type>
	size_t findBM(const value_type* str, size_t strSize, const value_type* pattern, size_t patSize)
	{
		if (strSize >= patSize)
		{
			std::hash_map<value_type, size_t> badCharTable;
			std::hash_map<size_t, size_t> goodSuffixTable;
			buildBadCharTable(str, strSize, pattern, patSize, badCharTable);
			buildGoodSuffixTable(pattern, patSize, goodSuffixTable);
			auto goodSuffixIndex = patSize - 1;
			size_t start = 0;
			size_t ret;
			while (start <= strSize - patSize)
			{
				ret = compare(str, start, pattern, patSize);
				// find
				if (ret == patSize)
				{
					return start;
				}
				else
				{
					auto suffixSize = ret;
					auto strIndex = start + (patSize - ret - 1);
					auto c = str[strIndex];
					auto patIndex = patSize - ret - 1;
					auto bad = calcBadCharMoveStep<value_type>(c, patIndex, badCharTable);
					auto good = calcGoodSuffixMoveStep<value_type>(goodSuffixIndex, suffixSize, goodSuffixTable);
					auto moveStep = maxValue<size_t>(bad,good);
					start += moveStep;
				}
			}
		}
		return NPOS;
	}

	template<class value_type>
	SubStringIndexesPtr findAllSubStrBM(const value_type* str, size_t strSize, const value_type* pattern, size_t patSize)
	{
		SubStringIndexesPtr poss = std::make_shared<Vector<size_t>>();
		if (strSize >= patSize)
		{
			std::hash_map<value_type, size_t> badCharTable;
			std::hash_map<size_t, size_t> goodSuffixTable;
			buildBadCharTable(str, strSize, pattern, patSize, badCharTable);
			buildGoodSuffixTable(pattern, patSize, goodSuffixTable);
			auto goodSuffixIndex = patSize - 1;
			size_t start = 0;
			size_t ret;
			while (start <= strSize - patSize)
			{
				ret = compare(str, start, pattern, patSize);
				// find
				if (ret == patSize)
				{
					poss->add(start);
					start += patSize;
				}
				else
				{
					auto suffixSize = ret;
					auto strIndex = start + (patSize - ret - 1);
					auto c = str[strIndex];
					auto patIndex = patSize - ret - 1;
					auto bad = calcBadCharMoveStep<value_type>(c, patIndex, badCharTable);
					auto good = calcGoodSuffixMoveStep<value_type>(goodSuffixIndex, suffixSize, goodSuffixTable);
					auto moveStep = maxValue<size_t>(bad, good);
					start += moveStep;
				}
			}
		}
		return poss;
	}
}