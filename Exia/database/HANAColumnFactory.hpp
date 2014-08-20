#pragma once
#include "HANAException.hpp"
#include "Column.hpp"
#include "BaseColumn.hpp"
#include "HANATypes.h"
#include <string>
namespace db
{
	class HANAColumnFactory
	{
	public:
		static Column* CreateColumnByType(const std::string& name,const HANAColumnType& type)
		{
			switch (type.sqlDataType)
			{
			case SqlDataType::SBIGINT:
				return new BigIntColumn(name,type);
			case SqlDataType::SDATE:
				return new DateColumn(name, type);
			case SqlDataType::SDECIMAL:
				return new DecimalColumn(name, type);
			case SqlDataType::SDOUBLE:
				return new DoubleColumn(name, type);
			case SqlDataType::SFLOATN:
				return new FloatNColumn(name, type);
			case SqlDataType::SINTEGER:
				return new IntegerColumn(name, type);
			case SqlDataType::SNVARCHAR:
				return new NVarcharColumn(name, type);
			case SqlDataType::SREAL:
				return new RealColumn(name, type);
			case SqlDataType::SSECONDDATE:
				return new SecondDateColumn(name, type);
			case SqlDataType::SSMALLINT:
				return new SmallIntColumn(name, type);
			case SqlDataType::STIME:
				return new TimeColumn(name, type);
			case SqlDataType::STIMESTAMP:
				return new TimestampColumn(name, type);
			case SqlDataType::STINYINT:
				return new TinyIntColumn(name, type);
			case SqlDataType::SVARCHAR:
				return new VarcharColumn(name, type);
			default:
				throw HANAException("unknown column type");
			}
		}
	};
}