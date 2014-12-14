#pragma once
#include "PlayerBase.h"
#include <Exia\common\InternalBuffer.hpp>
#include <memory>
#include <vector>

namespace audio
{
	namespace player
	{
		template <class T>
		class __declspec(dllexport) AudioBuffer
		{
		public:
			AudioBuffer(size_t bufferCount,size_t bufferSize);
			virtual ~AudioBuffer();

			T* operator[](const size_t index)
			{
				return  mBuffers[index]->getData();
			}

			T* operator[](const size_t index) const
			{
				return mBuffers[index]->getData();
			}

			size_t GetBufferCount() const
			{
				return mBufferCount
			}

			size_t GetBufferSize() const
			{
				return mBufferSize;
			}
		private:
			size_t mBufferCount;
			size_t mBufferSize;
			std::vector<std::shared_ptr<common::InternalBuffer<T>>> mBuffers;
		};

		template<class T>
		AudioBuffer<T>::AudioBuffer(size_t bufferCount, size_t bufferSize)
		{
			mBufferCount = bufferCount;
			mBufferSize = bufferSize;
			for (size_t i = 0; i < bufferCount; i++)
			{
				std::shared_ptr<common::InternalBuffer<T> > buffer(new common::InternalBuffer<T>(bufferSize));
				mBuffers.push_back(buffer);
			}
		}

		template<class T>
		AudioBuffer<T>::~AudioBuffer()
		{
			mBuffers.clear();
		}
	}
}
