#pragma once
#include"MediaModel.h"
#include <memory>
#include <AudioPlayer.h>
#include <hash_map>
#include <string>
#include <Decoder.h>
#include <DecoderFactory.hpp>
using namespace audio;
using namespace audio::player;


namespace zpl
{
	class PlayerControl
	{
	public:
		PlayerControl();
		~PlayerControl();
		void InitPlayer();
		void PreparePlay(const MediaModel& m);
	public:
		std::shared_ptr<AudioPlayer> player;
	private:
		std::hash_map<int, std::shared_ptr<Decoder>> decoders;
		Decoder* activeDecoder;
		MediaModel m;
	};
}


