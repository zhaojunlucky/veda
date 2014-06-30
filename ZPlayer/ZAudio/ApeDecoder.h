#pragma once
#include "Decoder.h"

#include <ape\All.h>

#include <ape\MACLib.h>
#include <Exia\common\InternalBuffer.hpp>
#include <memory>
namespace audio
{
#define APE_BLOCKS_NUM 1024
	using namespace APE;
	class __declspec(dllexport) ApeDecoder :
		public Decoder
	{
	public:
		ApeDecoder();
		virtual ~ApeDecoder();

		virtual int Open(const wchar_t* file);
		virtual int Read(BYTE* buffer, DWORD dwSizeToRead, DWORD* sizeReaded);
		virtual int Reset();
		virtual int Seek(float duration);
		virtual int Close();
	private:
		void SetAudioInfo(const char* key, const char* value);

	private:
		IAPEDecompress * m_pAPEDecompress;
		unsigned int m_total_blocks;
		unsigned int m_current_blocks;
		int m_block_algin;
		std::shared_ptr<common::InternalBuffer<BYTE>> m_pWaveDataAlloc;
		BYTE* m_pWaveDataBuffer;
		unsigned int m_nWaveDataNum;		// number of samples in samples buffer
	};
}


