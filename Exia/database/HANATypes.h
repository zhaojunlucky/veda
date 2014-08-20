#pragma once
#ifdef WIN32
#include <Windows.h>
#endif
#include <sql.h>
#include <sqlext.h>

namespace db
{
#define BigInt __int64
	enum SqlDataType
	{
		SUNKNOWN_TYPE = SQL_UNKNOWN_TYPE,
		/*
		The VARCHAR(n) data type specifies a variable-length ASCII character string, where n indicates the maximum length in bytes and is an integer between 1 and 5000.
		 */
		SVARCHAR = SQL_VARCHAR,
		SNVARCHAR = SQL_WVARCHAR,

		SDECIMAL = SQL_DECIMAL,
		SINTEGER = SQL_INTEGER,
		SSMALLINT = SQL_SMALLINT,
		STINYINT = SQL_TINYINT,
		SFLOATN = SQL_FLOAT,
		SREAL = SQL_REAL,
		SDOUBLE = SQL_DOUBLE,
		SBIGINT = SQL_BIGINT,
		//SMALLDECIMAL = SQL_DECIMAL,

		STIMESTAMP = SQL_TYPE_TIMESTAMP,
		SSECONDDATE = SQL_DATETIME,
		SDATE = SQL_TYPE_DATE,
		STIME = SQL_TYPE_TIME

	};

	enum CDataType
	{
		CUNKNOWN_TYPE = SQL_UNKNOWN_TYPE,
		CVARCHAR = SQL_C_CHAR,
		CNVARCHAR = SQL_C_WCHAR,

		CDECIMAL = SQL_C_CHAR, // length should be p + s + 2
		CINTEGER = SQL_C_LONG,
		CSMALLINT = SQL_C_LONG,
		CTINYINT = SQL_C_LONG,
		CFLOATN = SQL_C_DOUBLE,
		CREAL = SQL_REAL,
		CDOUBLE = SQL_C_DOUBLE,
		CBIGINT = SQL_C_SBIGINT,
		CTIMESTAMP = SQL_C_TYPE_TIMESTAMP,
		CSECONDDATE = SQL_C_TYPE_TIMESTAMP,
		CDATE = SQL_C_TYPE_DATE,
		CTIME = SQL_C_TYPE_TIME

	};

	struct HANAColumnType
	{
		HANAColumnType()
			:sqlDataType(SqlDataType::SUNKNOWN_TYPE)
		{

		}
		HANAColumnType(SqlDataType sqlDataType, CDataType cDataType, unsigned short precision, unsigned short scale, unsigned int size,bool isNullable)
			:sqlDataType(sqlDataType), cDataType(cDataType), precision(precision), scale(scale), size(size), isNullable(isNullable)
		{
			if (cDataType == CDataType::CNVARCHAR)
			{
				this->dataSize = sizeof(wchar_t) *(size+1);
			}
			else if (cDataType == CDataType::CVARCHAR)
			{
				this->dataSize = sizeof(char)*(size + 1);
			}
			else
			{
				this->dataSize = size;
			}
		}

		HANAColumnType(const HANAColumnType& hdt)
		{
			sqlDataType = hdt.sqlDataType;
			cDataType = hdt.cDataType;
			precision = hdt.precision;
			scale = hdt.scale;
			size = hdt.size;
			dataSize = hdt.dataSize;
		}

		HANAColumnType& operator = (const HANAColumnType& hdt)
		{
			if (this != &hdt)
			{
				sqlDataType = hdt.sqlDataType;
				cDataType = hdt.cDataType;
				precision = hdt.precision;
				scale = hdt.scale;
				size = hdt.size;
				dataSize = hdt.dataSize;
			}
			return *this;
		}
		SqlDataType sqlDataType;
		CDataType cDataType;
		unsigned short precision;
		unsigned short scale;// for decimal(p,3)
		unsigned int size;// for varchar 
		unsigned int dataSize;
		bool isNullable;
	};

	//DATE TIME SECOND_DATE TIME_STAMP TINYINT(unsigned char) SMALLINT(short) INTEGER(int) BIGINT(INT64)
	//	DECIMAL(precision 1 - 34, scale 0 - p)  SMALLDECIMAL(p, s) REAL(float) DOUBLE(double) FLOAT(n) n < 25 float n >= 25 double default double
	//	VARCHAR 1-5000 ascii
	//	NVARCHAR 1-5000 unicode
}