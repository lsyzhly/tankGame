#include "view.h"
namespace view
{
	class HeadquartersShow:Show
	{
	public:
		HeadquartersShow(int rat,int type);
		int type;                           //type��ʾheadquarters���࣬0,1��ʾ
		virtual void Repaint() ;
		virtual void move(int x, int y,...);//����λ�ö���Դ���г�ʼ����������type

	};

}