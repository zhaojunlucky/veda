#include "ZHUICtrl.h"

namespace zhui
{
	ZHUICtrl::ZHUICtrl(const element& el)
		:el(el), mUserData(0)
	{
	}

	ZHUICtrl::ZHUICtrl(HELEMENT he)
		: el(he), mUserData(0)
	{
	}

	ZHUICtrl::ZHUICtrl(const ZHUICtrl& ctrl)
		: el(ctrl.el), mUserData(ctrl.mUserData)
	{

	}


	ZHUICtrl::~ZHUICtrl()
	{
	}
	ZHUICtrl& ZHUICtrl::operator=(const element& el)
	{
		this->el = el;
		mUserData = 0;
		return *this;
	}
	ZHUICtrl& ZHUICtrl::operator=(const HELEMENT he)
	{
		this->el = he;
		mUserData = 0;
		return *this;
	}
	ZHUICtrl& ZHUICtrl::operator=(const ZHUICtrl& ctrl)
	{
		if (this != &ctrl)
		{
			el = ctrl.el;
			mUserData = ctrl.mUserData;
		}
		return *this;
	}
	bool ZHUICtrl::operator==(const element& el) const
	{
		return this->el == el;
	}
	bool ZHUICtrl::operator==(const HELEMENT he) const
	{
		return this->el == he;
	}
	bool ZHUICtrl::operator==(const ZHUICtrl& ctrl) const
	{
		return el == ctrl.el;
	}
	element& ZHUICtrl::GetElelemt()
	{
		return el;
	}

	const char* ZHUICtrl::GetElementType() const
	{
		return el.get_element_type();
	}

	CTL_TYPE ZHUICtrl::GetCtrlType() const
	{
		return el.get_ctl_type();
	}

	void ZHUICtrl::SetUserData(void* data)
	{
		mUserData = data;
	}
	void* ZHUICtrl::GetUserData()
	{
		return mUserData;
	}
}
