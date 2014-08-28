#include "MusicListCtrl.h"


CMusicListCtrl::CMusicListCtrl(CPaintManagerUI& paint_manager)
	:mRootNode(0), mDelayDeltaY(0), mDelayNumber(0), mDelayLeft(0),
	mLevelExpandImage(_T("<i list_icon_b.png>")),
	mLevelCollapseImage(_T("<i list_icon_a.png>")),
	mLevelTextStartPos(10),
	mTextPadding(10,0,0,0),
	mPaintManager(paint_manager)
{
	SetItemShowHtml(true);
	mRootNode = new Node;
	mRootNode->getData().level = -1;
	mRootNode->getData().childVisible = true;
	mRootNode->getData().hasChild = true;
	mRootNode->getData().listElement = 0;
}
CMusicListCtrl::~CMusicListCtrl()
{
	if (mRootNode)
	{
		delete mRootNode;
		mRootNode = 0;
	}
}

bool CMusicListCtrl::Add(CControlUI* pControl)
{
	if (!pControl)
	{
		return false;
	}
	if (_tcsicmp(pControl->GetClass(), _T("ListContainerElementUI")) != 0)
		return false;

	return CListUI::Add(pControl);
}

bool CMusicListCtrl::AddAt(CControlUI* pControl, int iIndex)
{
	if (!pControl)
		return false;

	if (_tcsicmp(pControl->GetClass(), _T("ListContainerElementUI")) != 0)
		return false;

	return CListUI::AddAt(pControl, iIndex);
}

bool CMusicListCtrl::Remove(CControlUI* pControl)
{
	if (!pControl)
		return false;

	if (_tcsicmp(pControl->GetClass(), _T("ListContainerElementUI")) != 0)
		return false;

	if (reinterpret_cast<Node*>(static_cast<CListContainerElementUI*>(pControl->GetInterface(_T("ListContainerElement")))->GetTag()) == NULL)
		return CListUI::Remove(pControl);
	else
		return RemoveNode(reinterpret_cast<Node*>(static_cast<CListContainerElementUI*>(pControl->GetInterface(_T("ListContainerElement")))->GetTag()));
}

bool CMusicListCtrl::RemoveAt(int iIndex)
{
	CControlUI* pControl = GetItemAt(iIndex);
	if (!pControl)
		return false;

	if (_tcsicmp(pControl->GetClass(), _T("ListContainerElementUI")) != 0)
		return false;

	if (reinterpret_cast<Node*>(static_cast<CListContainerElementUI*>(pControl->GetInterface(_T("ListContainerElement")))->GetTag()) == NULL)
		return CListUI::RemoveAt(iIndex);
	else
		return RemoveNode(reinterpret_cast<Node*>(static_cast<CListContainerElementUI*>(pControl->GetInterface(_T("ListContainerElement")))->GetTag()));
}

void CMusicListCtrl::RemoveAll()
{
	CListUI::RemoveAll();
	for (int i = 0; i < mRootNode->getChildCount(); ++i)
	{
		Node* child = mRootNode->getChild(i);
		RemoveNode(child);
	}
	delete mRootNode;

	mRootNode = new Node;
	mRootNode->getData().level = -1;
	mRootNode->getData().childVisible = true;
	mRootNode->getData().hasChild = true;
	mRootNode->getData().listElement = 0;
}

void CMusicListCtrl::DoEvent(TEventUI& event)
{
	if (!IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND)
	{
		if (m_pParent != NULL)
			m_pParent->DoEvent(event);
		else
			CVerticalLayoutUI::DoEvent(event);
		return;
	}

	if (event.Type == UIEVENT_TIMER && event.wParam == SCROLL_TIMERID)
	{
		if (mDelayLeft > 0)
		{
			--mDelayLeft;
			SIZE sz = GetScrollPos();
			LONG lDeltaY = (LONG)(calculateDelay((double)mDelayLeft / mDelayNumber) * mDelayDeltaY);
			if ((lDeltaY > 0 && sz.cy != 0) || (lDeltaY < 0 && sz.cy != GetScrollRange().cy))
			{
				sz.cy -= lDeltaY;
				SetScrollPos(sz);
				return;
			}
		}
		mDelayDeltaY = 0;
		mDelayNumber = 0;
		mDelayLeft = 0;
		m_pManager->KillTimer(this, SCROLL_TIMERID);
		return;
	}
	if (event.Type == UIEVENT_SCROLLWHEEL)
	{
		LONG lDeltaY = 0;
		if (mDelayNumber > 0)
			lDeltaY = (LONG)(calculateDelay((double)mDelayLeft / mDelayNumber) * mDelayDeltaY);
		switch (LOWORD(event.wParam))
		{
		case SB_LINEUP:
			if (mDelayDeltaY >= 0)
				mDelayDeltaY = lDeltaY + 8;
			else
				mDelayDeltaY = lDeltaY + 12;
			break;
		case SB_LINEDOWN:
			if (mDelayDeltaY <= 0)
				mDelayDeltaY = lDeltaY - 8;
			else
				mDelayDeltaY = lDeltaY - 12;
			break;
		}
		if
			(mDelayDeltaY > 100) mDelayDeltaY = 100;
		else if
			(mDelayDeltaY < -100) mDelayDeltaY = -100;

		mDelayNumber = (DWORD)sqrt((double)abs(mDelayDeltaY)) * 5;
		mDelayLeft = mDelayNumber;
		m_pManager->SetTimer(this, SCROLL_TIMERID, 50U);
		return;
	}

	CListUI::DoEvent(event);
}

