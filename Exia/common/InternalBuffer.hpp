#pragma once
namespace common
{
	template <class T>
	class InternalBuffer
	{
	public:
		InternalBuffer(size_t size)
		{
			mData = new T[size];
			mSize = size;
		}
		~InternalBuffer()
		{
			delete mData;
		}

		operator T*()
		{
			return mData;
		}

		size_t GetBufferSize() const
		{
			return mSize;
		}

		size_t Copy(T* dst, size_t sizeToCopy) const
		{
			size_t len = GetDataSize();
			if (len > sizeToCopy)
			{
				len = sizeToCopy;
			}
			for (size_t i = mIndex; i < mIndex + sizeToCopy; i++)
			{
				dst[i - mIndex] = mData[i];
			}
			return len;
		}
		// reset the data size, and set the current data index to 0
		void SetDataSize(size_t size)
		{
			mDataSize = size;
			mIndex = 0;
		}

		size_t GetDataSize() const
		{
			return mDataSize - mIndex;
		}

		T* getData()
		{
			return mData;
		}
	private:
		T* mData;
		size_t mDataSize;
		size_t mSize;
		size_t mIndex;
	};
}