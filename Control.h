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
	//������������
	//movesquare�������ƶ�
	//Control�ฺ������ƶ�
	class Control{
	protected:
		int maxcount;
		int count;
		Control(int maxcount);
	public:
		//�ƶ�һ�δ��鷽��
		virtual bool run() = 0;
		virtual ~Control();
	};
	//̹���Զ�������,���ڿ�����ͨ�ط�̹��
	//TODO ��ӿ�����
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