#ifndef LYbulletshow_S
#define LYbulletshow_S
#include "view.h"
namespace view
{
	class BulletShow:public Show
	{
	public:
		int type;
		BulletShow(int rat,int type);                         //type表示bullet种类，上右下左
		virtual void Repaint() ;
		virtual void move(int x, int y,...);//传进位置对资源进行初始化,传进type表示bullet类型

	};

}
#endif