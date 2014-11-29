#pragma once
#include <UIlib.h>
using namespace DuiLib;
class PlayControlUI : public CContainerUI
{
public:
	PlayControlUI()
	{
		CDialogBuilder builder;
		CContainerUI* pPlayControl = static_cast<CContainerUI*>(builder.Create(_T("ui/play_control.xml"), (UINT)0));
		if (pPlayControl) {
			this->Add(pPlayControl);
		}
		else {
			this->RemoveAll();
			return;
		}
	}
};