#ifndef CONTROL_H
#define CONTROL_H
#include <map>
#ifdef CPP11
#include <mutex>
#include <thread>
using std::thread;
using std::mutex;
#endif
#include <list>
#include <time.h>
#include <vector>
#include <set>
#include "item.h"
#include "bumpcheck.h"
extern UINT player1tank[5];//表示player1的上下左右,fire的虚拟键值
extern UINT player2tank[5];//表示player2的上下左右,fire的虚拟键值
namespace Controler{
	using std::map;
	using std::vector;
	using std::set;
	using std::list;
	using item::Tank;
	using item::mpointer;
	using item::pointer;
	using item::Bullet;
	using bump::bumpchecker;
	//控制器抽象类
	//movesquare本身不能移动
	//Control类负责控制移动
	class Control{
	protected:
		int maxcount;
		Control(int maxcount);
	public:
		//移动一次纯虚方法
		virtual bool run() = 0;
		virtual ~Control();
	};
	//坦克自动控制类,用于控制普通地方坦克
	//TODO 添加开火功能
	class autoTankControl :public Control{
	public:
		Tank *tank;
		autoTankControl(Tank *tank);
		virtual bool run();
	};
	class playTankControl:public Control{
	public:
		//int flg;//用来标志刷新的频率来表示速度
		int type;//0表示player1,1表示player2
		Tank *tank;
		playTankControl(Tank *tank,int type);
		clock_t clo;
		virtual bool run();
	};
	class bulletControl:public Control{
    public:
        Bullet *bul;
		bulletControl(Bullet *bul);
		virtual ~bulletControl();
		virtual bool run();
	};
}
#endif
