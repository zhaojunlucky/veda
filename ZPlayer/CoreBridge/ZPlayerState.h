#pragma once
namespace CoreBridge
{
	public ref class ZPlayerState
	{
	public:
		ZPlayerState();

		bool isPlaying;
		bool isPause;
		bool isStop;
		bool isMute;
		int volume;
	};
}
