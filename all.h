#ifndef ALL_H
#define ALL_H
#define MOVEDIRECT 0x8000//向某方向移动
#define MOVESETDIRECT 0x2000//设置方向
#define MOVELEVEL 0x4000//设置等级
#define MOVESTATE 0x1000//设置状态
#define MOVEVALUE 0xfff
#define MOVEFLAG 0xf000
#define BULLETSIZE 4
#define SCREENW 416
#define SCREENH 416
#include <stdio.h>
extern int *test_type;
extern FILE *fpi;
enum direct { up=0, down=2, left=3, right=1 ,wrong};

//不能移动的类型,墙和土
enum unmoveType { tu=1 ,qiang=2, cao=3,shui=4,boss=5,tank=6,myclock=7,shovel=8,bomp=9,star=10,cap=11};

//碰撞的类型
enum bumpType
{
    stop = 1,//碰撞后停止
    abandonded = 2,
    through = 4,//碰撞后穿过
    astop = 3
};

namespace bump
{
class bumpchecker;
}

namespace Controler
{
class Control;
typedef Control* cpointer;
}

namespace item
{
class pos;
class square;
class moveSquare;
class unmoveSquare;
class Tank;
class Bullet;
typedef square *pointer;
typedef moveSquare *mpointer;
typedef unmoveSquare *upointer;
}

namespace view
{
class Show;
}

template <class T>
void deletef(T a)
{
    delete a;
}

extern item::Tank *ptanks[2];
extern int pcount;
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
