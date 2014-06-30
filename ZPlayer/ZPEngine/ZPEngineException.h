#pragma once
#include <exception>

namespace audio
{
	namespace player
	{
		class __declspec(dllexport) ZPEngineException : public std::exception
		{
		public:
			ZPEngineException(const char* message)
				:std::exception(message)
			{

			}

			virtual ~ZPEngineException()
			{

			}
		};
	}
}