#pragma once
#include "AssertException.h"

namespace veda
{
	
	template <class T = wchar_t>
	/*
	T must be char type or wchar_t type
	*/
	class Assert
	{
	public:
		static void isTrue(bool expression, const T* errMessage) //throw AssertException<T>
		{
			if (!expression && errMessage)
			{
				throw AssertException<T>(errMessage);
			}
		}
	};


}


