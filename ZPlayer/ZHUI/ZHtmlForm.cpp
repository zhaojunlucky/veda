#include "stdafx.h"
#include "ZHtmlForm.h"
#include "UIToolKits.h"
#include <htmlayout_controls.hpp>
#include <htmlayout_dialog.hpp>
#include <htmlayout_dom.h>
#include <htmlayout_dom.hpp>
#include <htmlayout_graphin.h>
#include <htmlayout_notifications.hpp>
#include <htmlayout_queue.h>
#include <htmlayout_value.hpp>
#include <htmlayout_x.h>
#include <value.h>

namespace zhui
{
	ZHtmlForm::ZHtmlForm(HINSTANCE instance,const wchar_t* htmlRes, const ZFormPara& formPara, const wchar_t* title)
		:event_handler(0xFFFFFFFF), ZHUICtrl(0), mInstance(instance), mHtmlRes(htmlRes), mFormPara(formPara), mTitle(title)
	{
		InitForm();
	}


	ZHtmlForm::~ZHtmlForm()
	{
	}

	void ZHtmlForm::SetTitle(const wchar_t* wcTitle)
	{
		mTitle = NULL != wcTitle ? wcTitle:L"";
		SetWindowTextW(mHwnd, mTitle.c_str());
	}
	void ZHtmlForm::SetSize(const Size &size)
	{
		mFormPara.size = size;
		RECT rc;
		GetWindowRect(mHwnd, &rc);
		rc.right = mFormPara.size.width;
		rc.bottom = mFormPara.size.height;
		MoveWindow(rc);
	}
	void ZHtmlForm::SetPoint(const Point& point)
	{
		RECT rc;
		GetWindowRect(mHwnd, &rc);
		mFormPara.point = point;
		rc.left = point.x;
		rc.top = point.y;

		rc.right = rc.left + mFormPara.size.width;
		rc.bottom = rc.top + mFormPara.size.height;
		MoveWindow(rc);
	}
	const Size& ZHtmlForm::GetSize() const
	{
		return mFormPara.size;
	}
	const Point& ZHtmlForm::GetPoint() const
	{
		return mFormPara.point;
	}
	void ZHtmlForm::Show()
	{
		ShowWindow(mHwnd, 10);
		UpdateWindow(mHwnd);
	}

	void ZHtmlForm::Close()
	{
		SendMessage(mHwnd, WM_CLOSE, 0, 0);
	}

	void ZHtmlForm::MoveWindow(RECT& rect)
	{
		::MoveWindow(mHwnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);
	}

	void ZHtmlForm::InitForm()
	{
		RegisterWindowClass(mFormPara.appIcon, mFormPara.appIconSmall);
		mHwnd = CreateWindow(L"ZHtmlForm", mTitle.c_str(), WS_OVERLAPPEDWINDOW,
			mFormPara.point.x, mFormPara.point.y, mFormPara.size.width, mFormPara.size.height, NULL, NULL, mInstance, this);

		if (!mHwnd) 
		{
			throw ZFormException("fail to createwindow");
		}
		SetWindowLongPtr(mHwnd, GWLP_USERDATA, (DWORD)this);
		el = htmlayout::dom::element::root_element(mHwnd);
	}

	void ZHtmlForm::RegisterWindowClass(UINT appIcon, UINT appIconSmall)
	{
		WNDCLASSEX wcex = { 0 };
		wcex.cbSize = sizeof(WNDCLASSEX);
		HINSTANCE hInst = mInstance;
		if (!(::GetClassInfoEx(hInst, L"ZHtmlForm", &wcex)))
		{
			wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
			wcex.lpfnWndProc = WndProc;
			wcex.cbClsExtra = 0;
			wcex.cbWndExtra = 0;
			wcex.hInstance = hInst;
			wcex.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(appIcon));
			wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
			wcex.hbrBackground = NULL;//(HBRUSH)(COLOR_WINDOW+1);
			wcex.lpszClassName = L"ZHtmlForm";
			wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(appIconSmall));

