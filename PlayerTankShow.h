#include "view.h"
namespace view
{
	class PlayerTankShow:Show
	{
	public:
		int size;//tank�Ĵ�С
		int dir;//tank�ķ���
		//int dis;//tank�ƶ��ľ���
		//int rank;//tank�ĵȼ�
		int flag;//tank��Ӧ�õ�ͼƬ��0��־��һ�ţ�1��ʾ�ڶ���

		PlayerTankShow(int rat);
		virtual void Repaint() ;
		virtual void move(int x, int y,...);

	}

}