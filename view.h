#ifndef VIEW_H
#define VIEW_H
#include "all.h"
#include "main.h"

namespace view{
	//��ʾ����,������
	//ֻ������ʾ,
	class Show{
	public:
		RECT rec;
		//���������������opengl,����directx�����޸�
		//������,��ʾ��������С��ʵ����ʾ��С�ı���
		int rat;
		Show(int rat);
		//���ƶ�λ�û���ͼ��
		virtual void Repaint() = 0;
		//����λ�úͷ���
		virtual void move(int x, int y,...)=0;
		virtual ~Show();
	};
	class moveShow:public Show{
    public:
        int maxcount;
        int count;
	};
}

#endif
