#pragma once

#include "HANATypes.h"

namespace db
{
	class HANAColumnTypeFactory
	{
	public:
		static HANAColumnType CreateVarchar(unsigned int size,bool isNullable = true)
		{
			return HANAColumnType(SVARCHAR, CVARCHAR, 0, 0, size, isNullable);
		}

		static HANAColumnType CreateNVarchar(unsigned int size, bool isNullable = true)
		{
			return HANAColumnType(SNVARCHAR, CNVARCHAR, 0, 0, size, isNullable);
		}

		static HANAColumnType CreateDecimal(unsigned int precision, unsigned int scale, bool isNullable = true)
		{
			return HANAColumnType(SDECIMAL, CDECIMAL, precision, scale, precision + scale + 2, isNullable);
		}

		static HANAColumnType CreateInteger(bool isNullable = true)
		{
			return HANAColumnType(SINTEGER, CINTEGER, 0, 0, 4, isNullable);
		}

		static HANAColumnType CreateSmallInt(bool isNullable = true)
		{
			return HANAColumnType(SSMALLINT, CSMALLINT, 0, 0, 0, isNullable);
		}

		static HANAColumnType CreateTinyInt(bool isNullable = true)
		{
			return HANAColumnType(STINYINT, CTINYINT, 0, 0, 0, isNullable);
		}

		static HANAColumnType CreateFloatN(unsigned int n, bool isNullable = true)
		{
			return HANAColumnType(SFLOATN, CFLOATN, 0, 0, n + 2, isNullable);
		}

		static HANAColumnType CreateReal(bool isNullable = true)
		{
			return HANAColumnType(SREAL, CREAL, 0, 0, 0, isNullable);
		}
		static HANAColumnType CreateDouble(bool isNullable = true)
		{
			return HANAColumnType(SDOUBLE, CDOUBLE, 0, 0, 0, isNullable);
		}
		static HANAColumnType CreateBigInt(bool isNullable = true)
		{
			return HANAColumnType(SBIGINT, CBIGINT, 0, 0, 0, isNullable);
		}
		static HANAColumnType CreateTimestamp(bool isNullable = true)
		{
			return HANAColumnType(STIMESTAMP, CTIMESTAMP, 0, 0, 0, isNullable);
		}
		static HANAColumnType CreateSecondDate(bool isNullable = true)
		{
			return HANAColumnType(SSECONDDATE, CSECONDDATE, 0, 0, 0, isNullable);
		}
		static HANAColumnType CreateDate(bool isNullable = true)
		{
			return HANAColumnType(SDATE, CDATE, 0, 0, 0, isNullable);
		}
		static HANAColumnType CreateTime(bool isNullable = true)
		{
			return HANAColumnType(STIME, CTIME, 0, 0, 0, isNullable);
		}
		
		static SqlDataType ParseSqlDataType(const wchar_t* type)
		{
			SqlDataType dt = SqlDataType::SUNKNOWN_TYPE;
			if (0 == wcsicmp(type, L"varchar"))
			{
				dt = SqlDataType::SVARCHAR;
			}
			else if (0 == wcsicmp(type, L"nvarchar"))
			{
				dt = SqlDataType::SNVARCHAR;
			}
			else if (0 == wcsicmp(type, L"DECIMAL"))
			{
				dt = SqlDataType::SDECIMAL;
			}
			else if (0 == wcsicmp(type, L"INTEGER"))
			{
				dt = SqlDataType::SINTEGER;
			}
			else if (0 == wcsicmp(type, L"SMALLINT"))
			{
				dt = SqlDataType::SSMALLINT;
			}
			else if (0 == wcsicmp(type, L"TINYINT"))
			{
				dt = SqlDataType::STINYINT;
			}
			else if (0 == wcsicmp(type, L"FLOATN"))
			{
				dt = SqlDataType::SFLOATN;
			}
			else if (0 == wcsicmp(type, L"real"))
			{
				dt = SqlDataType::SREAL;
			}
			else if (0 == wcsicmp(type, L"double"))
			{
				dt = SqlDataType::SDOUBLE;
			}
			else if (0 == wcsicmp(type, L"bigint"))
			{
				dt = SqlDataType::SBIGINT;
			}
			else if (0 == wcsicmp(type, L"date"))
			{
				dt = SqlDataType::SDATE;
			}
			else if (0 == wcsicmp(type, L"TIME"))
			{
				dt = SqlDataType::STIME;
			}
			else if (0 == wcsicmp(type, L"TIMESTAMP"))
			{
				dt = SqlDataType::STIMESTAMP;
			}
			else if (0 == wcsicmp(type, L"seconddate"))
			{
				dt = SqlDataType::SSECONDDATE;
			}
			return dt;
		}
	};
}