#pragma once
#include <vector>
#include <string>

namespace common
{
	class StringHelper
	{
	public:
		static void TrimLeft(const std::wstring& str, std::wstring& dst)
		{
			const wchar_t* pattern = L" \n\r\t";
			size_t firstNotOf = str.find_first_not_of(pattern);
			size_t firstOf = str.find_first_of(pattern);
			if (firstNotOf != std::wstring::npos)
			{
				dst = str.substr(firstNotOf);
			}
			else if (firstOf != std::wstring::npos)
			{
				// str are all space
				dst = L"";
			}
			else
			{
				dst = str;
			}
		}

		static void TrimRight(const std::wstring& str, std::wstring& dst)
		{
			const wchar_t* pattern = L" \n\r\t";
			size_t lastNotOf = str.find_last_not_of(pattern);
			size_t lastOf = str.find_last_of(pattern);
			if (str.find_first_not_of(L" \n\r\t") != std::wstring::npos)
			{
				dst = str.substr(0, lastNotOf + 1);
			}
			else if (lastOf != std::wstring::npos)
			{
				// str are all space
				dst = L"";
			}
			else
			{
				dst = str;
			}
		}

		static void Trim(const std::wstring& str, std::wstring& dst)
		{
			std::wstring dest;
			TrimLeft(str, dest);
			TrimRight(dest, dst);
		}
		static void Split(const std::string& line, std::vector<std::string> &cols, char delimiter)
		{
			int linepos = 0;
			int inquotes = false;
			char c;
			int linemax = (int)line.length();
			std::string curstring;

			while (line[linepos] != 0 && linepos < linemax) {

				c = line[linepos];

				if (!inquotes && curstring.length() == 0 && c == '"') {
					//beginquotechar
					inquotes = true;
				}
				else if (inquotes && c == '"') {
					//quotechar
					if ((linepos + 1 < linemax) && (line[linepos + 1] == '"')) {
						//encountered 2 double quotes in a row (resolves to 1 double quote)
						curstring.push_back(c);
						linepos++;
					}
					else {
						//endquotechar
						inquotes = false;
					}
				}
				else if (!inquotes && c == delimiter) {
					//end of field
					TrimLeftAndPushBack(cols, curstring);
					curstring = "";
				}
				else if (!inquotes && (c == '\r' || c == '\n')) {
					TrimLeftAndPushBack(cols, curstring);
					return;
				}
				else {
					curstring.push_back(c);
				}
				linepos++;
			}
			if (curstring.size() > 0)
			{
				TrimLeftAndPushBack(cols, curstring);
			}
		}
		static void Split(const std::wstring& line, std::vector<std::wstring> &cols, wchar_t delimiter)
		{
			int linepos = 0;
			int inquotes = false;
			wchar_t c;
			int linemax = (int)line.length();
			std::wstring curstring;

			while (line[linepos] != 0 && linepos < linemax) {

				c = line[linepos];

				if (!inquotes && curstring.length() == 0 && c == L'"') {
					//beginquotechar
					inquotes = true;
				}
				else if (inquotes && c == L'"') {
					//quotechar
					if ((linepos + 1 < linemax) && (line[linepos + 1] == L'"')) {
						//encountered 2 double quotes in a row (resolves to 1 double quote)
						curstring.push_back(c);
						linepos++;
					}
					else {
						//endquotechar
						inquotes = false;
					}
				}
				else if (!inquotes && c == delimiter) {
					//end of field
					TrimLeftAndPushBack(cols, curstring);
					curstring = L"";
				}
				else if (!inquotes && (c == L'\r' || c == L'\n')) {
					TrimLeftAndPushBack(cols, curstring);
					return;
				}
				else {
					curstring.push_back(c);
				}
				linepos++;
			}
			if (curstring.size() > 0)
			{
				TrimLeftAndPushBack(cols, curstring);
			}
		}
	private:
		static inline
			void TrimLeftAndPushBack(std::vector<std::string> &strs, std::string &str)
		{
				const char *s = str.c_str();
				while (*s == ' ' || *s == '\t') s++;
				strs.push_back(s);
		}

		static inline
			void TrimLeftAndPushBack(std::vector<std::wstring> &strs, std::wstring &str)
		{
				const wchar_t *s = str.c_str();
				while (*s == L' ' || *s == L'\t') s++;
				strs.push_back(s);
		}
	};
}