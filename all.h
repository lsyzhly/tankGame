#ifndef ALL_H
#define ALL_H
#define MOVEDIRECT 0x8000//向某方向移动
#define MOVESETDIRECT 0x2000//设置方向
#define MOVELEVEL 0x4000//设置等级
#define MOVEVALUE 0xfff
#define MOVEFLAG 0xf000
extern int *test_type;
enum direct{ up=0, down=2, left=3, right=1 };

//不能移动的类型,墙和土
enum unmoveType{ tu=1 ,qiang=2, cao=3};

//碰撞的类型
enum bumpType {
	stop = 1,//碰撞后停止
	abandonded = 2,
	through = 4,//碰撞后穿过
	astop = 3
};

//方向取反
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

#define movedrt(drt,rect,size) {\
	switch(drt){\
		case up:\
			rect.top-=size;\
			rect.bottom-=size;\
			break;\
		case down:\
			rect.top+=size;\
			rect.bottom+=size;\
			break;\
		case left:\
			rect.right-=size;\
			rect.left-=size;\
			break;\
		case right:\
			rect.right+=size;\
			rect.left+=size;\
			break;\
	}\
}

#endif
