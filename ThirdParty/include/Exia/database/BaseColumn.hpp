#pragma once
#ifdef WIN32
#include <Windows.h>
#endif
#include <sql.h>
#include <sqlext.h>
#include <vector>
#include <string>
#include "Column.hpp"
#include "HANATypes.h"
#include "DataConvertUtil.hpp"

namespace db
{
		 
	template<class T>
	class BaseColumn : public Column
	{
	public:
		BaseColumn(const std::string& columnName,const HANAColumnType& columnType)
			:mColumnName(columnName), mColumnType(columnType)
		{

		}

		virtual ~BaseColumn()
		{

		}

		size_t GetSize() const
		{
			return mData.size();
		}

		const void* GetDataPtr() const
		{
			return (void*)mData.data();
		}
		const void* GetDataLenPtr() const
		{
			return (void*)mDataLen.data();
		}

		const char* GetColumnName() const
		{
			return mColumnName.c_str();
		}

		const HANAColumnType& GetColumnType() const
		{
			return mColumnType;
		}

		void Clear()
		{
			mData.clear();
			mDataLen.clear();
		}

		virtual void Reserve(size_t size)
		{
			mData.reserve(size);
			mDataLen.reserve(size);
		}

		virtual void Resize(size_t size)
		{
			mData.resize(size);
			mDataLen.resize(size);
		}

		void RemoveLast()
		{
			mData.pop_back();
			mDataLen.pop_back();
		}

		virtual bool AddData(const char* data, size_t len)
		{
			bool ret = true;
			T value;
			bool isNull = (data == NULL || len == 0);

			if (isNull)
			{
				memset(&value, 0, sizeof(T));
			}
			else
			{
				ret = StrToValue(data, value);
			}
			if (ret)
			{
				mData.push_back(value);
				mDataLen.push_back(isNull && mColumnType.isNullable ? SQL_NULL_DATA : SQL_NTS);
			}
			return ret;

		}

		virtual bool AddData(const std::string& data)
		{
			return AddData(data.c_str(), data.size());
		}

		virtual bool AddData(const wchar_t* data,size_t len)
		{
			bool ret = true;
			T value;
			bool isNull = (data == NULL || len == 0);

			if (isNull)
			{
				memset(&value, 0, sizeof(T));
			}
			else
			{
				ret = StrToValue(data, value);
			}
			if (ret)
			{
				mData.push_back(value);
				mDataLen.push_back(isNull && mColumnType.isNullable ? SQL_NULL_DATA : SQL_NTS);
			}
			return ret;
		}

		virtual bool AddData(const std::wstring& data)
		{
			return AddData(data.c_str(), data.size());
		}

	protected:
		std::vector<T> mData;
		std::vector<SQLULEN> mDataLen;
		std::string mColumnName;
		HANAColumnType mColumnType;
	};

	template<class T>
	class BaseCharColumn : public BaseColumn<T>
	{
	public:
		BaseCharColumn(const std::string& columnName, const HANAColumnType& columnType)
			:BaseColumn<T>(columnName, columnType)
		{

		}
		virtual ~BaseCharColumn()
		{

		}

		virtual void Reserve(size_t size)
		{
			mData.reserve(size*mColumnType.size);
			mDataLen.reserve(size);
		}

		virtual void Resize(size_t size)
		{
			mData.resize(size*mColumnType.size);
			mDataLen.resize(size);
		}

		virtual bool AddData(const char* data, size_t len)
		{
			
			bool isNull = (data == NULL || len == 0);
			
			if (isNull)
			{
				len = 0;
			}

			if (mColumnType.sqlDataType != SNVARCHAR)
			{
				if (len > mColumnType.size)
				{
					return false;
				}
				for (size_t i = 0; i < len; i++)
				{
					mData.push_back(data[i]);
				}
				for (size_t i = len; i <= mColumnType.size; i++)
				{
					mData.push_back('\0');
				}
			}
			else
			{
				std::wstring wstr = L"";
				eio::StringConvertInternal sci;
				if (!isNull)
				{
					wstr = sci.Char2Wchar(data, len);
				}
				if (wstr.size() > mColumnType.size)
				{
					return false;
				}
				for (size_t i = 0; i < wstr.size(); i++)
				{
					mData.push_back(wstr.c_str()[i]);
				}
				for (size_t i = wstr.size(); i <= mColumnType.size; i++)
				{
					mData.push_back('\0');
				}
			}
			
			mDataLen.push_back(isNull && mColumnType.isNullable ? SQL_NULL_DATA : SQL_NTSL);
			return true;

		}

		virtual bool AddData(const wchar_t* data, size_t len)
		{

			bool isNull = (data == NULL || len == 0);

			if (isNull)
			{
				len = 0;
			}

			if (mColumnType.sqlDataType != SVARCHAR)
			{
				if (len > mColumnType.size)
				{
					return false;
				}
				for (size_t i = 0; i < len; i++)
				{
					mData.push_back(data[i]);
				}
				for (size_t i = len; i <= mColumnType.size; i++)
				{
					mData.push_back('\0');
				}
			}
			else
			{
				std::string str = "";
				eio::StringConvertInternal sci;
				if (!isNull)
				{
					str = sci.Wchar2Char(data, len);
				}
				if (str.size() > mColumnType.size)
				{
					return false;
				}
				for (size_t i = 0; i < str.size(); i++)
				{
					mData.push_back(str.c_str()[i]);
				}
				for (size_t i = str.size(); i <= mColumnType.size; i++)
				{
					mData.push_back('\0');
				}
			}

			mDataLen.push_back(isNull && mColumnType.isNullable ? SQL_NULL_DATA : SQL_NTSL);
			return true;

		}
	};


	typedef BaseCharColumn<char> VarcharColumn;
	typedef BaseCharColumn<wchar_t> NVarcharColumn;

	typedef BaseCharColumn<char> DecimalColumn;
	typedef BaseColumn<int> IntegerColumn;
	typedef BaseColumn<short> SmallIntColumn;
	typedef BaseColumn<unsigned char> TinyIntColumn;
	typedef BaseCharColumn<char> FloatNColumn;
	typedef BaseColumn<float> RealColumn;
	typedef BaseColumn<double> DoubleColumn;
	typedef BaseColumn<BigInt> BigIntColumn;

	typedef BaseColumn<SQL_DATE_STRUCT> DateColumn;
	typedef BaseColumn<SQL_TIME_STRUCT> TimeColumn;
	typedef BaseColumn<SQL_TIMESTAMP_STRUCT> TimestampColumn;
	typedef BaseColumn<SQL_TIMESTAMP_STRUCT> SecondDateColumn;

}