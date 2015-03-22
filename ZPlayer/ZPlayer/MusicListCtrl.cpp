#include "MusicListCtrl.h"
#include <Logger.h>
using namespace veda;
extern Logger logger;
#include "resource.h"
#include "UIMenu.h"


CMusicListCtrl::CMusicListCtrl(CPaintManagerUI& paint_manager)
	://mRootNode(0),//, mDelayDeltaY(0), mDelayNumber(0), mDelayLeft(0),
	//mLevelExpandImage(_T("<i ui/list_icon_b.png>")),
	//mLevelCollapseImage(_T("<i ui/list_icon_a.png>")),
	//mLevelTextStartPos(10),
	mTextPadding(10,0,0,0),
	mPaintManager(paint_manager)
{
	mFromNode = NULL;
	mLastHoverNode = NULL;
	/*mRootNode = new Node;
	mRootNode->getData().level = -1;
	mRootNode->getData().childVisible = true;
	mRootNode->getData().hasChild = true;
	mRootNode->getData().listElement = 0;*/
	mDragDropCur = LoadCursor(CPaintManagerUI::GetInstance(), MAKEINTRESOURCE(IDC_DRAG_DROP));
	mDoDragDrop = false;
}
CMusicListCtrl::~CMusicListCtrl()
{
	/*if (mRootNode)
	{
		delete mRootNode;
		mRootNode = 0;
	}*/
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

	//if (reinterpret_cast<Node*>(static_cast<CListContainerElementUI*>(pControl->GetInterface(_T("ListContainerElement")))->GetTag()) == NULL)
		return CListUI::Remove(pControl);
	//else
		//return RemoveNode(reinterpret_cast<Node*>(static_cast<CListContainerElementUI*>(pControl->GetInterface(_T("ListContainerElement")))->GetTag()));
}

bool CMusicListCtrl::RemoveAt(int iIndex)
{
	CControlUI* pControl = GetItemAt(iIndex);
	if (!pControl)
		return false;

	if (_tcsicmp(pControl->GetClass(), _T("ListContainerElementUI")) != 0)
		return false;

	//if (reinterpret_cast<Node*>(static_cast<CListContainerElementUI*>(pControl->GetInterface(_T("ListContainerElement")))->GetTag()) == NULL)
	return CListUI::RemoveAt(iIndex);
	//else
		//return RemoveNode(reinterpret_cast<Node*>(static_cast<CListContainerElementUI*>(pControl->GetInterface(_T("ListContainerElement")))->GetTag()));
}

void CMusicListCtrl::RemoveAll()
{
	CListUI::RemoveAll();
	/*for (int i = 0; i < mRootNode->getChildCount(); ++i)
	{
		Node* child = mRootNode->getChild(i);
		RemoveNode(child);
	}
	delete mRootNode;

	mRootNode = new Node;
	mRootNode->getData().level = -1;
	mRootNode->getData().childVisible = true;
	mRootNode->getData().hasChild = true;
	mRootNode->getData().listElement = 0;*/
}

