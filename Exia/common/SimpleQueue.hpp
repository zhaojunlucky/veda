#pragma once
#include <queue>
#include <mutex>

using namespace std;
namespace al
{
	template <class T>
	class SimpleQueue
	{
	public:
		void enqueue(T v)
		{
			std::lock_guard<std::mutex> lock(mMutex);
			mQ.push(v);
		}

		bool dequeue(T& v)
		{
			std::lock_guard<std::mutex> lock(mMutex);
			bool ok = false;
			if (mQ.size() > 0)
			{
				v = mQ.front();
				mQ.pop();
				ok = true;
			}
			return ok;
		}

		size_t size() const
		{
			std::lock_guard<std::mutex> lock(mMutex);
			return mQ.size();
		}

		bool isEmpty() const
		{
			std::lock_guard<std::mutex> lock(mMutex);
			return (mQ.size() == 0);
		}
	private:
		queue<T> mQ;
		mutex mMutex;
	};
}