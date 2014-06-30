#pragma once
#include <vector>
namespace geo
{
	// not thread safe
	template <class T>
	class GeoCollection
	{
	public:
		GeoCollection()
		{

		}

		virtual ~GeoCollection()
		{
			DeleteAll();
		}

		virtual void FreeObject(T* v)
		{
			delete v;
		}

		void Delete(size_t index)
		{
			FreeObject(mData[index]);
			mData.erase(mData.begin() + index);
		}

		void DeleteAll()
		{
			for (size_t i = 0; i < mData.size(); i++)
			{
				FreeObject(mData[i]);
			}
			mData.clear();
		}

		T* Remove(size_t index)
		{
			T* v = mData[index];
			mData.erase(mData.begin() + index);
			return v;
		}

		size_t Size() const
		{
			return mData.size();
		}

		virtual void AddCopy(const T& v) = 0;
		void Add(T* v)
		{
			mData.push_back(v);
		}

		const T* Get(size_t index) const
		{
			return mData[index];
		}

		const T & operator[](size_t index) const
		{
			return *mData[index];
		}

		void Reverse()
		{
			std::reverse(mData.begin(), mData.end());
		}
	private:
		GeoCollection& operator = (const GeoCollection& other)
		{
			return *this;
		}
		GeoCollection(const GeoCollection& other)
		{

		}
	protected:
		std::vector<T*> mData;
	};

}