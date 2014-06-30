#include "ZHSelectCtrl.h"

namespace zhui
{
	ZHSelectCtrl::ZHSelectCtrl()
		:ZHUICtrl(0)
	{

	}
	ZHSelectCtrl::ZHSelectCtrl(const element& el)
		:ZHUICtrl(el)
	{
	}
	ZHSelectCtrl::ZHSelectCtrl(const HELEMENT he)
		:ZHUICtrl(he)
	{

	}
	ZHSelectCtrl::ZHSelectCtrl(const ZHUICtrl& ctrl)
		:ZHUICtrl(ctrl)
	{

	}


	ZHSelectCtrl::~ZHSelectCtrl()
	{
	}

	unsigned int ZHSelectCtrl::GetItemCount() const
	{
		return el.children_count();
	}

	HELEMENT ZHSelectCtrl::GetItem(unsigned index) const
	{
		return el.child(index);
	}

	const wchar_t* ZHSelectCtrl::GetItemText(unsigned index) const
	{
		return ((element)el.child(index)).text().c_str();
	}

	element ZHSelectCtrl::AddItem(const wchar_t* text)
	{
		element e = el.create("li", text);
		el.append(e);
		return e;
	}

	element ZHSelectCtrl::AddItemWithHtml(const char* html)
	{
		element e = el.create("li");
		el.append(e);
		e.set_html((const unsigned char*)html, strlen(html));
		return e;
	}

	void ZHSelectCtrl::AddItem(const element& e)
	{
		el.append(e);
	}
	element ZHSelectCtrl::InsertItem(unsigned int index, const wchar_t* text)
	{
		element e = el.create("li", text);
		el.insert(e, index);
		return e;
	}
	element ZHSelectCtrl::InsertItemWithHtml(unsigned int index, const char* html)
	{
		element e = el.create("li");
		InsertItem(index, e);
		e.set_html((const unsigned char*)html, strlen(html));
		return e;
	}
	void ZHSelectCtrl::InsertItem(unsigned int index, const element& e)
	{
		el.insert(e, index);
	}
	void ZHSelectCtrl::GetSelectItemsIndex(std::vector<unsigned int>& itemsIndex)
	{
		itemsIndex.clear();
		for (unsigned int i = 0; i < el.children_count(); i++)
		{
			element e = el.child(i);
			if (e.get_state(6))
			{
				itemsIndex.push_back(i);
			}
		}
	}

	unsigned int ZHSelectCtrl::getSelectItemIndex() const
	{
		for (unsigned int i = 0; i < el.children_count(); i++)
		{
			element e = el.child(i);
			if (e.get_state(6))
			{
				return i;
			}
		}
	}
	void ZHSelectCtrl::SetSelectIndex(unsigned int index)
	{
		std::vector<unsigned int> selectedIndex;
		GetSelectItemsIndex(selectedIndex);
		for (size_t i = 0; i < selectedIndex.size(); i++)
		{
			element e = GetItem(selectedIndex[i]);
			e.set_state(0, STATE_CHECKED | STATE_EXPANDED);
		}
		element e = GetItem(index);
		e.set_state(STATE_CHECKED | STATE_EXPANDED);
	}

	void ZHSelectCtrl::Remove(unsigned int index)
	{
		element e = el.child(index);
		e.destroy();
	}
	void ZHSelectCtrl::Clear()
	{
		el.clear();
	}

	void ZHSelectCtrl::UpdateItemText(unsigned int index, const wchar_t* text)
	{
		element e = el.child(index);
		e.set_text(text);
	}
	void ZHSelectCtrl::UpdateItemHtml(unsigned int index, const char* html)
	{
		element e = el.child(index);
		e.set_html((const unsigned char*)html, strlen(html));
	}
}
