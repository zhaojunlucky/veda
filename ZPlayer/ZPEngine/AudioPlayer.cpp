#include "stdafx.h"
#include "AudioPlayer.h"
#include "ZPEngineException.h"
#include "VoiceCallback.h"

namespace audio
{
	namespace player
	{
		AudioPlayer::AudioPlayer()
		{
			mBuffers.reset(new AudioBuffer<BYTE>(MAX_BUFFER_COUNT, STREAMING_BUFFER_SIZE));
			CoInitializeEx(NULL, COINIT_MULTITHREADED);
			InitAudio2();
		}


		AudioPlayer::~AudioPlayer()
		{
			if (!mPlayerState.isStop)
			{
				Stop();
			}
			CleanupAudio();
			CoUninitialize();
		}


		int AudioPlayer::Open(Decoder* decoder)
		{
			Stop();
			mDecoder = decoder;


			if (!mDecoder)
			{
				return PlayerError::InvalidDecoder;
			}
			mPlayControl.startSec = 0;
			mPlayControl.endSec = mDecoder->getWaveInfo().durationTime;
			return 0;
		}
		int AudioPlayer::Play()
		{
			if (mPlayerState.isPlaying)
			{
				Stop();
			}
			mPlayControl.start = mDecoder->CalcaulateWaveSize(mPlayControl.startSec);
			mPlayControl.end = mDecoder->CalcaulateWaveSize(mPlayControl.endSec);

			// play
			mThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)PlayerThread, (void *)this, 0, &mThreadId);
			if (NULL == mThread)
			{
				return -2;
			}
			mPlayerState.isPlaying = true;
			mPlayerState.isStop = false;
			return 0;
		}

		int AudioPlayer::Play(float start, float end)
		{
			if (start >= end || end > mDecoder->getWaveInfo().durationTime)
			{
				return PlayerError::InvalidPlayTime;
			}
			mPlayControl.startSec = start;
			mPlayControl.endSec = end;
			return Play();
		}
		int AudioPlayer::Pause()
		{
			if (!mAudio2.bInitialized || !mPlayerState.isPlaying)
			{
				return -1;
			}
			if (mPlayerState.isPause)
			{
				return 0;
			}
			mAudio2.pXAudio2->StopEngine();
			mPlayerState.isPause = true;
			Callback(PlayerStateMessage::Pause);
			return 0;
		}
		int AudioPlayer::Resume()
		{
			if (!mPlayerState.isPause)
			{
				return -1;
			}
			mAudio2.pXAudio2->StartEngine();
			mPlayerState.isPause = false;
			return 0;
		}
		int AudioPlayer::Stop()
		{
			if (!mAudio2.bInitialized || mPlayerState.isStop)
				return -1;

			if (mPlayerState.isPause)
			{
				mAudio2.pSourceVoice->SetVolume(0);
				mAudio2.pXAudio2->StartEngine();
			}
			mPlayerState.isPause = false;
			mPlayerState.isPlaying = false;
			WaitForSingleObject(mThread, INFINITE);
			if (mThread)
				CloseHandle(mThread);
			mThread = 0;

			mPlayerState.isStop = true;
			return 0;
		}
		int AudioPlayer::Seek(float duration)
		{
			if (duration < mPlayControl.startSec || duration > mPlayControl.endSec)
				return -2;
			if (mPlayerState.isPlaying)
				Stop();
			if (0 != mDecoder->Seek(duration))
				return -1;
			Play();
			return 0;
		}
		float AudioPlayer::GetPlayDuration() const
		{
			return mDecoder->CalcalateTime(mDecoder->GetCurrentPosition());
		}
		int AudioPlayer::SetVolumne(int volume)
		{
			volume = max(volume, MIN_VOLUME);
			volume = min(volume, MAX_VOLUME);

			if (volume == mPlayerState.volume)
				return 0;
			mPlayerState.volume = volume;
			if (mPlayerState.isPlaying && !mPlayerState.isMute)
				mAudio2.pSourceVoice->SetVolume(1.0f * volume / (float)MAX_VOLUME);
			return 0;
		}
		int AudioPlayer::SetMute(bool mute)
		{
			if (mPlayerState.isMute == mute)
				return 0;

			mPlayerState.isMute = mute;
			mAudio2.pSourceVoice->SetVolume(mute ? 0 : 1.0f * mPlayerState.volume / (float)MAX_VOLUME);
			return 0;
		}
		int AudioPlayer::SetCallback(ZACallbackFunction func, void* para)
		{
			mCallback.callbackFunc = func;
			mCallback.client = para;
			return 0;
		}

		const WaveInfo& AudioPlayer::GetWaveInfo() const
		{
			return mDecoder->getWaveInfo();
		}

		const PlayerState& AudioPlayer::GetPlayerState() const
		{
			return mPlayerState;
		}
		void AudioPlayer::InitAudio2()
		{
			ZeroMemory(&mAudio2, sizeof(Audio2));
			UINT32 flags = 0;
#ifdef _DEBUG
			flags |= XAUDIO2_DEBUG_ENGINE;
#endif
			HRESULT hr;

			if (FAILED(hr = XAudio2Create(&mAudio2.pXAudio2, flags)))
			{
				throw ZPEngineException("fail to init xaudio2");
			}

			if (FAILED(hr = mAudio2.pXAudio2->CreateMasteringVoice(&mAudio2.pMasteringVoice)))
			{
				SAFE_RELEASE(mAudio2.pXAudio2);
				throw ZPEngineException("fail to create mastering voice");
			}

			if (FAILED(hr = mAudio2.pXAudio2->GetDeviceDetails(0, &mDetails)))
			{
				SAFE_RELEASE(mAudio2.pXAudio2);
				throw ZPEngineException("fail to get device details");
			}

			if (FAILED(hr = mAudio2.pXAudio2->CreateSubmixVoice(&mAudio2.pSubmixVoice, 1,
				mDetails.OutputFormat.Format.nSamplesPerSec, 0, 0,
				NULL, NULL)))
			{
				SAFE_RELEASE(mAudio2.pXAudio2);
				throw ZPEngineException("fail to create submix voice");
			}

			mAudio2.pSourceVoice = 0;
			// done
			mAudio2.bInitialized = true;
			mPlayerState.isStop = true;

			memset(&mCallback, 0, sizeof(mCallback));
		}


		void AudioPlayer::CleanupAudio()
		{
			if (!mAudio2.bInitialized)
				return;

			if (mAudio2.pSourceVoice)
			{
				mAudio2.pSourceVoice->DestroyVoice();
				mAudio2.pSourceVoice = NULL;
			}

			if (mAudio2.pSubmixVoice)
			{
				mAudio2.pSubmixVoice->DestroyVoice();
				mAudio2.pSubmixVoice = NULL;
			}

			if (mAudio2.pMasteringVoice)
			{
				mAudio2.pMasteringVoice->DestroyVoice();
				mAudio2.pMasteringVoice = NULL;
			}

			//m_audioState.pXAudio2->StopEngine();

			SAFE_RELEASE(mAudio2.pReverbEffect);
			SAFE_RELEASE(mAudio2.pXAudio2);
			mAudio2.bInitialized = false;
		}

		int WINAPI AudioPlayer::PlayerThread(void* lpdwParam)
		{
			AudioPlayer* player = (AudioPlayer*)lpdwParam;
			if (NULL == player)
			{
				return PlayerError::InvalidPlayerPara;
			}

			if (player->mAudio2.pSourceVoice)
			{
				player->mAudio2.pSourceVoice->Stop(0);
				player->mAudio2.pSourceVoice->DestroyVoice();
				player->mAudio2.pSourceVoice = 0;
			}
			
			VoiceCallback voiceCallback;
			HRESULT hr;
			if (FAILED(hr = player->mAudio2.pXAudio2->CreateSourceVoice(
				&player->mAudio2.pSourceVoice, &(player->GetWaveInfo().waveFormatex), 0, XAUDIO2_DEFAULT_FREQ_RATIO,
				&voiceCallback, NULL, NULL)))
			{
				return PlayerError::FailToCreateSourceVoice;
			}

			size_t CurrentDiskBuffer = 0;
			player->mAudio2.pSourceVoice->SetVolume(
				player->mPlayerState.isMute ? 0 : 1.0f*player->mPlayerState.volume / (float)MAX_VOLUME
				);
			hr = player->mAudio2.pSourceVoice->Start(0);

		
			player->Callback(PlayerStateMessage::Play);

			DWORD dwRead;
			DWORD cbValid;
			DWORD has;
			XAUDIO2_VOICE_STATE state;

			DWORD end = player->mPlayControl.end;
			Decoder* decoder = player->mDecoder;
			AudioBuffer<BYTE>* buffers = player->mBuffers.get();
			bool isEnd = false;
			while (decoder->GetCurrentPosition() < end && player->mPlayerState.isPlaying)
			{
				has = end - decoder->GetCurrentPosition();
				decoder->Read((*buffers)[CurrentDiskBuffer], STREAMING_BUFFER_SIZE, &dwRead);
				cbValid = min(STREAMING_BUFFER_SIZE, dwRead);
				if (has <= 0)
				{
					cbValid += has;
				}
				else
				{
					cbValid = min(has, dwRead);
				}
				if (cbValid <= 0)
				{
					cbValid = decoder->getWaveInfo().waveFormatex.nBlockAlign;
					memset((*buffers)[CurrentDiskBuffer], 0, STREAMING_BUFFER_SIZE);
					isEnd = true;
				}

				while (player->mAudio2.pSourceVoice->GetState(&state), state.BuffersQueued >= MAX_BUFFER_COUNT - 1)
				{
					if (!player->mPlayerState.isPlaying)
					{
						player->mAudio2.pSourceVoice->Stop(0);
						player->mPlayerState.isStop = true;
						player->Callback(PlayerStateMessage::UserStop);
						return 0;
					}
					WaitForSingleObject(voiceCallback.hBufferEndEvent, INFINITE);
				}

				XAUDIO2_BUFFER buf = { 0 };
				buf.AudioBytes = cbValid;
				buf.pAudioData = (*buffers)[CurrentDiskBuffer];
				if (isEnd)
				{
					buf.Flags = XAUDIO2_END_OF_STREAM;
				}
				//HRESULT hh = GetLastError();

				hr = player->mAudio2.pSourceVoice->SubmitSourceBuffer(&buf);
				CurrentDiskBuffer++;
				CurrentDiskBuffer %= MAX_BUFFER_COUNT;

			}
						
			player->Callback(player->mPlayerState.isPlaying ? PlayerStateMessage::Stop : PlayerStateMessage::UserStop);
			return 0;
		}

		void AudioPlayer::Callback(PlayerStateMessage message, WPARAM wp, LPARAM lp)
		{
			if (NULL != mCallback.callbackFunc)
			{
				mCallback.callbackFunc(this, message, mCallback.client,wp, lp);
			}
		}
	}
}
