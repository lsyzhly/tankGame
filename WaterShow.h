#include "view.h"
namespace view
{
	class WaterShow:Show
	{
	public:
		WaterShow(int rat,int type);
		int type;                           //type表示water种类，0,1表示
		virtual void Repaint() ;
		virtual void move(int x, int y,...);//传进位置对资源进行初始化，并传进type

	};

}