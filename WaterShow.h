#include "view.h"
namespace view
{
	class WaterShow:Show
	{
	public:
		WaterShow(int rat,int type);
		int type;                           //type��ʾwater���࣬0,1��ʾ
		virtual void Repaint() ;
		virtual void move(int x, int y,...);//����λ�ö���Դ���г�ʼ����������type

	};

}