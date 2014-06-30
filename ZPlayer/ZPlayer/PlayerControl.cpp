#include "PlayerControl.h"

namespace zpl
{
	PlayerControl::PlayerControl()
	{
	}


	PlayerControl::~PlayerControl()
	{
	}

	void PlayerControl::InitPlayer()
	{
		player.reset(new AudioPlayer);
	}

	void PlayerControl::PreparePlay(const MediaModel& m)
	{
		this->m = m;
		if (!player->GetPlayerState().isStop)
		{
			player->Stop();
		}

		activeDecoder->Close();
		Decoder* d = 0;
		std::hash_map<int, std::shared_ptr<Decoder>>::iterator it = decoders.find(m.af);
		if (it != decoders.end())
		{
			d = it->second.get();
			d->Open(m.file.c_str());
		}
		else
		{
			std::shared_ptr<Decoder> dptr(audio::DecoderFactory::CreateDecoderByFile(m.file.c_str()));
			decoders[m.af] = dptr;
			d = dptr.get();
		}
		activeDecoder = d;
	}

}