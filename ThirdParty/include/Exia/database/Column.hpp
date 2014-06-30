#pragma once
#include "HANATypes.h"
#include <string>

namespace db
{
	class Column
	{
	public:
		virtual size_t GetSize() const = 0;
		virtual const void* GetDataPtr() const = 0;
		virtual const void* GetDataLenPtr() const = 0;

		virtual const char* GetColumnName() const = 0;

		virtual const HANAColumnType& GetColumnType() const = 0;

		virtual void Clear() = 0;

		virtual void Reserve(size_t size) = 0;
		virtual void Resize(size_t size) = 0;

		virtual void RemoveLast() = 0;

		virtual bool AddData(const char* data, size_t len) = 0;
		virtual bool AddData(const std::string& data) = 0;
		virtual bool AddData(const wchar_t* data, size_t len) = 0;
		virtual bool AddData(const std::wstring& data) = 0;
	};
}