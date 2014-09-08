#pragma once
#include <time.h>
#include <string>
using namespace std;
#include <sys/timeb.h> 

namespace veda
{
	class Datetime
	{
	public:
		Datetime();
		Datetime(time_t t);
		Datetime(const wchar_t* timeStr, const wchar_t* pattern = L"yyyy-MM-dd HH:mm:ss");
		~Datetime();
		time_t getTime() const;
		short getYear() const;
		short getMonth() const;
		short getDay() const;
		short getMinute() const;
		short getSecond() const;
		short getMillisecond() const;
		short getDayOfYear() const;
		short getDayOfWeek() const;
		wstring format(const wchar_t* pattern = L"yyyy-MM-dd HH:mm:ss");
		void format(wchar_t* buf, const wchar_t* pattern = L"yyyy-MM-dd HH:mm:ss");
		static Datetime now();
	private:
		void parse(time_t t);
		void parse(struct tm* tm);
		void parse(const wchar_t* timeStr, const wchar_t* pattern);
	private:
		time_t timeVal;
		short year;
		short month;
		short day;
		short hour;
		short minute;
		short second;
		short millisecond;
		short dayOfYear;
		short dayOfWeek;
	};
}


