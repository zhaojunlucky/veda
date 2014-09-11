#pragma once
#include <time.h>
#include <string>
using namespace std;
#include <sys/timeb.h> 
#include <Vector.h>
#include "DateFormat.h"
#include "ZString.h"
namespace veda
{
	/**
	 * y -> year
	 * M -> month [1-12]
	 * d -> date [1-31]
	 * H -> hour [0-23]
	 * h -> hour [0-12]
	 * m -> minute [0-59]
	 * s -> second [0-59]
	 * S -> millisecond [0-999]
	 * a -> AM PM 
	 */
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
		DateFormat df;
	};
}


