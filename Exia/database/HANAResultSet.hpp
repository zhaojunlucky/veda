#pragma once
#include <memory>
#include <vector>
#include <InternalBuffer.hpp>
#include "BaseColumn.hpp"
#include "HANAColumnTypeFactory.hpp"

namespace db
{
	typedef std::shared_ptr<HANAResultSet> HANAResultSetPtr;

	class HANAResultSet
	{
	public:
		virtual ~HANAResultSet()
		{

		}

		unsigned short GetColumnCount() const
		{
			return mColumnTypes.size();
		}

		const HANAColumnType& GetColumnType(unsigned short index) const
		{
			return mColumnTypes[index];
		}

		const char* GetColumnName(unsigned short index) const
		{
			return mColumnNames[index].c_str();
		}

		unsigned int GetBatchSize() const
		{
			return mBatchSize;
		}

		unsigned int GetRowSize() const
		{
			return mRowSize;
		}

		bool Next() const
		{
			bool next = (SQL_NO_DATA != SQLFetch(mSQLStmt));
			return next;
		}

		const char* GetVarchar(unsigned short index)
		{
			std::string message;
			SQLLEN colLen = 0;
			SQLLEN buflen;

			SQLColAttribute(mSQLStmt, index, SQL_DESC_LENGTH, NULL, 0, 0, &colLen);
			if (mData->GetBufferSize() <= colLen)
			{
				mData.reset(new common::InternalBuffer<char>(colLen));
			}
			SQLRETURN rc = SQLGetData(mSQLStmt, index, SQL_CHAR, *mData.get(), mData->GetBufferSize(), &buflen);
			if (!SQL_SUCCEEDED(rc))
			{
				HANAException::GetHANAErrorMessage(SQL_HANDLE_STMT, mSQLStmt, rc, message);
				throw HANAException(message.c_str());
			}
			(*mData)[buflen] = '\0';
			return *mData.get();
		}
		const wchar_t *GetNVarchar(unsigned short index)
		{
			std::string message;
			SQLLEN colLen = 0;
			SQLLEN buflen;

			SQLColAttribute(mSQLStmt, index, SQL_DESC_LENGTH, NULL, 0, 0, &colLen);
			if (mData->GetBufferSize() <= colLen)
			{
				mWData.reset(new common::InternalBuffer<wchar_t>(colLen));
			}
			SQLRETURN rc = SQLGetData(mSQLStmt, index, SQL_WCHAR, *mWData.get(), mWData->GetBufferSize(), &buflen);
			if (!SQL_SUCCEEDED(rc))
			{
				HANAException::GetHANAErrorMessage(SQL_HANDLE_STMT, mSQLStmt, rc, message);
				throw HANAException(message.c_str());
			}
			(*mWData)[buflen] = L'\0';
			return *mWData.get();
		}
		double GetDouble(unsigned index)
		{
			return atof(GetVarchar(index));
		}
		int GetInteger(unsigned index)
		{
			return atoi(GetVarchar(index));
		}
		BigInt GetBigInt(unsigned index)
		{
			return _atoi64(GetVarchar(index));
		}
		long GetLong(unsigned index)
		{
			return atol(GetVarchar(index));
		}
	private:
		friend class HANAStatement;
		friend class HANAPreparedStatement;
		friend class HANACallableStatement;
		HANAResultSet(HANAStatement* stmt, SQLHSTMT sqlStmt)
			:mStmt(stmt), mSQLStmt(sqlStmt), mBatchSize(1000)
		{
			mData.reset(new common::InternalBuffer<char>(1024));
			mWData.reset(new common::InternalBuffer<wchar_t>(1024));

			Init();
		}

