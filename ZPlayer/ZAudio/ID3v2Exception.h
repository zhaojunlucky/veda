#pragma once
#include <exception>
using namespace std;
namespace audio
{
	namespace id3v2
	{
		class ID3v2Exception : public exception
		{
		public:
			ID3v2Exception(const char* message)
				:exception(message)
			{

			}
		};
	}
}