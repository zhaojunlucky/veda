#pragma once
#include "ThemeModel.h"
namespace zpl
{
	class ThemeController
	{
	public:
		ThemeController();
		~ThemeController();
		const ThemeModel& GetTheme() const;
	private:
		ThemeModel mTM;
	};
}


