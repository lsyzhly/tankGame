#include "view.h"
namespace view
{
	class PlayerTankShow:public Show
	{
	public:
		int dir;//tank�ķ���
		//int dis;//tank�ƶ��ľ���
		int rank;//tank�ĵȼ�,��ֵ0��1,2,3
		int flag;//tank��Ӧ�õ�ͼƬ��0��־��һ�ţ�1��ʾ�ڶ���
		int player;//tank������ң�0��ʾ���һ��1��ʾ��Ҷ�

		PlayerTankShow(int rat,int player);
		virtual void Repaint() ;
		virtual void move(int x, int y,...);//��Ҫ�������Ĳ�������Դ��x,y,tank�ƶ��ķ���,tank�ȼ�

	};

}
