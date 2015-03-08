#pragma once
#include <memory>

namespace veda
{
	template <class T>
	/*
	 T must be char or wchar_t type
	 */
	class AssertException 
	{
	public:
		AssertException()
		{
			mData = new T[1];
			mData[0] = L'\0';
		}
		AssertException(const T* data)
		{
			mData = 0;
			assign(data);
		}

		AssertException(const AssertException& other)
		{
			*this = other;
		}

		AssertException& operator=(const AssertException& other)
		{
			if (this != &other)
			{
				mData = 0;
				assign(other.mData);
			}
			
			return *this;
		}

		virtual ~AssertException()
		{
			if (mData)
			{
				delete mData;
				mData = 0;
			}
		}

		const T* getMessage() const
		{
			return mData;
		}
	private:
		void assign(const T* data)
		{
			if (mData != 0)
			{
				delete mData;
			}
			const T* ptr = &data[0];
			size_t len = 0;
			while (*ptr++)
			{
				++len;
			}
			mData = new T[len + 1];
			if (len > 0)
			{
				memcpy(mData, data, len*sizeof(T));
			}
			
			mData[len] = L'\0';
		}
	private:
		T* mData;
	};
}