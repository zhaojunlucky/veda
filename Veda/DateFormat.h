#pragma once
#include <Vector.h>
#include "ZString.h"

namespace veda
{
	struct Token
	{
		Token(){}
		Token(const Token& t)
		{
			s = t.s;
			e = t.e;
			key = t.key;
			isFormatKey = t.isFormatKey;
		}
		size_t s;
		size_t e;
		WString key;
		bool isFormatKey;
	};

	
	class DateFormat
	{
	public:
		void parseDatePattern(Vector<Token>& tokens, const wchar_t* pattern);
	private:
		bool isFormartKey(wchar_t k);
		bool checkToken(Token& t, wchar_t c);
		void pushToken(Vector<Token>& tokens,Token& t, size_t e);
	private:
		const WString keys = L"yMdHhmsSa";
	};
}


