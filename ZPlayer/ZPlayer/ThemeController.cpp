#include "ThemeController.h"

namespace zpl
{
	ThemeController::ThemeController()
	{
	}


	ThemeController::~ThemeController()
	{
	}

	const ThemeModel& ThemeController::GetTheme() const
	{
		return mTM;
	}
}
