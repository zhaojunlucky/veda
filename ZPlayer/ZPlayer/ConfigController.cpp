#include "ConfigController.h"

namespace  zpl
{
	ConfigController::ConfigController()
	{
		mCM.lastPlayIndex = 0;
		mCM.lastSelectedPlayList = "Temp";
	}


	ConfigController::~ConfigController()
	{
	}

	const string& ConfigController::GetLastSelectedPlayList() const
	{
		return mCM.lastSelectedPlayList;
	}
	size_t ConfigController::GetLastPlayIndex() const
	{
		return mCM.lastPlayIndex;
	}
}