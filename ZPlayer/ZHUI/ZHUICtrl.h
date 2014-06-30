#pragma once
#include <assert.h>
#include <htmlayout.h>
using namespace htmlayout;
using namespace htmlayout::dom;

namespace zhui
{
	class __declspec(dllexport) ZHUICtrl
	{
	public:
		ZHUICtrl(const element& el);
		ZHUICtrl(const HELEMENT he);
		ZHUICtrl(const ZHUICtrl& ctrl);
		virtual ~ZHUICtrl();
		ZHUICtrl& operator=(const element& el);
		ZHUICtrl& operator=(const HELEMENT he);
		ZHUICtrl& operator=(const ZHUICtrl& ctrl);
		bool operator==(const element& el) const;
		bool operator==(const HELEMENT he) const;
		bool operator==(const ZHUICtrl& ctrl) const;
		element& GetElelemt();
		const char* GetElementType() const;
		CTL_TYPE GetCtrlType() const;
		void SetUserData(void* data);
		void* GetUserData();
	protected:
		element el;
	private:
		void* mUserData;
	};
}


