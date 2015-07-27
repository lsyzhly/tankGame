#include "view.h"
namespace view
{
	class PlayerTankShow:Show
	{
	public:
		int size;//tank的大小
		int dir;//tank的方向
		//int dis;//tank移动的距离
		//int rank;//tank的等级
		int flag;//tank所应用的图片，0标志第一张，1表示第二张

		PlayerTankShow(int rat);
		virtual void Repaint() ;
		virtual void move(int x, int y,...);

	}

}