void CMusicListCtrl::DoEvent(TEventUI& event)
{
	//static Color defaultItemBKColor(0, 0, 0, 0);
	//static Color hoverItemBKColor(255, 168, 141, 120);
	if (event.Type == UIEVENT_RBUTTONDOWN && IsEnabled())
	{
		auto node = getFirstListNodeUIFromPoint(event.ptMouse);
		if (node != NULL)
		{
			veda::VEvent e;
			auto p = VEBind(&CMusicListCtrl::onContextMenu, this);
			CMenuWnd* pMenu = new CMenuWnd(mPaintManager.GetPaintWindow());
			
			//pMenu->MenuClick += std::move(p);//VEBind(&CMusicListCtrl::onContextMenu, this);
			//pMenu->MenuClick.attach( VEBind(&CMusicListCtrl::onContextMenu, this));
			//hook(&pMenu->ev, &CMusicListCtrl::onContextMenu);
			__hook(&__Event::trigger, &pMenu->ev, &CMusicListCtrl::onContextMenu);
			CPoint point = event.ptMouse; 
			ClientToScreen(mPaintManager.GetPaintWindow(), &point);
			pMenu->Init(NULL, L"ui\\menu\\menutest.xml", _T("xml"), point);

		}
	}
	if (event.Type == UIEVENT_BUTTONDOWN && IsEnabled())
	{
		mFromNode = getFirstListNodeUIFromPoint(event.ptMouse);
		//LOG_INFO(logger) << L"drag drop start" << endl;
		//mPaintManager.AddPostPaint(this);
		/*mCursor = ::GetCursor();
		::SetCursor(mDragDropCur);*/
	}
	else if (event.Type == UIEVENT_BUTTONUP && IsEnabled())
	{
		if (mDoDragDrop)
		{
			auto pNode = getFirstListNodeUIFromPoint(event.ptMouse);
			//LOG_INFO(logger) << L"drag drop end" << endl;
			if (pNode != mFromNode)
			{
				//LOG_INFO(logger) << L"not equal" << endl;
				//LOG_INFO(logger) << L"from Index:" << mFromNode->GetIndex() << L", to index:" << pNode->GetIndex() << endl;
				// call back
				//(*mDragDropCallback)(mFromNode->GetIndex(), pNode->GetIndex());
				if (m_pManager != NULL)
				{
					m_pManager->SendNotify(this, L"dragdrop", mFromNode->GetIndex(), pNode->GetIndex());
				}
			}
			mPaintManager.RemovePostPaint(this);
			
			//if (mLastHoverNode != NULL)
			//{
			//	mLastHoverNode->SetBkColor(defaultItemBKColor.GetValue());
			//}
			
			SetCursor(mCursor);
			mDoDragDrop = false;
		}
		mFromNode = NULL;
		mLastHoverNode = NULL;
	}
	else if (UIEVENT_MOUSELEAVE == event.Type && IsEnabled())
	{
		if (mLastHoverNode != NULL)
		{
			showDelBtn(mLastHoverNode, false);
		}
		mLastHoverNode = NULL;
	}
	else if (UIEVENT_MOUSEMOVE == event.Type && IsEnabled())
	{
		// draw shadow
		auto hoverNode = getFirstListNodeUIFromPoint(event.ptMouse);
		if (mFromNode != NULL)
		{
			if (!mDoDragDrop)
			{
				mCursor = ::GetCursor();
				::SetCursor(mDragDropCur);
				mDoDragDrop = true;
				mPaintManager.AddPostPaint(this);
			}
		}

		if (mLastHoverNode != NULL && mLastHoverNode != hoverNode)
		{
			showDelBtn(mLastHoverNode, false);
		}
		if (hoverNode)
		{
			showDelBtn(hoverNode, true);
		}
		if (hoverNode != NULL && hoverNode != mFromNode)
		{
			if (hoverNode != mLastHoverNode)
			{
				/*if (mLastHoverNode != NULL)
				{
					if (mDoDragDrop)
					{
						mLastHoverNode->SetBkColor(defaultItemBKColor.GetValue());
					}
				}*/

				mLastHoverNode = hoverNode;
				/*if (mDoDragDrop)
				{
					hoverNode->SetBkColor(hoverItemBKColor.GetValue());
				}*/
			}
		}
		else
		{
			/*if (mLastHoverNode != NULL)
			{
				if (mDoDragDrop)
				{
					mLastHoverNode->SetBkColor(defaultItemBKColor.GetValue());
				}
			}*/
			mLastHoverNode = NULL;
		}
	}

	CListUI::DoEvent(event);
}

//Node* CMusicListCtrl::GetRoot()
//{
//	return mRootNode;
//}

const TCHAR* const TITLE_CTRL = _T("title");
const TCHAR* const ARTIST_CTRL = _T("artist");
const TCHAR* const ALBUM_CTRL = _T("album");
const TCHAR* const DURATION_CTRL = _T("duration");
const TCHAR* const DETAILS_CTRL = _T("details");
const TCHAR* const DEL_CTRL = _T("del");
const int ITEM_NORMAL_HEIGHT = 32;
const int ITEM_SELCTED_HEIGHT = 50;