Node* CMusicListCtrl::GetRoot()
{
	return mRootNode;
}

const TCHAR* const TITLE_CTRL = _T("");
const TCHAR* const ARTIST_CTRL = _T("");
const TCHAR* const ALBUM_CTRL = _T("");
const TCHAR* const DURATION_CTRL = _T("");
const int ITEM_NORMAL_HEIGHT = 32;
const int ITEM_SELCTED_HEIGHT = 50;

static bool OnLogoButtonEvent(void* event) {
	if (((TEventUI*)event)->Type == UIEVENT_BUTTONDOWN) {
		CControlUI* pButton = ((TEventUI*)event)->pSender;
		if (pButton != NULL) {
			CListContainerElementUI* pListElement = (CListContainerElementUI*)(pButton->GetTag());
			if (pListElement != NULL) pListElement->DoEvent(*(TEventUI*)event);
		}
	}
	return true;
}

Node* CMusicListCtrl::AddNode(const MusicListItemInfo& item, Node* parent)
{
	if (!parent)
		parent = mRootNode;

	TCHAR szBuf[MAX_PATH] = { 0 };

	CListContainerElementUI* pListElement = NULL;
	if (!mDlgBuilder.GetMarkup()->IsValid()) {
		pListElement = static_cast<CListContainerElementUI*>(mDlgBuilder.Create(_T("friend_list_item.xml"), (UINT)0, NULL, &mPaintManager));
	}
	else {
		pListElement = static_cast<CListContainerElementUI*>(mDlgBuilder.Create((UINT)0, &mPaintManager));
	}
	if (pListElement == NULL)
		return NULL;

	Node* node = new Node;

	node->getData().level = parent->getData().level + 1;
	if (item.isFolder)
		node->getData().hasChild = !item.isEmpty;
	else
		node->getData().hasChild = false;

	node->getData().folder = item.isFolder;

	node->getData().childVisible = (node->getData().level == 0);
	node->getData().childVisible = false;

	node->getData().text = item.title;
	node->getData().value = item.id;
	node->getData().listElement = pListElement;

	if (!parent->getData().childVisible)
		pListElement->SetVisible(false);

	if (parent != mRootNode && !parent->getData().listElement->IsVisible())
		pListElement->SetVisible(false);

	CDuiRect rcPadding = mTextPadding;
	for (int i = 0; i < node->getData().level; ++i)
	{
		rcPadding.left += mLevelTextStartPos;
	}
	pListElement->SetPadding(rcPadding);

	CDuiString html_text;
	if (node->getData().hasChild)
	{
		if (node->getData().childVisible)
			html_text += mLevelExpandImage;
		else
			html_text += mLevelCollapseImage;

#if defined(UNDER_WINCE)
		_stprintf(szBuf, _T("<x %d>"), mLevelTextStartPos);
#else
		_stprintf_s(szBuf, MAX_PATH - 1, _T("<x %d>"), mLevelTextStartPos);
#endif
		html_text += szBuf;
	}

	if (item.isFolder)
	{
		html_text += node->getData().text;
	}
	else
	{
#if defined(UNDER_WINCE)
		_stprintf(szBuf, _T("%s"), item.title);
#else
		_stprintf_s(szBuf, MAX_PATH - 1, _T("%s"), item.title);
#endif
		html_text += szBuf;
	}

	CLabelUI* title = static_cast<CLabelUI*>(mPaintManager.FindSubControlByName(pListElement, TITLE_CTRL));
	if (title != NULL)
	{
		if (item.isFolder)
			title->SetFixedWidth(0);

		title->SetShowHtml(true);
		title->SetText(html_text);
	}

	if (!item.isFolder && !item.artist.IsEmpty())
	{
		CLabelUI* artist = static_cast<CLabelUI*>(mPaintManager.FindSubControlByName(pListElement, ARTIST_CTRL));
		if (artist != NULL)
		{
#if defined(UNDER_WINCE)
			_stprintf(szBuf, _T("<x 20><c #808080>%s</c>"), item.artist);
#else
			_stprintf_s(szBuf, MAX_PATH - 1, _T("<x 20><c #808080>%s</c>"), item.artist);
#endif
			artist->SetShowHtml(true);
			artist->SetText(szBuf);
		}
	}

	if (!item.isFolder && !item.album.IsEmpty())
	{
		CLabelUI* album = static_cast<CLabelUI*>(mPaintManager.FindSubControlByName(pListElement, ALBUM_CTRL));
		if (album != NULL)
		{
#if defined(UNDER_WINCE)
			_stprintf(szBuf, _T("<x 20><c #808080>%s</c>"), item.album);
#else
			_stprintf_s(szBuf, MAX_PATH - 1, _T("<x 20><c #808080>%s</c>"), item.album);
#endif
			album->SetShowHtml(true);
			album->SetText(szBuf);
		}
	}

	if (!item.isFolder && !item.duration.IsEmpty())
	{
		CLabelUI* duration = static_cast<CLabelUI*>(mPaintManager.FindSubControlByName(pListElement, DURATION_CTRL));
		if (duration != NULL)
		{
#if defined(UNDER_WINCE)
			_stprintf(szBuf, _T("<x 20><c #808080>%s</c>"), item.duration);
#else
			_stprintf_s(szBuf, MAX_PATH - 1, _T("<x 20><c #808080>%s</c>"), item.duration);
#endif
			duration->SetShowHtml(true);
			duration->SetText(szBuf);
		}
	}

	pListElement->SetFixedHeight(ITEM_NORMAL_HEIGHT);
	pListElement->SetTag((UINT_PTR)node);
	int index = 0;
	if (parent->hasChild())
	{
		Node* prev = parent->getLastChild();
		index = prev->getData().listElement->GetIndex() + 1;
	}
	else
	{
		if (parent == mRootNode)
			index = 0;
		else
			index = parent->getData().listElement->GetIndex() + 1;
	}
	if (!CListUI::AddAt(pListElement, index))
	{
		delete pListElement;
		delete node;
		node = NULL;
	}

	parent->addChild(node);
	return node;
}

