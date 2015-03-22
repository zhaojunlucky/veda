#pragma once 
#include "veda.h"
#include "EventArgs.h"
#include "Object.h"
namespace veda
{
	//template<class _Sender, class _Args> 
	class __Event : public Object
	{
	public:
		__event void trigger(Object* sender, EventArgs* args);

		void fire(Object* sender, EventArgs* args)
		{
			__raise this->trigger(sender, args);
		}
	};

//#define hook(source,r) __hook(&__Event::trigger, source, r);
}