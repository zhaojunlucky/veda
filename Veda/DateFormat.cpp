#include "stdafx.h"
#include "DateFormat.h"

namespace veda
{
	void DateFormat::parseDatePattern(Vector<Token>& tokens, const wchar_t* pattern)
	{
		size_t len = wcslen(pattern);
		wchar_t c;
		Token t;
		t.s = 0;
		t.key.push_back(pattern[0]);
		for (auto i = 1; i < len; i++)
		{
			c = pattern[i];
			
			switch (c)
			{
			case L'y':
			case L'M':
			case L'd':
			case L'H':
			case L'h':
			case L'm':
			case L's':
			case L'S':
			case L'a':
			{
				if (checkToken(t, c))
				{
					pushToken(tokens,t,i-1);
					t.key.clear();
					t.s = i;
					t.isFormatKey = false;
				}
				t.key.push_back(c);
			}break;
			default:
			{
				if (isFormartKey(t.key[t.key.size()-1]))
				{
					pushToken(tokens, t, i - 1);
					t.key.clear();
					t.s = i;				
					t.isFormatKey = false;
				}
				t.key.push_back(c);
			}
				break;
			}
		}
		pushToken(tokens, t, len - 1);
	}

	bool DateFormat::isFormartKey(wchar_t k)
	{
		return keys.find(k) != keys.npos;
	}

	bool DateFormat::checkToken(Token& t, wchar_t c)
	{
		return !(c == t.key[t.key.size() - 1]);
	}

	void DateFormat::pushToken(Vector<Token>& tokens, Token& t, size_t e)
	{
		t.e = e;
		for (auto c : t.key)
		{
			if (isFormartKey(c))
			{
				t.isFormatKey = true;
				break;
			}
		}
		tokens.add(t);
	}
}