static bool OnDelButtonEvent(void* event) {
	auto e = (TEventUI*)event;
	if (e->Type == UIEVENT_BUTTONDOWN) {
		CControlUI* pButton = ((TEventUI*)event)->pSender;
		if (pButton != NULL) {
			CListContainerElementUI* pListElement = (CListContainerElementUI*)(pButton->GetTag());
			
			CMusicListCtrl* mlc = (CMusicListCtrl*)pListElement->GetTag();
			mlc->sendDeleteMessage(pListElement);
		}
	}
	return true;
}


void CMusicListCtrl::AddItem(const MusicListItemInfo& item, int index)
{
	/*if (!parent)
		parent = mRootNode;*/

	TCHAR szBuf[MAX_PATH] = { 0 };

	CListContainerElementUI* pListElement = NULL;
	if (!mDlgBuilder.GetMarkup()->IsValid()) {
		pListElement = static_cast<CListContainerElementUI*>(mDlgBuilder.Create(_T("ui/music_list_item.xml"), (UINT)0, NULL, &mPaintManager));
	}
	else {
		pListElement = static_cast<CListContainerElementUI*>(mDlgBuilder.Create((UINT)0, &mPaintManager));
	}
	if (pListElement == NULL)
		return ;
	
	//Node* node = new Node;

	//node->getData().level = parent->getData().level + 1;
	//if (item.isFolder)
	//	node->getData().hasChild = !item.isEmpty;
	//else
	//	node->getData().hasChild = false;

	//node->getData().folder = item.isFolder;

	//node->getData().childVisible = (node->getData().level == 0);
	//node->getData().childVisible = false;

	//node->getData().text = item.title;
	//node->getData().value = item.id;
	//node->getData().listElement = pListElement;

	//if (!parent->getData().childVisible)
	//	pListElement->SetVisible(false);

	//if (parent != mRootNode && !parent->getData().listElement->IsVisible())
	//	pListElement->SetVisible(false);

	//CDuiRect rcPadding = mTextPadding;
	//for (int i = 0; i < node->getData().level; ++i)
	//{
	//	rcPadding.left += mLevelTextStartPos;
	//}
	pListElement->SetPadding(mTextPadding);

	//CDuiString html_text;
	//if (node->getData().hasChild)
	//{
	//	//if (node->getData().childVisible)
	//	//	html_text += mLevelExpandImage;
	//	//else
	//	//	html_text += mLevelCollapseImage;

	//	//_stprintf_s(szBuf, MAX_PATH - 1, _T("<x %d>"), mLevelTextStartPos);

	//	//html_text += szBuf;
	//}

	//if (item.isFolder)
	//{
	//	html_text += node->getData().text;
	//}
	//else
	//{
	//	_stprintf_s(szBuf, MAX_PATH - 1, _T("%s"), item.title.GetData());
	//	html_text += szBuf;
	//}
	pListElement->SetTag((UINT_PTR)this);
	CButtonUI* del = static_cast<CButtonUI*>(mPaintManager.FindSubControlByName(pListElement, DEL_CTRL));
	if (del != NULL)
	{
		del->OnEvent += MakeDelegate(&OnDelButtonEvent);
		del->SetTag((UINT_PTR)pListElement);
	}
	CLabelUI* title = static_cast<CLabelUI*>(mPaintManager.FindSubControlByName(pListElement, TITLE_CTRL));
	if (title != NULL)
	{
		if (item.isFolder)
			title->SetFixedWidth(0);

		//title->SetShowHtml(true);
		title->SetText(item.title.GetData());
	}

	if (!item.isFolder && !item.artist.IsEmpty())
	{
		CLabelUI* artist = static_cast<CLabelUI*>(mPaintManager.FindSubControlByName(pListElement, ARTIST_CTRL));
		if (artist != NULL)
		{
			//_stprintf_s(szBuf, MAX_PATH - 1, _T("<x 0><c #808080>%s</c>"), item.artist.GetData());
			//artist->SetShowHtml(true);
			artist->SetText(item.artist.GetData());
		}
	}

	if (!item.isFolder && !item.album.IsEmpty())
	{
		CLabelUI* album = static_cast<CLabelUI*>(mPaintManager.FindSubControlByName(pListElement, ALBUM_CTRL));
		if (album != NULL)
		{
			//_stprintf_s(szBuf, MAX_PATH - 1, _T("<x 0><c #808080>%s</c>"), item.album.GetData());
			//album->SetShowHtml(true);
			album->SetText(item.album.GetData());
		}
	}

	if (!item.isFolder && !item.duration.IsEmpty())
	{
		CLabelUI* duration = static_cast<CLabelUI*>(mPaintManager.FindSubControlByName(pListElement, DURATION_CTRL));
		if (duration != NULL)
		{
			//_stprintf_s(szBuf, MAX_PATH - 1, _T("<x 0><c #808080>%s</c>"), item.duration.GetData());
			//duration->SetShowHtml(true);
			duration->SetText(szBuf);
		}
	}

	pListElement->SetFixedHeight(ITEM_NORMAL_HEIGHT);
	//pListElement->SetTag((UINT_PTR)node);
	//int index = 0;
	//if (parent->hasChild())
	//{
	//	Node* prev = parent->getLastChild();
	//	index = prev->getData().listElement->GetIndex() + 1;
	//}
	//else
	//{
	//	if (parent == mRootNode)
	//		index = 0;
	//	else
	//		index = parent->getData().listElement->GetIndex() + 1;
	//}
	bool add = false;
	if (index == -1)
	{
		add = CListUI::Add(pListElement);
	}
	else
	{
		add = CListUI::AddAt(pListElement,index);
	}
	if (!add)
	{
		delete pListElement;
		//delete node;
		//node = NULL;
	}

	//parent->addChild(node);
	//return node;
}

