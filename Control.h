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
extern UINT player1tank[5];//��ʾplayer1����������,fire�������ֵ
extern UINT player2tank[5];//��ʾplayer2����������,fire�������ֵ
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
	public:
		//int flg;//������־ˢ�µ�Ƶ������ʾ�ٶ�
		int type;//0��ʾplayer1,1��ʾplayer2
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
