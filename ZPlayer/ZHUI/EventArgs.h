#pragma once
#include <htmlayout.h>
#include <string>
namespace zhui
{
	template <class T>
	struct __declspec(dllexport) EventArgs
	{
		EventArgs(const HELEMENT he, const T& params)
			:el(he), params(params)
		{
			const wchar_t* data = el.get_attribute("id");
			if (NULL != data)
			{
				id = data;
			}
			data = el.get_attribute("name");
			if (NULL != data)
			{
				name = data;
			}
		}

		EventArgs(const EventArgs& eventArgs)
		{
			el = eventArgs.el;
			params = eventArgs.params;
			id = eventArgs.id;
			name = eventArgs.name;
		}

		EventArgs& operator=(const EventArgs& eventArgs)
		{
			if (this != &eventArgs)
			{
				el = eventArgs.el;
				params = eventArgs.params;
				id = eventArgs.id;
				name = eventArgs.name;
			}
			return *this;
		}
		bool IsId(const wchar_t* data)
		{
			return id == data;
		}

		bool IsName(const wchar_t* data)
		{
			return name == data;
		}

		htmlayout::dom::element el;
		T params;
		std::wstring id;
		std::wstring name;
	};

	typedef EventArgs<struct BEHAVIOR_EVENT_PARAMS> BehaviorEventArgs;
	typedef EventArgs<struct MOUSE_PARAMS> MouseEventArgs;
}