//bool CMusicListCtrl::RemoveNode(Node* node)
//{
//	if (!node || node == mRootNode) return false;
//
//	for (int i = 0; i < node->getChildCount(); ++i)
//	{
//		Node* child = node->getChild(i);
//		RemoveNode(child);
//	}
//
//	CListUI::Remove(node->getData().listElement);
//	node->getParent()->removeChild(node);
//	delete node;
//
//	return true;
//}
//
//void CMusicListCtrl::SetChildVisible(Node* node, bool visible)
//{
//	if (!node || node == mRootNode)
//		return;
//
//	if (node->getData().childVisible == visible)
//		return;
//
//	node->getData().childVisible = visible;
//
//	TCHAR szBuf[MAX_PATH] = { 0 };
//	CDuiString html_text;
//	if (node->getData().hasChild)
//	{
//		/*if (node->getData().childVisible)
//			html_text += mLevelExpandImage;
//		else
//			html_text += mLevelCollapseImage;
//
//		_stprintf_s(szBuf, MAX_PATH - 1, _T("<x %d>"), mLevelTextStartPos);
//
//		html_text += szBuf;*/
//
//		html_text += node->getData().text;
//
//		CLabelUI* title = static_cast<CLabelUI*>(mPaintManager.FindSubControlByName(node->getData().listElement, TITLE_CTRL));
//		if (title != NULL)
//		{
//			//title->SetShowHtml(true);
//			title->SetText(html_text);
//		}
//	}
//
//	if (!node->getData().listElement->IsVisible())
//		return;
//
//	if (!node->hasChild())
//		return;
//
//	Node* begin = node->getChild(0);
//	Node* end = node->getLastChild();
//	for (int i = begin->getData().listElement->GetIndex(); i <= end->getData().listElement->GetIndex(); ++i)
//	{
//		CControlUI* control = GetItemAt(i);
//		if (_tcsicmp(control->GetClass(), _T("ListContainerElementUI")) == 0)
//		{
//			if (visible)
//			{
//				Node* local_parent = ((Node*)control->GetTag())->getParent();
//				if (local_parent->getData().childVisible && local_parent->getData().listElement->IsVisible())
//				{
//					control->SetVisible(true);
//				}
//			}
//			else
//			{
//				control->SetVisible(false);
//			}
//		}
//	}
//}

