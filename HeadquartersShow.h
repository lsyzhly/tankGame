#ifndef LYheadquartershow_S
#define LYheadquartershow_S
#include "view.h"
namespace view
{
	class HeadquartersShow:Show
	{
	public:
		HeadquartersShow(int rat,int type);
		int type;                           //type表示headquarters种类，0,1表示
		virtual void Repaint() ;
		virtual void move(int x, int y,...);//传进位置对资源进行初始化，并传进type

	};

}
#endif