#include "StringFind.h"

namespace veda
{
	template<class value_type>
	static void buildBadCharTable(const value_type* str, size_t strSize, const value_type* pattern, size_t patSize, std::hash_map<value_type, size_t> &badCharTable)
	{

	}

	template<class value_type>
	static void buildGoodSuffixTable(const value_type* pattern, size_t patSize, std::hash_map<size_t, size_t> &goodSuffixTable)
	{

	}

	template<class value_type>
	static size_t compare(const value_type* str,size_t start, const value_type* pattern, size_t patSize)
	{
		size_t i = 1;
		while (i <= patSize && str[start + patSize - i] == pattern[patSize - i])
		{
			i++;
		}
		return patSize - i + 1;
	}

	template<class value_type>
	static size_t calcBadCharMoveStep()
	{

	}

	template<class value_type>
	static size_t calcGoodSuffixMoveStep()
	{

	}

	template<class value_type>
	size_t find(const value_type* str, size_t strSize, const value_type* pattern, size_t patSize)
	{
		if (strSize >= patSize)
		{
			std::hash_map<value_type, size_t> badCharTable;
			std::hash_map<size_t, size_t> goodSuffixTable;
			buildBadCharTable(str, strSize, pattern, patSize, badCharTable);
			buildGoodSuffixTable(pattern, patSize, goodSuffixTable);

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
					auto moveStep = maxValue<size_t>(calcBadCharMoveStep(), calcGoodSuffixMoveStep());



				}
			}
		}
		else
		{
			return NPOS;
		}
	}
}