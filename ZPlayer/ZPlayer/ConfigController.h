#pragma once
#include "ConfigModel.h"
namespace  zpl
{
	class ConfigController
	{
	public:
		ConfigController();
		~ConfigController();

		const string& GetLastSelectedPlayList() const;
		size_t GetLastPlayIndex() const;
	private:
		ConfigModel mCM;
	};
}


