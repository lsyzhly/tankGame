#ifndef LYbulletshow_S
#define LYbulletshow_S
#include "view.h"
namespace view
{
	class BulletShow:public Show
	{
	public:
		int type;
		BulletShow(int rat,int type);                         //type��ʾbullet���࣬��������
		virtual void Repaint() ;
		virtual void move(int x, int y,...);//����λ�ö���Դ���г�ʼ��,����type��ʾbullet����

	};

}
#endif