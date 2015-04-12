#pragma once
namespace CoreBridge
{
	public ref class ZWaveInfo
	{
	public:
		ZWaveInfo();
		unsigned short        wFormatTag;         /* format type */
		unsigned short        nChannels;          /* number of channels (i.e. mono, stereo...) */
		unsigned long         nSamplesPerSec;     /* sample rate */
		unsigned long		  nAvgBytesPerSec;    /* for buffer estimation */
		unsigned short        nBlockAlign;        /* block size of data */
		unsigned short        wBitsPerSample;     /* number of bits per sample of mono data */
		unsigned short        cbSize;             /* the count in bytes of the size of */

		float				  durationTime;       /* the length of the media*/
		unsigned long		  waveSize;
		float				  bitrate;
	};
}
