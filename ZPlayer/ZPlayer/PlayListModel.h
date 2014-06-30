#pragma once 
#include <string>
using namespace std;
namespace zpl
{
	struct PlayListModel
	{
		PlayListModel(const string& uuid, const string& name)
			:uuid(uuid), name(name)
		{

		}
		string uuid;
		string name;
	};
}