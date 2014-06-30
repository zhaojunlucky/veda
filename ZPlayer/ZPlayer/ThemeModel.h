#pragma once
#pragma once
#include <string>
using namespace std;
namespace zpl
{
#define PLAY_LIST_TEMPLATE "<div class=\"caption\">%s</div><div class = \"details\">&nbsp; &nbsp; &nbsp; &nbsp; %d songs</div>"
#define MUSIC_LIST_TEMPLATE "<div class = \"caption\" uuid=\"%s\">%s</div><div class = \"details\">&nbsp; &nbsp; &nbsp; &nbsp; %s</div>"

	class ThemeModel
	{
	public:
		ThemeModel();
		~ThemeModel();

	public:
		wstring playCSSImg;
		wstring pauseCSSImg;
	};
}
