#pragma once
#include <Windows.h>
#include <string>
#include <functional>
#include <htmlayout.h>
#include <htmlayout_behavior.hpp>
#include <htmlayout_canvas.hpp>
#include <htmlayout_aux.h>
#include "ZFormPara.h"
#include "ZFormException.h"
#include "Event.h"
#include "ZHUICtrl.h"

namespace zhui
{
	class __declspec(dllexport) ZHtmlForm : htmlayout::event_handler, ZHUICtrl
	{
	public:
		ZHtmlForm(HINSTANCE instance,const wchar_t* HtmlRes, const ZFormPara& formPara, const wchar_t* title);
		virtual ~ZHtmlForm();

		void SetTitle(const wchar_t* wcTitle);
		void SetSize(const Size &size);
		void SetPoint(const Point& point);
		const Size& GetSize() const;
		const Point& GetPoint() const;
		void Show();
		void Close();

	private:
		void MoveWindow(RECT& rect);
		void InitForm();
		void RegisterWindowClass(UINT appIcon, UINT appIconSmall);
		LRESULT LoadResourceData(HWND hWnd, LPCWSTR uri);
		BOOL GetHtmlResource(LPCWSTR pszName, /*out*/PBYTE& pb, /*out*/DWORD& cb);
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK HTMLayoutNotifyHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LPVOID vParam);
		virtual BOOL handle_event(HELEMENT he, BEHAVIOR_EVENT_PARAMS& params);
		virtual BOOL handle_mouse(HELEMENT he, MOUSE_PARAMS& params);
		void Fire(Event<void(const HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params)>& event, const HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params);
		void FireMouseEvent(Event<void(HELEMENT he, const MOUSE_PARAMS& params, bool handled)>& event, HELEMENT he, const MOUSE_PARAMS& params, bool handled);
	protected:
		virtual LRESULT OnCreateControl(LPNMHL_CREATE_CONTROL control);
		virtual LRESULT OnControlCreated(LPNMHL_CREATE_CONTROL control);
		virtual LRESULT OnDestroyControl(LPNMHL_DESTROY_CONTROL control);
		virtual LRESULT OnLoadData(LPNMHL_LOAD_DATA data);
		virtual LRESULT OnDataLoaded(LPNMHL_DATA_LOADED data);
		virtual LRESULT OnDocumentComplete();
		virtual LRESULT OnAttachBehavior(LPNMHL_ATTACH_BEHAVIOR behavior);
		htmlayout::dom::element& GetRoot();
		htmlayout::dom::element FindElementById(const wchar_t* id);
	protected:
		Event<void(HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params)> ButtonClick;
		Event<void(HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params)> ButtonPress;
		Event<void(HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params)> ButtonStateChanged;
		Event<void(HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params)> EditValueChanged;
		Event<void(HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params)> EditValueChanging;
		Event<void(HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params)> SelectSelectionChanged;
		Event<void(HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params)> SelectStateChanged;
		Event<void(HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params)> PopupRequest;
		Event<void(HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params)> PopupReady;
		Event<void(HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params)> PopupDismissed;
		Event<void(HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params)> MenuItemActive;
		Event<void(HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params)> MenuItemClick;
		Event<void(HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params)> HyperLinkClick;
		Event<void(HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params)> TableHeaderClick;		
		Event<void(HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params)> TableRowClick;
		Event<void(HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params)> TableRowDoubleClick;
		Event<void(HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params)> ElementCollapsed;
		Event<void(HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params)> ElementExpanded;
		Event<void(HELEMENT he, const MOUSE_PARAMS& params, bool handled)> MouseDown;
		Event<void(HELEMENT he, const MOUSE_PARAMS& params, bool handled)> MouseUp;
		Event<void(HELEMENT he, const MOUSE_PARAMS& params, bool handled)> MouseDoubleClick;
	private:
		HINSTANCE mInstance;
		ZFormPara mFormPara;
		std::wstring mTitle;
		std::wstring mHtmlRes;
		HWND mHwnd;
	};
}