			RegisterClassEx(&wcex);
		}
	}

	BOOL ZHtmlForm::GetHtmlResource(LPCWSTR pszName, /*out*/PBYTE& pb, /*out*/DWORD& cb)
	{
		// Find specified resource and check if ok

		HRSRC hrsrc = ::FindResourceW(mInstance, pszName, MAKEINTRESOURCE(RT_HTML));
		DWORD i = GetLastError();
		if (!hrsrc)
			return false;

		// Load specified resource and check if ok

		HGLOBAL hgres = ::LoadResource(mInstance, hrsrc);
		if (!hgres) return FALSE;

		// Retrieve resource data and check if ok

		pb = (PBYTE)::LockResource(hgres); if (!pb) return FALSE;
		cb = ::SizeofResource(mInstance, hrsrc); if (!cb) return FALSE;

		return TRUE;
	}

	LRESULT ZHtmlForm::LoadResourceData(HWND hWnd, LPCWSTR uri)
	{
		// Check for trivial case

		if (!uri || !uri[0]) return LOAD_DISCARD;

		if (wcsncmp(uri, L"res:", 4) == 0)
			uri += 4;
		else
			return LOAD_OK; // it is not a "res:*" so proceed with the default loader

		// Retrieve url specification into a local storage since FindResource() expects
		// to find its parameters on stack rather then on the heap under Win9x/Me

		wchar_t achURL[MAX_PATH]; wcsncpy(achURL, uri, MAX_PATH);

		// Separate name and handle external resource module specification

		LPWSTR pszName = achURL;

		// Separate extension if any

		LPWSTR pszExt = wcsrchr(pszName, '.'); if (pszExt) *pszExt++ = '\0';

		// Find specified resource and leave if failed. Note that we use extension
		// as the custom resource type specification or assume standard HTML resource
		// if no extension is specified

		HRSRC hrsrc = 0;
		bool  isHtml = false;
		if (pszExt == 0 || _wcsicmp(pszExt, L"HTML") == 0)
		{
			hrsrc = ::FindResourceW(mInstance, pszName, (LPCWSTR)RT_HTML);
			isHtml = true;
		}
		else
			hrsrc = ::FindResourceW(mInstance, pszName, pszExt);

		if (!hrsrc) return LOAD_OK; // resource not found here - proceed with default loader

		// Load specified resource and check if ok

		HGLOBAL hgres = ::LoadResource(mInstance, hrsrc);
		if (!hgres) return LOAD_DISCARD;

		// Retrieve resource data and check if ok

		PBYTE pb = (PBYTE)::LockResource(hgres); if (!pb) return LOAD_DISCARD;
		DWORD cb = ::SizeofResource(mInstance, hrsrc); if (!cb) return LOAD_DISCARD;

		// Report data ready

		::HTMLayoutDataReady(hWnd, uri, pb, cb);

		return LOAD_OK;
	}

	LRESULT CALLBACK ZHtmlForm::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		/*PAINTSTRUCT ps;
		HDC hdc;*/

		LRESULT lResult;
		BOOL    bHandled = FALSE;

		// HTMLayout +
		// HTMLayout could be created as separate window 
		// using CreateWindow API.
		// But in this case we are attaching HTMLayout functionality
		// to the existing window delegating windows message handling to 
		// HTMLayoutProcND function.
		lResult = HTMLayoutProcND(hWnd, message, wParam, lParam, &bHandled);
		if (bHandled)
			return lResult;
		// HTMLayout -
		ZHtmlForm* form = 0;
		if (WM_CREATE == message)
		{
			CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
			form = (ZHtmlForm*)cs->lpCreateParams;
		}
		else
		{
			form = (ZHtmlForm*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		}
		switch (message)
		{
			/*case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			{
			RECT r;
			GetClientRect(hWnd,&r);
			HBRUSH hb = CreateSolidBrush(0xffffffff);
			FillRect(hdc,&r,hb);
			DeleteObject(hb);
			}
			// TODO: Add any drawing code here...
			EndPaint(hWnd, &ps);
			break;*/
		case WM_CREATE:
		{
			//EnableBlurBehind ( hWnd );
			UIToolKits uit;
			uit.SetAeroTransparentBack(hWnd);

			// Normally HTMLayout sends its notifications
			// to its parent. 
			// In this particular case we are using callback function to receive and
			// and handle notification. Don't bother the desktop window (parent of this window)
			// by our notfications.

			HTMLayoutSetCallback(hWnd, form->HTMLayoutNotifyHandler, form);

			// attach DOM events handler so we will be able to receive DOM events like BUTTON_CLICK, HYPERLINK_CLICK, etc.
			//HTMLayoutWindowAttachEventHandler( hWnd, 
			//    DOMEventsHandler.element_proc, 
			//   &DOMEventsHandler, 
			//    DOMEventsHandler.subscribed_to);
			htmlayout::attach_event_handler(hWnd, form);

			WCHAR path[2048] = L"file://";
			GetModuleFileNameW(NULL, &path[7], 2048 - 7);

			PBYTE pb; DWORD cb;
			if (form->GetHtmlResource(form->mHtmlRes.c_str(), pb, cb))
				HTMLayoutLoadHtmlEx(hWnd, pb, cb, path); // we use path here so all relative links in the document will resolved against it.
			else
			{
				HTMLayoutLoadFile(hWnd, form->mHtmlRes.c_str());
			}
		} break;
		case WM_ERASEBKGND:
			return TRUE; // as HTMLayout will draw client area in full
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}

	BOOL ZHtmlForm::handle_event(HELEMENT he, BEHAVIOR_EVENT_PARAMS& params)
	{
		switch (params.cmd)
		{
		case BUTTON_CLICK:  Fire(ButtonClick, he, params);   break;// click on button
		case BUTTON_PRESS:  Fire(ButtonPress, he, params);            break;// mouse down or key down in button
		case BUTTON_STATE_CHANGED: Fire(ButtonStateChanged, he, params);     break;
		case EDIT_VALUE_CHANGING:  Fire(EditValueChanging, he, params);     break;// before text change
		case EDIT_VALUE_CHANGED:  Fire(EditValueChanged, he, params);      break;//after text change
		case SELECT_SELECTION_CHANGED: Fire(SelectSelectionChanged, he, params); break;// selection in <select> changed
		case SELECT_STATE_CHANGED: Fire(SelectStateChanged, he, params);     break;// node in select expanded/collapsed, heTarget is the node
		case POPUP_REQUEST:Fire(PopupRequest, he, params);
			break;// request to show popup just received, 
			//     here DOM of popup element can be modifed.
		case POPUP_READY:   Fire(PopupReady, he, params);            break;// popup element has been measured and ready to be shown on screen,
			//     here you can use functions like ScrollToView.
		case POPUP_DISMISSED:  Fire(PopupDismissed, he, params);         break;// popup element is closed,
			//     here DOM of popup element can be modifed again - e.g. some items can be removed
			//     to free memory.
		case MENU_ITEM_ACTIVE:  Fire(MenuItemActive, he, params);              // menu item activated by mouse hover or by keyboard
			break;
		case MENU_ITEM_CLICK:  Fire(MenuItemClick, he, params);               // menu item click 
			break;


			// "grey" event codes  - notfications from behaviors from this SDK 
		case HYPERLINK_CLICK:   Fire(HyperLinkClick, he, params);        break;// hyperlink click
		case TABLE_HEADER_CLICK:  Fire(TableHeaderClick, he, params);      break;// click on some cell in table header, 
			//     target = the cell, 
			//     reason = index of the cell (column number, 0..n)
		case TABLE_ROW_CLICK:  Fire(TableRowClick, he, params);         break;// click on data row in the table, target is the row
			//     target = the row, 
			//     reason = index of the row (fixed_rows..n)
		case TABLE_ROW_DBL_CLICK:  Fire(TableRowDoubleClick, he, params);     break;// mouse dbl click on data row in the table, target is the row
			//     target = the row, 
			//     reason = index of the row (fixed_rows..n)

		case ELEMENT_COLLAPSED:    Fire(ElementCollapsed, he, params);     break;// element was collapsed, so far only behavior:tabs is sending these two to the panels
		case ELEMENT_EXPANDED:     Fire(ElementExpanded, he, params);      break;// element was expanded,

		}
		return FALSE;
	}

	BOOL ZHtmlForm::handle_mouse(HELEMENT he, MOUSE_PARAMS& params)
	{
		switch (params.cmd)
		{
		case MOUSE_DOWN: FireMouseEvent(MouseDown,he,params,false); break;
		case MOUSE_DOWN | HANDLED: FireMouseEvent(MouseDown, he, params, true); break;
		case MOUSE_UP: FireMouseEvent(MouseUp, he, params, false); break;
		case MOUSE_UP | HANDLED: FireMouseEvent(MouseUp, he, params, true); break;
		case MOUSE_DCLICK: FireMouseEvent(MouseDoubleClick, he, params,false); break;
		case MOUSE_DCLICK | HANDLED: FireMouseEvent(MouseDoubleClick, he, params, true); break;
		}
		return FALSE;
	}
	LRESULT CALLBACK ZHtmlForm::HTMLayoutNotifyHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LPVOID vParam)
	{
		// all HTMLayout notification are comming here.
		NMHDR*  phdr = (NMHDR*)lParam;

		ZHtmlForm* form = (ZHtmlForm*)vParam;
		
		switch (phdr->code)
		{
		case HLN_CREATE_CONTROL:    return form->OnCreateControl((LPNMHL_CREATE_CONTROL)lParam);
		case HLN_CONTROL_CREATED:   return form->OnControlCreated((LPNMHL_CREATE_CONTROL)lParam);
		case HLN_DESTROY_CONTROL:   return form->OnDestroyControl((LPNMHL_DESTROY_CONTROL)lParam);
		case HLN_LOAD_DATA:         return form->OnLoadData((LPNMHL_LOAD_DATA)lParam);
		case HLN_DATA_LOADED:       return form->OnDataLoaded((LPNMHL_DATA_LOADED)lParam);
		case HLN_DOCUMENT_COMPLETE: return form->OnDocumentComplete();
		case HLN_ATTACH_BEHAVIOR:   return form->OnAttachBehavior((LPNMHL_ATTACH_BEHAVIOR)lParam);
		}
		return 0;
	}

	void ZHtmlForm::Fire(Event<void(const HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params)>& event, const HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params)
	{
		if (!event.IsNull())
		{
			event.mFunc(he, params);
		}
	}
	void ZHtmlForm::FireMouseEvent(Event<void(HELEMENT he, const MOUSE_PARAMS& params, bool handled)>& event, HELEMENT he, const MOUSE_PARAMS& params, bool handled)
	{
		if (!event.IsNull())
		{
			event.mFunc(he,params,handled);
		}
	}
	LRESULT ZHtmlForm::OnCreateControl(LPNMHL_CREATE_CONTROL control)
	{
		return 0;
	}

	LRESULT ZHtmlForm::OnControlCreated(LPNMHL_CREATE_CONTROL control)
	{
		return 0;
	}

	LRESULT ZHtmlForm::OnDestroyControl(LPNMHL_DESTROY_CONTROL control)
	{
		return 0;
	}

	LRESULT ZHtmlForm::OnLoadData(LPNMHL_LOAD_DATA data)
	{
		return LoadResourceData(data->hdr.hwndFrom, data->uri);
	}

	LRESULT ZHtmlForm::OnDataLoaded(LPNMHL_DATA_LOADED data)
	{
		return 0;
	}

	LRESULT ZHtmlForm::OnDocumentComplete()
	{
		return 0;
	}

	LRESULT ZHtmlForm::OnAttachBehavior(LPNMHL_ATTACH_BEHAVIOR behavior)
	{
		// attach custom behaviors
		htmlayout::behavior::handle(behavior);

		// behavior implementations are located om /include/behaviors/ folder
		// to connect them into the chain of available 
		// behaviors - just include them into the project.
		return 0;
	}

	htmlayout::dom::element& ZHtmlForm::GetRoot()
	{
		return el;
	}

	htmlayout::dom::element ZHtmlForm::FindElementById(const wchar_t* id)
	{
		return el.get_element_by_id(id);
	}
}