bool CMusicListCtrl::RemoveNode(Node* node)
{
	if (!node || node == mRootNode) return false;

	for (int i = 0; i < node->getChildCount(); ++i)
	{
		Node* child = node->getChild(i);
		RemoveNode(child);
	}

	CListUI::Remove(node->getData().listElement);
	node->getParent()->removeChild(node);
	delete node;

	return true;
}

void CMusicListCtrl::SetChildVisible(Node* node, bool visible)
{
	if (!node || node == mRootNode)
		return;

	if (node->getData().childVisible == visible)
		return;

	node->getData().childVisible = visible;

	TCHAR szBuf[MAX_PATH] = { 0 };
	CDuiString html_text;
	if (node->getData().hasChild)
	{
		if (node->getData().childVisible)
			html_text += mLevelExpandImage;
		else
			html_text += mLevelCollapseImage;

#if defined(UNDER_WINCE)
		_stprintf(szBuf, _T("<x %d>"), mLevelTextStartPos);
#else
		_stprintf_s(szBuf, MAX_PATH - 1, _T("<x %d>"), mLevelTextStartPos);
#endif
		html_text += szBuf;

		html_text += node->getData().text;

		CLabelUI* title = static_cast<CLabelUI*>(mPaintManager.FindSubControlByName(node->getData().listElement, TITLE_CTRL));
		if (title != NULL)
		{
			title->SetShowHtml(true);
			title->SetText(html_text);
		}
	}

	if (!node->getData().listElement->IsVisible())
		return;

	if (!node->hasChild())
		return;

	Node* begin = node->getChild(0);
	Node* end = node->getLastChild();
	for (int i = begin->getData().listElement->GetIndex(); i <= end->getData().listElement->GetIndex(); ++i)
	{
		CControlUI* control = GetItemAt(i);
		if (_tcsicmp(control->GetClass(), _T("ListContainerElementUI")) == 0)
		{
			if (visible)
			{
				Node* local_parent = ((Node*)control->GetTag())->getParent();
				if (local_parent->getData().childVisible && local_parent->getData().listElement->IsVisible())
				{
					control->SetVisible(true);
				}
			}
			else
			{
				control->SetVisible(false);
			}
		}
	}
}

bool CMusicListCtrl::CanExpand(Node* node) const
{
	if (!node || node == mRootNode)
		return false;

	return node->getData().hasChild;
}

bool CMusicListCtrl::SelectItem(int iIndex, bool bTakeFocus)
{
	if (iIndex == m_iCurSel) return true;

	// We should first unselect the currently selected item
	if (m_iCurSel >= 0) {
		CControlUI* pControl = GetItemAt(m_iCurSel);
		if (pControl != NULL) {
			IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
			if (pListItem != NULL)
			{
				CListContainerElementUI* pFriendListItem = static_cast<CListContainerElementUI*>(pControl);
				Node* node = (Node*)pControl->GetTag();
				if ((pFriendListItem != NULL) && (node != NULL) && !node->isFolder())
				{
					pFriendListItem->SetFixedHeight(ITEM_NORMAL_HEIGHT);
				}
				pListItem->Select(false);
			}
		}

		m_iCurSel = -1;
	}

	if (iIndex < 0)
		return false;

	if (!__super::SelectItem(iIndex, bTakeFocus))
		return false;


	CControlUI* pControl = GetItemAt(m_iCurSel);
	if (pControl != NULL) {
		CListContainerElementUI* pFriendListItem = static_cast<CListContainerElementUI*>(pControl);
		Node* node = (Node*)pControl->GetTag();
		if ((pFriendListItem != NULL) && (node != NULL) && !node->isFolder())
		{
			pFriendListItem->SetFixedHeight(ITEM_SELCTED_HEIGHT);
		}
	}
	return true;
}