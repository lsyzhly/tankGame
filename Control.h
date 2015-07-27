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
#include <vector>
#include <set>
#include "item.h"
#include "bumpcheck.h"
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
		int count;
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
		bool type;
		Tank *tank;
		playTankControl(Tank *tank,bool type);
		virtual bool run();
	};
}
#endif