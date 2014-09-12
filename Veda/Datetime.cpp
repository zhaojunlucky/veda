#include "stdafx.h"
#include "Datetime.h"

namespace veda
{

	Datetime::Datetime()
	{
		struct timeb tp;

		ftime(&tp);
		millisecond = tp.millitm;
		timeVal = tp.time;
		parse(timeVal);
	}

	Datetime::Datetime(time_t t)
		:timeVal(t)
	{
		millisecond = 0;
		parse(timeVal);
	}
	Datetime::Datetime(const wchar_t* timeStr, const wchar_t* pattern)
	{
		parse(timeStr, pattern);
	}
	Datetime::~Datetime()
	{
	}

	time_t Datetime::getTime() const
	{
		return timeVal;
	}
	short Datetime::getYear() const
	{
		return year;
	}
	short Datetime::getMonth() const
	{
		return month;
	}
	short Datetime::getDay() const
	{
		return day;
	}
	short Datetime::getMinute() const
	{
		return minute;
	}
	short Datetime::getSecond() const
	{
		return second;
	}
	short Datetime::getMillisecond() const
	{
		return millisecond;
	}

	short Datetime::getDayOfYear() const
	{
		return dayOfYear;
	}
	short Datetime::getDayOfWeek() const
	{
		return dayOfWeek;
	}

	wstring Datetime::format(const wchar_t* pattern)
	{
		wstring str;
		str.reserve(64);
		format(&str[0], pattern);
		return std::move(str);
	}
	void Datetime::format(wchar_t* buf, const wchar_t* pattern)
	{
		String sh;
		Vector<Token> ts;
		df.parseDatePattern(ts, pattern);
		wchar_t *ptr = &buf[wcslen(buf)];
		for (auto& t : ts)
		{
			if (t.isFormatKey)
			{
				switch (t.key[0])
				{
				case L'y':
				{
					if (t.key.size() == 2)
					{
						sh = (year-(year/100)*100);
					}
					else
					{
						sh = year;
					}
				}break;
				case L'M':
				{
					if (t.key.size() == 1)
					{
						sh = month;
					}
					else
					{
						sh.format(_T("%02d"), month);
					}
				}break;
				case L'd':
				{
					if (t.key.size() == 1)
					{
						sh = day;
					}
					else
					{
						sh.format(_T("%02d"), day);
					}
				}break;
				case L'H':
				{
					if (t.key.size() == 1)
					{
						sh = hour;
					}
					else
					{
						sh.format(_T("%02d"), hour);
					}
				}break;
				case L'h':
				{
					int h = (hour > 12) ? hour % 12 : hour;
					if (t.key.size() == 1)
					{
						sh = h;
					}
					else
					{
						sh.format(_T("%02d"), h);
					}
				}break;
				case L'm':
				{
					if (t.key.size() == 1)
					{
						sh = minute;
					}
					else
					{
						sh.format(_T("%02d"), minute);
					}
				}break;
				case L's':
				{
					if (t.key.size() == 1)
					{
						sh = second;
					}
					else
					{
						sh.format(_T("%02d"), second);
					}
				}break;
				case L'S':
				{
					if (t.key.size() == 2)
					{
						sh = second;
					}
					else
					{
						sh.format(_T("%03d"), second);
					}
				}break;
				case L'a':
				{
					sh = hour >= 12 ?_T("PM"):_T("AM");
				}break;
				default:
					sh = _T("");
					break;
				}
			}
			else
			{
				sh = t.key.c_str();
			}
			
			size_t len = sh.getSize();
			*(ptr + len) = '\0';
			for (auto i = 0; i < len; i++)
			{
				*ptr++ = sh[i];
			}

		}
	}
	Datetime Datetime::now()
	{
		return std::move(Datetime());
	}
	void Datetime::parse(time_t t)
	{
		struct tm tm;
		localtime_s(&tm,&timeVal);
		parse(&tm);
	}
	void Datetime::parse(struct tm* tm)
	{
		year = tm->tm_year + 1900;
		month = tm->tm_mon + 1;
		day = tm->tm_mday;
		hour = tm->tm_hour;
		minute = tm->tm_min;
		second = tm->tm_sec;
		dayOfYear = tm->tm_yday;
		dayOfWeek = tm->tm_wday;
	}
	void Datetime::parse(const wchar_t* timeStr, const wchar_t* pattern)
	{
		
	}
}

