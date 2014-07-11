#pragma once
namespace audio
{
	namespace id3v2
	{
#define GetBit(value, pos) ( (value >> pos) & 0x01)
#define BigEndian2UInt(sizePtr) (((sizePtr[0] & 0x7F) << 21) | ((sizePtr[1] & 0x7F) << 14) | ((sizePtr[2] & 0x7F) << 7) | (sizePtr[3] & 0x7F))
		static const char* ID3 = "ID3";


	}
}