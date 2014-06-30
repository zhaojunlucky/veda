#pragma once
#include "ZHUICtrl.h"
namespace zhui
{
	class __declspec(dllexport) ZHSelectCtrl :
		public ZHUICtrl
	{
	public:
		ZHSelectCtrl();
		ZHSelectCtrl(const element& el);
		ZHSelectCtrl(const HELEMENT he);
		ZHSelectCtrl(const ZHUICtrl& ctrl);
		virtual ~ZHSelectCtrl();

		unsigned int GetItemCount() const;
		HELEMENT GetItem(unsigned index) const;
		const wchar_t* GetItemText(unsigned index) const;
		element AddItem(const wchar_t* text);
		element AddItemWithHtml(const char* html);
		void AddItem(const element& e);
		element InsertItemWithHtml(unsigned int index, const char* html);
		element InsertItem(unsigned int index, const wchar_t* text);
		void InsertItem(unsigned int index, const element& e);
		void GetSelectItemsIndex(std::vector<unsigned int>& itemsIndex);
		unsigned int getSelectItemIndex() const;
		void SetSelectIndex(unsigned int index);
		void Remove(unsigned int index);
		void Clear();
		void UpdateItemText(unsigned int index, const wchar_t* text);
		void UpdateItemHtml(unsigned int index, const char* html);
	};
}