		void Init()
		{
			std::string message;
			short colCount = 0;
			SQLRETURN rc = SQLNumResultCols(mSQLStmt, (SQLSMALLINT*)&colCount);

			if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
			{
				HANAException::GetHANAErrorMessage(SQL_HANDLE_STMT, mSQLStmt, rc, message);
				throw HANAException(message.c_str());
			}
			SQLSMALLINT len;
			SQLLEN colType;
			char data[1024];

			for (int i = 0; i < colCount; i++)
			{
				rc = SQLColAttributeA(mSQLStmt, i, SQL_DESC_TYPE, 0, 0, 0, &colType);

				rc = SQLColAttributeA(mSQLStmt, i, SQL_DESC_NAME, data, 1023, &len, NULL);



				data[len] = '\0';
				mColumnNames.push_back(data);
				switch (colType)
				{
				case SQL_VARCHAR:
				{
					SQLLEN colLen;
					rc = SQLColAttributeA(mSQLStmt, i, SQL_DESC_LENGTH, NULL, 0, 0, &colLen);
					HANAColumnType hct = HANAColumnTypeFactory::CreateVarchar(colLen);
					mColumnTypes.push_back(hct);
				}break;
				case SQL_WCHAR:
				{
					SQLLEN colLen;
					rc = SQLColAttributeA(mSQLStmt, i, SQL_DESC_LENGTH, NULL, 0, 0, &colLen);
					HANAColumnType hct = HANAColumnTypeFactory::CreateNVarchar(colLen);
					mColumnTypes.push_back(hct);
				}break;

				case SQL_DECIMAL:
				{
					SQLLEN p;
					SQLLEN s;
					rc = SQLColAttributeA(mSQLStmt, i, SQL_DESC_PRECISION, NULL, 0, 0, &p);
					rc = SQLColAttributeA(mSQLStmt, i, SQL_DESC_SCALE, NULL, 0, 0, &s);

					HANAColumnType hct = HANAColumnTypeFactory::CreateDecimal(p, s);
					mColumnTypes.push_back(hct);
				}break;
				case SQL_INTEGER:
				{
					HANAColumnType hct = HANAColumnTypeFactory::CreateInteger();
					mColumnTypes.push_back(hct);
				}break;
				case SQL_SMALLINT:
				{
					HANAColumnType hct = HANAColumnTypeFactory::CreateSmallInt();
					mColumnTypes.push_back(hct);
				}break;
				case SQL_TINYINT:
				{
					HANAColumnType hct = HANAColumnTypeFactory::CreateTinyInt();
					mColumnTypes.push_back(hct);
				}break;
				case SQL_REAL:
				{
					HANAColumnType hct = HANAColumnTypeFactory::CreateReal();
					mColumnTypes.push_back(hct);
				}break;
				case SQL_FLOAT:
				case SQL_DOUBLE:
				{
					HANAColumnType hct = HANAColumnTypeFactory::CreateDouble();
					mColumnTypes.push_back(hct);
				}break;
				case SQL_BIGINT:
				{
					HANAColumnType hct = HANAColumnTypeFactory::CreateBigInt();
					mColumnTypes.push_back(hct);
				}break;

				case SQL_TYPE_TIMESTAMP:
				{
					HANAColumnType hct = HANAColumnTypeFactory::CreateTimestamp();
					mColumnTypes.push_back(hct);
				}break;
				case SQL_DATETIME:
				{
					HANAColumnType hct = HANAColumnTypeFactory::CreateSecondDate();
					mColumnTypes.push_back(hct);
				}break;
				case SQL_TYPE_DATE:
				{
					HANAColumnType hct = HANAColumnTypeFactory::CreateDate();
					mColumnTypes.push_back(hct);
				}break;
				case SQL_TYPE_TIME:
				{
					HANAColumnType hct = HANAColumnTypeFactory::CreateTime();
					mColumnTypes.push_back(hct);
				}break;
				default:
				{
					char buf[128];
					sprintf(buf, "unkown sql type:%d", colType);
					throw HANAException(buf);
				}break;
				}
			}
		}
	private:
		HANAStatement* mStmt;
		SQLHSTMT mSQLStmt;
		std::vector<HANAColumnType> mColumnTypes;
		std::vector<std::string> mColumnNames;
		unsigned int mBatchSize;
		unsigned int mRowSize;
		std::shared_ptr<common::InternalBuffer<char>> mData;
		std::shared_ptr<common::InternalBuffer<wchar_t>> mWData;
	};
}