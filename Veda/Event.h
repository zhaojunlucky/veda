#pragma once
#include <functional>
#include "veda.h"
#include "EventArgs.h"
#include "Object.h"

namespace veda
{
	template <typename E>
	class VEDA_EXPORT Event
	{
	public:
		void attach (std::function<E>&& func)
		{
			mFunc = std::move(func);
		}
		void detach()
		{
			mFunc.swap();
		}

		Event& operator+=(std::function<E>&& func)
		{
			mFunc = std::move(func);
			return *this;
		}

		Event& operator-=(std::function<E>&& func)
		{
			mFunc.swap();
			return *this;
		}

		std::function < E >& operator()()
		{
			return mFunc;
		}
	private:
		std::function < E > mFunc;
	};

	typedef Event<void(Object*, EventArgs*)> VEvent;
#define VEBind(x,y) std::bind((x),(y),std::placeholders::_1,std::placeholders::_2)
}