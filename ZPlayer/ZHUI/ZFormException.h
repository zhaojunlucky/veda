#pragma once
#include <exception>
namespace zhui
{
	class __declspec(dllexport) ZFormException : public std::exception
	{
	public:
		ZFormException(const char* message);
		virtual ~ZFormException();
	};
}


