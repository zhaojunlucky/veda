#pragma once
#include <vector>
#include <functional>
#include <string>

namespace zhui
{
	template <class T>
	class __declspec(dllexport) Event
	{
	public:
		Event()
			:isNull(true)
		{

		}
		virtual ~Event()
		{

		}

		Event& operator=(const std::function<T>& func)
		{
			mFunc = func;
			isNull = false;
			return *this;
		}

		void Remove()
		{
			isNull = true;
		}
		bool IsNull()
		{
			return isNull;
		}
	public:
		std::function<T> mFunc;
	private:
		bool isNull;
	};

}