//bool CMusicListCtrl::CanExpand(Node* node) const
//{
//	if (!node || node == mRootNode)
//		return false;
//
//	return node->getData().hasChild;
//}

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
				CListContainerElementUI* pMusicListItem = static_cast<CListContainerElementUI*>(pControl);
				//Node* node = (Node*)pControl->GetTag();
				if (pMusicListItem != NULL)
				{
					pMusicListItem->SetFixedHeight(ITEM_NORMAL_HEIGHT);
					CContainerUI* pDetailsPanel = static_cast<CContainerUI*>(mPaintManager.FindSubControlByName(pMusicListItem, DETAILS_CTRL));
					if (pDetailsPanel != NULL)
					{
						pDetailsPanel->SetVisible(false);
					}
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
		CListContainerElementUI* pMusicListItem = static_cast<CListContainerElementUI*>(pControl);
		//Node* node = (Node*)pControl->GetTag();
		if (pMusicListItem != NULL)
		{
			pMusicListItem->SetFixedHeight(ITEM_SELCTED_HEIGHT);
			CContainerUI* pDetailsPanel = static_cast<CContainerUI*>(mPaintManager.FindSubControlByName(pMusicListItem, DETAILS_CTRL));
			if (pDetailsPanel != NULL)
			{
				
				auto rc = this->GetItemAt(m_iCurSel)->GetPos();
				pDetailsPanel->SetVisible(true);
				if (rc.top == 37)
				{
					Scroll(0, -18);
				}
				
			}
		}
	}
	return true;
}

void CMusicListCtrl::sendDeleteMessage(CListContainerElementUI* pListElement)
{
	if (pListElement != NULL && m_pManager != NULL)
	{
		if (mLastHoverNode == pListElement)
		{
			mLastHoverNode = NULL;
		}
		m_pManager->SendNotify(this, L"dellistitem", pListElement->GetIndex());
	}
}

CListContainerElementUI* CMusicListCtrl::getFirstListNodeUIFromPoint(const POINT& pt)
{
	LPVOID lpControl = NULL;
	CControlUI* pControl = m_pManager->FindSubControlByPoint(this, pt);
	while (pControl)
	{
		lpControl = pControl->GetInterface(DUI_CTR_LISTCONTAINERELEMENT);
		if (lpControl != NULL)
		{
			break;
		}
		pControl = pControl->GetParent();
	}
	if (lpControl)
	{
		return static_cast<CListContainerElementUI*>(lpControl);
	}
	else
		return NULL;
}

void CMusicListCtrl::DoPostPaint(HDC hDC, const RECT& rcPaint)
{
	//LOG_INFO(logger) << L"paint" << endl;
	//if (mDoDragDrop)
	{
		/*CDuiRect rcParent = m_pParent->GetPos();
		RECT rcUpdate = rcPaint;
		static Color hoverItemBKColor(0, 0, 0, 0);
		CRenderEngine::DrawTextW(hDC, &mPaintManager, rcUpdate, mFromNode->fin, hoverItemBKColor.GetValue(), 0, 0);*/
	}
}

void CMusicListCtrl::showDelBtn(CListContainerElementUI* pList, bool visible)
{
	auto pDelBtn = pList->FindSubControl(DEL_CTRL);
	if (pDelBtn)
	{
		pDelBtn->SetVisible(visible);
	}
}

void CMusicListCtrl::onContextMenu(Object* pSender, EventArgs* pEvent)
{
	auto pMenuArg = (MenuEventArgs*)pEvent;
	LOG_INFO(logger) << "context menu:" << pMenuArg->menuItemName << endl;
}