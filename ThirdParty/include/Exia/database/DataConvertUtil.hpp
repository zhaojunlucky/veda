#pragma once
#include <string>
#include "HANATypes.h"
#include <StringConvertInternal.hpp>


namespace db
{
	static bool StrToValue(const std::string &s, char &v)
	{
		if (s.empty()) return false;
		v = (char)atoi(s.c_str());
		return true;
	}

	static bool StrToValue(const std::wstring &s, char &v)
	{
		if (s.empty()) return false;
		v = (char)_wtoi(s.c_str());
		return true;
	}

	static bool StrToValue(const std::wstring &s, wchar_t &v)
	{
		if (s.empty()) return false;
		v = (wchar_t)_wtoi(s.c_str());
		return true;
	}

	static bool StrToValue(const std::string &s, short &v)
	{
		if (s.empty()) return false;
		v = (short)atoi(s.c_str());
		return true;
	}

	static bool StrToValue(const std::wstring &s, short &v)
	{
		if (s.empty()) return false;
		v = (short)_wtoi(s.c_str());
		return true;
	}

	static bool StrToValue(const std::string &s, int &v)
	{
		if (s.empty()) return false;
		v = atoi(s.c_str());
		return true;
	}

	static bool StrToValue(const std::wstring &s, int &v)
	{
		if (s.empty()) return false;
		v = _wtoi(s.c_str());
		return true;
	}

	static bool StrToValue(const std::string &s, BigInt &v)
	{
		if (s.empty()) return false;
#ifdef _WIN32
		v = _atoi64(s.c_str());
#else
		v = atoll(s.c_str());
#endif
		return true;
	}

	static bool StrToValue(const std::wstring &s, BigInt &v)
	{
		if (s.empty()) return false;
#ifdef _WIN32
		v = _wtoi64(s.c_str());
#else
		v = atoll(s.c_str());
#endif
		return true;
	}

	static bool StrToValue(const std::string &s, float &v)
	{
		if (s.empty()) return false;
		v = (float)atof(s.c_str());
		return true;
	}

	static bool StrToValue(const std::wstring &s, float &v)
	{
		if (s.empty()) return false;
		v = (float)_wtof(s.c_str());
		return true;
	}

	static bool StrToValue(const std::string &s, double &v)
	{
		if (s.empty()) return false;
		v = atof(s.c_str());
		return true;
	}

	static bool StrToValue(const std::wstring &s, double &v)
	{
		if (s.empty()) return false;
		v = _wtof(s.c_str());
		return true;
	}

	static bool StrToValue(const std::string &s, SQL_DATE_STRUCT &v)
	{
		if (s.empty()) return false;
		int year, month, day;
		if (3 == sscanf(s.c_str(), "%d-%d-%d", &year, &month, &day)) {
			v.year = year;
			v.month = month;
			v.day = day;
			if (v.year < 0 || v.year > 3000) return false;
			if (v.month <= 0 || v.month > 12) return false;
			if (v.day <= 0 || v.day > 31) return false;
			return true;
		}
		return false;
	}

	static bool StrToValue(const std::wstring &s, SQL_DATE_STRUCT &v)
	{
		if (s.empty()) return false;
		int year, month, day;
		if (3 == swscanf(s.c_str(), L"%d-%d-%d", &year, &month, &day)) {
			v.year = year;
			v.month = month;
			v.day = day;
			if (v.year < 0 || v.year > 3000) return false;
			if (v.month <= 0 || v.month > 12) return false;
			if (v.day <= 0 || v.day > 31) return false;
			return true;
		}
		return false;
	}

	static bool StrToValue(const std::string &s, SQL_TIME_STRUCT &v)
	{
		if (s.empty()) return false;
		int hour, minute, second;
		if (3 == sscanf(s.c_str(), "%d:%d:%d", &hour, &minute, &second)) {
			v.hour = hour;
			v.minute = minute;
			v.second = second;
			if (v.hour > 24) return false;
			if (v.minute >= 60) return false;
			if (v.second >= 60) return false;
			return true;
		}
		return false;
	}

	static bool StrToValue(const std::wstring &s, SQL_TIME_STRUCT &v)
	{
		if (s.empty()) return false;
		int hour, minute, second;
		if (3 == swscanf(s.c_str(), L"%d:%d:%d", &hour, &minute, &second)) {
			v.hour = hour;
			v.minute = minute;
			v.second = second;
			if (v.hour > 24) return false;
			if (v.minute >= 60) return false;
			if (v.second >= 60) return false;
			return true;
		}
		return false;
	}

	static bool StrToValue(const std::string &s, SQL_TIMESTAMP_STRUCT &v)
	{
		if (s.empty()) return false;

		int year, month, day, hour, minute, second, fraction;

		int r = sscanf(s.c_str(), "%d-%d-%d%*[ -]%d%*[:.]%d%*[:.]%d%*[:.]%d",
			&year, &month, &day, &hour, &minute, &second, &fraction);
		if (r == 5 || r == 6 || r == 7) {
			if (r == 5) {
				second = fraction = 0;
			}
			else if (r == 6) {
				fraction = 0;
			}

			if (year <= 0 || year > 3000) return false;
			if (month < 0 || month > 12) {
				return false;
			}
			else if (month == 0) {
				month = 1;
			}
			if (day < 0 || day > 31) {
				return false;
			}
			else if (day == 0) {
				day = 1;
			}
			if (hour > 24) return false;
			if (minute > 60) return false;
			if (second > 60) return false;

			v.year = year;
			v.month = month;
			v.day = day;
			v.hour = hour;
			v.minute = minute;
			v.second = second;
			v.fraction = fraction;

			return true;
		}
		return false;
	}

	static bool StrToValue(const std::wstring &s, SQL_TIMESTAMP_STRUCT &v)
	{
		if (s.empty()) return false;

		int year, month, day, hour, minute, second, fraction;

		int r = swscanf(s.c_str(), L"%d-%d-%d%*[ -]%d%*[:.]%d%*[:.]%d%*[:.]%d",
			&year, &month, &day, &hour, &minute, &second, &fraction);
		if (r == 5 || r == 6 || r == 7) {
			if (r == 5) {
				second = fraction = 0;
			}
			else if (r == 6) {
				fraction = 0;
			}

			if (year <= 0 || year > 3000) return false;
			if (month < 0 || month > 12) {
				return false;
			}
			else if (month == 0) {
				month = 1;
			}
			if (day < 0 || day > 31) {
				return false;
			}
			else if (day == 0) {
				day = 1;
			}
			if (hour > 24) return false;
			if (minute > 60) return false;
			if (second > 60) return false;

			v.year = year;
			v.month = month;
			v.day = day;
			v.hour = hour;
			v.minute = minute;
			v.second = second;
			v.fraction = fraction;

			return true;
		}
		return false;
	}
	/*
	 * this couldn't be called
	 */
	static bool StrToValue(const std::string &s, wchar_t &v)
	{
		v = 0;
		return true;
	}

}