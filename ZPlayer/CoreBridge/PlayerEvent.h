#pragma once
#include "Core.h"
namespace CoreBridge
{
	public delegate void onPlay();
	public delegate void onPause();
	public delegate void onStop();
	public delegate void onUserStop();
	public delegate void onResume();
	public delegate void onFileOpen();
	public delegate void onMute(bool mute);
	public delegate void onVolume();
	public delegate void onSeek();
}