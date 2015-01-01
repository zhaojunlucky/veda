#pragma once
#include <UIlib.h>
using namespace DuiLib;
#include "UIListCtrlCommon.h"
struct MusicListItemInfo
{
	bool isFolder;
	bool isEmpty;
	CDuiString id;
	CDuiString title;
	CDuiString album;
	CDuiString artist;
	CDuiString duration;
};

class CMusicListCtrl : public CListUI 
{
public:
	CMusicListCtrl(CPaintManagerUI& paint_manager);
	~CMusicListCtrl();

	bool Add(CControlUI* pControl);

	bool AddAt(CControlUI* pControl, int iIndex);

	bool Remove(CControlUI* pControl);

	bool RemoveAt(int iIndex);

	void RemoveAll();

	void DoEvent(TEventUI& event);

	Node* GetRoot();

	Node* AddNode(const MusicListItemInfo& item, Node* parent = NULL);

	bool RemoveNode(Node* node);

	void SetChildVisible(Node* node, bool visible);

	bool CanExpand(Node* node) const;

	bool SelectItem(int iIndex, bool bTakeFocus = false);

private:
	
	CListContainerElementUI* getFirstListNodeUIFromPoint(const POINT& pt);
	virtual void DoPostPaint(HDC hDC, const RECT& rcPaint);
private:
	Node*	mRootNode;
	bool mDoDragDrop;
	CListContainerElementUI* mFromNode;
	CListContainerElementUI* mLastHoverNode;
	CDuiRect	mTextPadding;
	int mLevelTextStartPos;
	CDuiString mLevelExpandImage;
	CDuiString mLevelCollapseImage;
	CPaintManagerUI& mPaintManager;
	HCURSOR mCursor;
	HCURSOR mDragDropCur;
	CDialogBuilder mDlgBuilder;
};

