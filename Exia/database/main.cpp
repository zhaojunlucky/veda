#include "database.h"
#include <iostream>
#include <conio.h>

using namespace std;
using namespace db;

void SetDatabase(HANAConnection& conn, const wchar_t* sql);
int main()
{
	cout << "sizeof(wchar_t):" << sizeof(wchar_t) << endl;
	HANAColumnType nvar = HANAColumnTypeFactory::CreateNVarchar(50);
	HANAColumnType intCol = HANAColumnTypeFactory::CreateInteger();

	Column* name = new NVarcharColumn("name", nvar);
	Column* password = new NVarcharColumn("name", nvar);

	Column* gender = new NVarcharColumn("", nvar);
	Column* age = new IntegerColumn("age", intCol);
	age->AddData("12");
	age->AddData("19");
	
	name->AddData(L"zhaojunÕÔ¿¡");
	password->AddData(L"123456");
	gender->AddData(L"ÄÐ");

	name->AddData(L"chendan³Ìµ¤");
	password->AddData(L"12111");
	gender->AddData(L"Å®");
	
	wchar_t names[3][51] = { L"ÄÐ", L"Å®" };
	cout << "sizeof(names[0]):" << sizeof(names[0]) << endl;
	SQLLEN l[2] = {SQL_NTS,SQL_NTS};
	NVarcharColumn* col = (NVarcharColumn*)gender;
	VarcharColumn* col1 = (VarcharColumn*)name;
	try
	{
		HANAConnection conn(L"SQLServer", L"sa", L"123456");
		conn.Open();
		SetDatabase(conn, L"USE TEST");
		HANAStatementPtr hst = conn.PrepareStatement(L"INSERT INTO USERTABLE VALUES(?,?,?)");
		hst->SetParameterSize(2);
		hst->BindColumn(1, ParameterType::In, *name);
		//hst->BindParameter(1, ParameterType::In, SQL_C_WCHAR, SQL_WVARCHAR, 50, 0, names, sizeof(names[0]), l);

		hst->BindColumn(2, ParameterType::In, *password);
		hst->BindColumn(3, ParameterType::In, *gender);

		cout << "execute result:" << hst->ExecuteUpdate() << endl;

		conn.Close();
	}
	catch (HANAException &e)
	{
		cout << "error:" << e.what()<<",errcode:"<< e.GetErrorCode()<< endl;
	}
	system("PAUSE");
	return 0;
}

void SetDatabase(HANAConnection& conn, const wchar_t* sql)
{
	HANAStatementPtr hst = conn.PrepareStatement(sql);
	wcout << sql << ":" << hst->ExecuteUpdate() << endl;
}