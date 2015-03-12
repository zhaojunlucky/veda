#pragma once
#include "AssertException.h"

namespace veda
{
	
	template <class T>
	/*
	T must be char type or wchar_t type
	*/
	class Assert
	{
		
	public:
		typedef AssertException<T> _AssertException;
		//throw AssertException<T>
		void isTrue(bool expression, const T* errMessage) 
		{
			if (!expression && errMessage)
			{
				throw _AssertException(errMessage);
			}
		}
	};


}


