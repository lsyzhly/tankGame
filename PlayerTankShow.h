#include "view.h"
namespace view
{
	class PlayerTankShow:Show
	{
	public:
		int size;//tank�Ĵ�С
		int dir;//tank�ķ���
		//int dis;//tank�ƶ��ľ���
		int rank;//tank�ĵȼ�,��ֵ0��1,2,3
		int flag;//tank��Ӧ�õ�ͼƬ��0��־��һ�ţ�1��ʾ�ڶ���
		int player;//tank������ң�1��ʾ���һ��2��ʾ��Ҷ�

		PlayerTankShow(int rat,int rank,int player);
		virtual void Repaint() ;
		virtual void move(int x, int y,...);//��Ҫ�������Ĳ�������Դ��x,y,tank�ƶ��ķ���,tank�ȼ�

	};

}