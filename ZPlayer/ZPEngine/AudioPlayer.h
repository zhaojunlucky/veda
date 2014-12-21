#pragma once
#include "AudioBuffer.h"
#include <Decoder.h>
#include <xAudio2.h>
#include "PlayerBase.h"

namespace audio
{
	namespace player
	{
		class __declspec(dllexport) AudioPlayer
		{
		public:
			AudioPlayer();
			virtual ~AudioPlayer();

			int Open(Decoder* decoder);
			int Play();
			int Play(float start, float end);
			int Pause();
			int Resume();
			int Stop();
			// seek and play
			int Seek(float duration);
			float GetPlayDuration() const;
			int SetVolumne(int vol);
			int SetMute(bool mute);
			int SetCallback(ZACallbackFunction func,void* para);

			const WaveInfo& GetWaveInfo() const;
			const PlayerState& GetPlayerState() const;
			float getCurrentPlayStart() const;
		private:
			void InitAudio2();
			void CleanupAudio();
			static int WINAPI PlayerThread(void* lpdwParam);
			void Callback(PlayerStateMessage message, WPARAM wp = 0, LPARAM lp = 0);

		private:
			struct Audio2 mAudio2;
			XAUDIO2_DEVICE_DETAILS mDetails;
			Decoder* mDecoder;
			std::shared_ptr<AudioBuffer<BYTE>> mBuffers;
			struct PlayerState mPlayerState;
			struct PlayControl mPlayControl;
			struct Callback mCallback;
			HANDLE mThread;
			DWORD mThreadId;
		};
	}
}


