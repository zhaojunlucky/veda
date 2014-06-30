#pragma once
#include <Windows.h>
#include <Mmsystem.h>
#include <Exia\common\StringConvertInternal.hpp>


namespace audio
{
	enum AudioFormat
	{
		Wav,
		Flac,
		Ape,
		MP3,
		Unknown
	};
	//typedef struct WAVEFORMATEX
	//{
	//	WORD        wFormatTag;         /* format type */
	//	WORD        nChannels;          /* number of channels (i.e. mono, stereo...) */
	//	DWORD       nSamplesPerSec;     /* sample rate */
	//	DWORD       nAvgBytesPerSec;    /* for buffer estimation */
	//	WORD        nBlockAlign;        /* block size of data */
	//	WORD        wBitsPerSample;     /* number of bits per sample of mono data */
	//	WORD        cbSize;             /* the count in bytes of the size of */
	//}WAVEFORMATEX;

	enum AudioError
	{
		Ok,
		FailToOpenFile,
		InvalidParameter,
		FailToSeek,
		FailToReset,
		FailToRead,
		FailToInitialized,
		FileNotInitialized,
		FailToInitializeAudioLibrary,
		FailToGetWaveInfo,
		SeekDurationOutOfRange,
		FailToAllocateMemory,
		FailToDecodeData,
		UnrecognizedFileFormat
	};
	typedef struct WaveInfo
	{
		WAVEFORMATEX waveFormatex;
		float		durationTime;       /* the length of the media*/
		DWORD		waveSize;
		float		bitrate;
	}WaveInfo;

}

