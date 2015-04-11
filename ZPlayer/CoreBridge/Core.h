#pragma once
#include <AudioPlayer.h>
#include <vcclr.h>
using namespace audio;
using namespace audio::player;
using namespace System;
using namespace System::Runtime::InteropServices;

namespace CoreBridge
{
#pragma unmanaged
	public delegate void InvokePlayerCallback(void* instance, PlayerStateMessage mes, void *client, WPARAM w, LPARAM l);


}