#ifndef ALL_H
#define ALL_H
enum direct{ up=0, down=1, left=2, right=3 };

//�����ƶ�������,ǽ����
enum unmoveType{ qiang, tu ,cao};

//��ײ������
enum bumpType {
	stop = 1,//��ײ��ֹͣ
	abandonded = 2,
	through = 4,//��ײ�󴩹�
	astop = 3
};

//����ȡ��
direct operator!(direct);

namespace bump{
	class bumpchecker;
}

namespace Controler{
	class Control;
	class autoTankControl;
	typedef Control* cpointer;
}

namespace item{
	class square;
	class moveSquare;
	class unmoveSquare;
	class Tank;
	class Bullet;
	typedef square *pointer;
	typedef moveSquare *mpointer;
	typedef unmoveSquare *upointer;
}

namespace view{
	class Show;
}

#endif